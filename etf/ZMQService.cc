#include "ZMQService.hh"
#include "ETFLog.hh"
#include "zmq.h"

namespace etf
{

const std::string ACCOUNT_QRY = "EtfQryAccount";
const std::string POSITION_QRY = "EtfQryPosition";
const std::string ORDER_QRY = "EtfQryOrder";
const std::string TRADE_QRY = "EtfQryTrade";
// const std::string MD_QRY = "EtfSubMD";
const std::string OVER = "Over";

ZMQService::ZMQService(int argc, char* argv[])
{
  try
  {
    etf::ETFConfig cfg(argc, argv);

    etf_cfg_ = cfg.etfCfg();

    zmq_ctx_ = zmq_ctx_new();

    zmq_rep_ = zmq_socket(zmq_ctx_, ZMQ_REP);

    int rc = zmq_bind(zmq_rep_, etf_cfg_.addr_rep.data());
    assert( rc==0 );

    zmq_pub_ = zmq_socket(zmq_ctx_, ZMQ_PUB);
    int pc = zmq_bind(zmq_pub_, etf_cfg_.addr_pub.data());
    assert( pc==0 );

    const ufx::UFXCfg& ufx_cfg = cfg.ufxCfg();
    ufx_service_.reset( ufx::TraderService::createService(ufx_cfg));
  }
  catch( ... )
  {
    throw;
  }

}

void ZMQService::run()
{
  while( true )
  {
    char buffer [256] = "";
    zmq_recv (zmq_rep_, buffer, 256, 0);
    ETF_INFO <<"zmq recv: " <<buffer;
    
    zmq_send (zmq_rep_, "OK!!!", 5, 0);

    if( ACCOUNT_QRY==buffer )
    {
      qryAccount();
    }
    else if( POSITION_QRY==buffer )
    {
      qryPosition();
    }
    else if( ORDER_QRY==buffer )
    {
      qryOrder();
    }
    else if( TRADE_QRY==buffer )
    {
      qryTrade();
    }
    else
    {
      ETF_ERROR <<"unknow tag from zm_rep: " <<buffer;
    }
  }  // end while
}


void ZMQService::qryAccount()
{
  ufx::DepositComboQueryResponse resp;
  ufx_service_->depositComboQuery(etf_cfg_.account_code,
                                  etf_cfg_.asset_no,
                                  etf_cfg_.combi_no,
                                  resp);
  std::stringstream rep_stream;
  rep_stream <<"OnRspAccount"
             <<"," <<resp.occupy_deposit_balance
             <<"," <<resp.enable_deposit_balance;

  pubMsg( rep_stream.str() );
}

void ZMQService::qryPosition()
{
  ufx::PositionComboQueryResponse resp;
  ufx_service_->positionComboQuery(etf_cfg_.account_code,
                                   etf_cfg_.asset_no,
                                   etf_cfg_.combi_no,
                                   resp);

  ufx::PositionComboQueryResponse::const_iterator i_iter = resp.begin();

  for(; i_iter!=resp.end(); i_iter++ )
  {
    std::stringstream rep_stream;
    rep_stream <<"OnRspPosition"
               <<"," <<i_iter->stock_code
               <<"," <<i_iter->position_flag
               <<"," <<i_iter->current_amount;

    pubMsg( rep_stream.str() );
  }

  pubMsg( OVER );
}

void ZMQService::qryOrder()
{
  ufx::EntrustComboQueryResponse resp;
  ufx_service_->entrustComboQuery(etf_cfg_.account_code,
                                   etf_cfg_.asset_no,
                                   etf_cfg_.combi_no,
                                   resp);

  ufx::EntrustComboQueryResponse::const_iterator i_iter = resp.begin();

  for(; i_iter!=resp.end(); i_iter++ )
  {
    std::stringstream rep_stream;
    rep_stream <<"OnRspOrder"
               <<"," <<i_iter->stock_code
               <<"," <<i_iter->entrust_direction
               <<"," <<i_iter->futures_direction
               <<"," <<i_iter->entrust_price
               <<"," <<i_iter->entrust_amount
               <<"," <<i_iter->entrust_status
               <<"," <<i_iter->deal_amount;

    pubMsg( rep_stream.str() );
  }

  pubMsg( OVER );
}

void ZMQService::qryTrade()
{
  ufx::DealComboQueryResponse resp;
  ufx_service_->dealComboQuery(etf_cfg_.account_code,
                               etf_cfg_.asset_no,
                               etf_cfg_.combi_no,
                               resp);

  ufx::DealComboQueryResponse::const_iterator i_iter = resp.begin();

  for(; i_iter!=resp.end(); i_iter++ )
  {
    std::stringstream rep_stream;
    rep_stream <<"OnRspTrade"
               <<"," <<i_iter->stock_code
               <<"," <<i_iter->entrust_direction
               <<"," <<i_iter->futures_direction
               <<"," <<i_iter->deal_amount
               <<"," <<i_iter->deal_price
               <<"," <<i_iter->deal_time;

    pubMsg( rep_stream.str() );
  }

  pubMsg( OVER );
}

void ZMQService::pubMsg(const std::string& msg)
{
  // ETF_INFO <<msg;

  do
  {
    int ret = zmq_send_const(zmq_pub_, msg.data(), msg.length(), ZMQ_DONTWAIT);
    if( ret!=msg.length() )
      continue;
    else
      break;
    
  }while(true);
}

};  // namespace etf
