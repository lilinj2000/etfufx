#include <memory>

#include "zmq.h"
#include "gtest/gtest.h"

#include "ZMQPubService.hh"

class ZMQTest : public ::testing::Test
{
public:

  void SetUp()
  {
    pub_service_.reset( new ZMQPubService(addr_pub_) );
    
    zmq_ctx_ = zmq_ctx_new();

    zmq_sub_ = zmq_socket(zmq_ctx_, ZMQ_SUB);
    
    int ret = zmq_setsockopt(zmq_sub_, ZMQ_SUBSCRIBE, "", 0);
    assert( ret==0 );
    
    ret = zmq_connect(zmq_sub_, addr_sub_.data());
    assert( ret==0 );
  
  }

  ZMQTest():
      addr_sub_("tcp://127.0.0.1:6556"),
      addr_pub_("tcp://*:6556"),
      zmq_ctx_(NULL),
      zmq_sub_(NULL)
  {
  }

  
protected:
  std::string addr_sub_;
  std::string addr_pub_;

  void* zmq_ctx_;
  void* zmq_sub_;

  boost::scoped_ptr<ZMQPubService> pub_service_;

};

TEST_F(ZMQTest, subTest)
{

  int count = 0;
  do
  {
    char buffer[1024];
    memset(buffer, 0x0, sizeof(buffer));
    
    int ret = zmq_recv(zmq_sub_, buffer, sizeof(buffer), 0);
    assert(ret!=-1);

    std::cout <<"recv data: " <<buffer <<std::endl;

    count++;

    if( count>10000 )
    {
      pub_service_->stop();

      break;
    }
        
  }while(true);

  ASSERT_TRUE( true );

}


