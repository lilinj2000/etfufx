#include "TraderServiceImpl.hh"

#include "UFXLog.hh"

#include <stdexcept>

namespace ufx
{

TraderServiceImpl::TraderServiceImpl(const UFXCfg& cfg):
    cfg_(cfg),
    ufx_config_(NULL),
    ufx_connection_(NULL),
    subsystem_no_(115)
{
  UFX_TRACE <<"TraderServiceImpl::TraderServiceImpl()";

  ufx_util_.reset( new UFXUtil() );
  
  ufx_config_ = NewConfig();

  // load t2sdk config file
  if( ufx_config_->Load( cfg_.t2sdk_cfg.data() )!=0 )
  {
    ufx_util_->throwError("load t2sdk file [" + cfg_.t2sdk_cfg + "] failed");
  }

  ufx_connection_ = NewConnection( ufx_config_ );

  int ret = ufx_connection_->Create2BizMsg(NULL) ;
  if ( 0!=ret )
  {
    ufx_util_->throwError(ufx_connection_,
                          "connection inital callback failed", ret);
  }

  ret = ufx_connection_->Connect(cfg_.connection_timeout) ;
  if (0!=ret )
  {
    ufx_util_->throwError(ufx_connection_,
                          "connection connect failed", ret);
  }

  login();
}

TraderServiceImpl::~TraderServiceImpl()
{
  if( ufx_connection_ )
    ufx_connection_->Release();

  if( ufx_config_ )
    ufx_config_->Release();
}

void TraderServiceImpl::depositComboQuery(const std::string& account_code,
                                          const std::string& asset_no,
                                          const std::string& combi_no,
                                          DepositComboQueryResponse& resp)
{
  UFX_TRACE <<"TraderServiceImpl::depositComboQuery";

  UFX_INFO <<"account code is " <<account_code <<std::endl
           <<"asset no is " <<asset_no <<std::endl
           <<"combi no is " <<combi_no;
  
  DepositComboQueryRequest req;
  req.user_token = user_token_;
  req.account_code = account_code;
  req.asset_no = asset_no;
  req.combi_no = combi_no;

  IF2Packer* packer = ufx_util_->depositComboQueryPacker(req);

  try
  {
    IF2UnPacker* unpacker;
    CallService(FuncDepositComboQuery, packer, &unpacker);

    ufx_util_->showPacket( unpacker );
    
    ufx_util_->depositComboQueryResponse(unpacker, resp);
  }
  catch( ... )
  {
    freePacker( packer );
    
    throw;
  }

  freePacker( packer );

  return;

}

void TraderServiceImpl::positionComboQuery(const std::string& account_code,
                                           const std::string& asset_no,
                                           const std::string& combi_no,
                                           PositionComboQueryResponse& resp)
{
  UFX_TRACE <<"TraderServiceImpl::positionComboQuery";

  UFX_INFO <<"account code is " <<account_code <<std::endl
           <<"asset no is " <<asset_no <<std::endl
           <<"combi no is " <<combi_no;
  
  PositionComboQueryRequest req;
  req.user_token = user_token_;
  req.account_code = account_code;
  req.asset_no = asset_no;
  req.combi_no = combi_no;

  IF2Packer* packer = ufx_util_->positionComboQueryPacker(req);

  try
  {
    IF2UnPacker* unpacker;
    CallService(FuncPositionComboQuery, packer, &unpacker);

    ufx_util_->showPacket( unpacker );
    
    ufx_util_->positionComboQueryResponse(unpacker, resp);
  }
  catch( ... )
  {
    freePacker( packer );
    
    throw;
  }

  freePacker( packer );

  return;

}

void TraderServiceImpl::entrustComboQuery(const std::string& account_code,
                                          const std::string& asset_no,
                                          const std::string& combi_no,
                                          EntrustComboQueryResponse& resp)
{
  UFX_TRACE <<"TraderServiceImpl::entrustComboQuery";

  UFX_INFO <<"account code is " <<account_code <<std::endl
           <<"asset no is " <<asset_no <<std::endl
           <<"combi no is " <<combi_no;
  
  EntrustComboQueryRequest req;
  req.user_token = user_token_;
  req.account_code = account_code;
  req.asset_no = asset_no;
  req.combi_no = combi_no;

  IF2Packer* packer = ufx_util_->entrustComboQueryPacker(req);

  try
  {
    IF2UnPacker* unpacker;
    CallService(FuncEntrustComboQuery, packer, &unpacker);

    ufx_util_->showPacket( unpacker );
    
    ufx_util_->entrustComboQueryResponse(unpacker, resp);
  }
  catch( ... )
  {
    freePacker( packer );
    
    throw;
  }

  freePacker( packer );

  return;

}

void TraderServiceImpl::dealComboQuery(const std::string& account_code,
                                       const std::string& asset_no,
                                       const std::string& combi_no,
                                       DealComboQueryResponse& resp)
{
  UFX_TRACE <<"TraderServiceImpl::dealComboQuery";

  UFX_INFO <<"account code is " <<account_code <<std::endl
           <<"asset no is " <<asset_no <<std::endl
           <<"combi no is " <<combi_no;
  
  DealComboQueryRequest req;
  req.user_token = user_token_;
  req.account_code = account_code;
  req.asset_no = asset_no;
  req.combi_no = combi_no;

  IF2Packer* packer = ufx_util_->dealComboQueryPacker(req);

  try
  {
    IF2UnPacker* unpacker;
    CallService(FuncDealComboQuery, packer, &unpacker);

    ufx_util_->showPacket( unpacker );
    
    ufx_util_->dealComboQueryResponse(unpacker, resp);
  }
  catch( ... )
  {
    freePacker( packer );
    
    throw;
  }

  freePacker( packer );

  return;

}

void TraderServiceImpl::login()
{
  UFX_TRACE <<"TraderServiceImpl::login";
  
  LoginRequest req;
  req.operator_no = cfg_.operator_no;
  req.password = cfg_.password;
  req.mac_address = cfg_.mac_address;
  req.op_station = cfg_.op_station;
  req.ip_address = cfg_.ip_address;
  
  IF2Packer* packer = ufx_util_->loginPacker(req);

  try
  {
    IF2UnPacker* unpacker;
    CallService(FuncClientLogin,packer, &unpacker);

    ufx_util_->showPacket( unpacker );
    
    ufx_util_->userToken(unpacker, user_token_);
  }
  catch( ... )
  {
    freePacker( packer );
    throw;
  }

  freePacker( packer );

  return;
}


void TraderServiceImpl::CallService(int function_no, IF2Packer* req_packer, IF2UnPacker** resp_unpacker)
{
  UFX_TRACE <<"TraderServiceImpl::CallService";

  UFX_INFO <<"fucntion no: " <<function_no;

  int ret = ufx_connection_->SendBiz(function_no, req_packer);
  if (ret>0 )
  {
    void* recv_msg;
    ret = ufx_connection_->RecvBiz(ret, &recv_msg, cfg_.receiver_timeout);
    UFX_DEBUG <<"receiver response code: " <<ret;

    switch(ret)
    {
      case 0:
      case 1:

        (*resp_unpacker) = (IF2UnPacker*)recv_msg;

        ufx_util_->checkErrorInfo(*resp_unpacker);

        if((*resp_unpacker)->GetDatasetCount() > 1) (*resp_unpacker)->SetCurrentDatasetByIndex(1);
        break;
        
      case 2:
        ufx_util_->throwError( (char*)recv_msg );
        break;
        
      default:
        ufx_util_->throwError(ufx_connection_, "receive error", ret);
        break;
    }
  }
  else
  {
    ufx_util_->throwError(ufx_connection_, "send error", ret);
  }

  return ;
}


void TraderServiceImpl::freePacker(IF2Packer* packer)
{
  packer->FreeMem(packer->GetPackBuf());
  packer->Release();

  return;
}

// util function

TraderService* TraderService::createService(const UFXCfg& cfg)
{
  return new TraderServiceImpl(cfg);
}


};  // namespace ufx
