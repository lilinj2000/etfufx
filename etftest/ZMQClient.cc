#include "ZMQClient.hh"
#include "zmq.h"

#include <iostream>

namespace etf
{

const std::string ACCOUNT_QRY = "EtfQryAccount";
const std::string POSITION_QRY = "EtfQryPosition";
const std::string ORDER_QRY = "EtfQryOrder";
const std::string TRADE_QRY = "EtfQryTrade";
const std::string MD_QRY = "EtfSubMD";
const std::string OVER = "Over";
const int SEND_FLAGS = 0;

ZMQClient::ZMQClient(int argc, char* argv[]):
    done_(false)
{
  try
  {
    std::auto_ptr<soil::Config> config( soil::Config::create() );
    config->configFile() = "etfclient.cfg";
    config->registerOptions( &etf_client_options_ );

    config->loadConfig();
    
    zmq_ctx_ = zmq_ctx_new();

    zmq_req_ = zmq_socket(zmq_ctx_, ZMQ_REQ);

    int rc = zmq_connect(zmq_req_, etf_client_options_.addr_req.data());
    assert( rc==0 );

    zmq_sub_ = zmq_socket(zmq_ctx_, ZMQ_SUB);

    rc = zmq_setsockopt (zmq_sub_, ZMQ_SUBSCRIBE, "", 0);
    assert (rc == 0);

    int sc = zmq_connect(zmq_sub_, etf_client_options_.addr_sub.data());
    assert( sc==0 );

    receive_pub_thread_.reset(new boost::thread(&ZMQClient::receivePubData, this));
    
  }
  catch( ... )
  {
    throw;
  }

}

ZMQClient::~ZMQClient()
{
  zmq_close( zmq_req_ );

  zmq_close( zmq_sub_ );
}

void ZMQClient::run()
{
  while( !done_ )
  {

    int option = -1;
    std::cout <<"1. " <<ACCOUNT_QRY <<std::endl;
    std::cout <<"2. " <<POSITION_QRY <<std::endl;
    std::cout <<"3. " <<ORDER_QRY <<std::endl;
    std::cout <<"4. " <<TRADE_QRY <<std::endl;
    std::cout <<"0. quit" <<std::endl;
    std::cin >>option;

    std::string request;
    switch( option )
    {
      case 1:
        request = ACCOUNT_QRY;
        break;

      case 2:
        request = POSITION_QRY;
        break;

      case 3:
        request = ORDER_QRY;
        break;

      case 4:
        request = TRADE_QRY;
        break;

      case 0:
        std::cout <<"QUIT!!!" <<std::endl;
        
        done_ = true;
        continue;

      default:
        std::cout <<"the input option - " <<option <<" error." <<std::endl
                  <<"the option range is (0-4)" <<std::endl;
    };

    zmq_send(zmq_req_, request.data(), request.length(), SEND_FLAGS);
    
    char buffer[1024];
    int ret = zmq_recv(zmq_req_, buffer, 1024, 0);
    buffer[ret] = 0;
    
    std::cout <<"the receive rep is: " <<buffer <<std::endl;
    
  }  // end while
}

void ZMQClient::receivePubData()
{
  do
  {
    char buffer[1024];
    int ret = zmq_recv(zmq_sub_, buffer, 1024, 0);
    buffer[ret] = 0;
    std::cout <<"the receive pub is: " <<buffer <<std::endl;
    
  }while( !done_ );
 
}

};  // namespace etf
