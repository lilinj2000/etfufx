#include "UFXUtil.hh"
#include "UFXLog.hh"

#include <string>
#include <sstream>
#include <iomanip>

#include "t2sdk_interface.h"

namespace ufx
{

IF2Packer* UFXUtil::loginPacker(const LoginRequest& req)
{
  IF2Packer* packer = NewPacker(2);
  
  packer->AddRef();
  packer->BeginPack();
  packer->AddField("operator_no",     'S',16, 0);
  packer->AddField("password",        'S',32, 0);
  packer->AddField("mac_address",     'S',255,0);
  packer->AddField("op_station",      'S',255,0);
  packer->AddField("ip_address",      'S',32, 0);
  packer->AddStr(req.operator_no.data());
  packer->AddStr(req.password.data());
  packer->AddStr(req.mac_address.data());
  packer->AddStr(req.op_station.data());
  packer->AddStr(req.ip_address.data());
  packer->EndPack();
  
  return packer;
}

IF2Packer* UFXUtil::depositComboQueryPacker(const DepositComboQueryRequest& req)
{
  IF2Packer* packer = NewPacker(2);
  
  packer->AddRef();
  packer->BeginPack();
  packer->AddField("user_token",     'S', 40, 0);
  packer->AddField("account_code",   'S', 18, 0);
  if( !req.asset_no.empty() )
      packer->AddField("asset_no",   'S', 16, 0);
  else if( !req.combi_no.empty() )
    packer->AddField("combi_no",   'S', 9, 0);
  else
    throwError("asset_no and combi_no, both not exist");
  
  packer->AddStr(req.user_token.data());
  packer->AddStr(req.account_code.data());
  if( !req.asset_no.empty() )
      packer->AddStr(req.asset_no.data());
  else
    packer->AddStr(req.combi_no.data());
  
  packer->EndPack();
  
  return packer;
}

IF2Packer* UFXUtil::positionComboQueryPacker(const PositionComboQueryRequest& req)
{
  IF2Packer* packer = NewPacker(2);
  
  packer->AddRef();
  packer->BeginPack();
  packer->AddField("user_token",     'S', 40, 0);
  packer->AddField("account_code",   'S', 18, 0);
  if( !req.asset_no.empty() )
      packer->AddField("asset_no",   'S', 16, 0);
  else if( !req.combi_no.empty() )
    packer->AddField("combi_no",   'S', 9, 0);
  else
    throwError("asset_no and combi_no, both not exist");
  
  packer->AddStr(req.user_token.data());
  packer->AddStr(req.account_code.data());
  if( !req.asset_no.empty() )
      packer->AddStr(req.asset_no.data());
  else
    packer->AddStr(req.combi_no.data());
  
  packer->EndPack();
  
  return packer;
}

IF2Packer* UFXUtil::entrustComboQueryPacker(const EntrustComboQueryRequest& req)
{
  IF2Packer* packer = NewPacker(2);
  
  packer->AddRef();
  packer->BeginPack();
  packer->AddField("user_token",     'S', 40, 0);
  packer->AddField("account_code",   'S', 18, 0);
  if( !req.asset_no.empty() )
      packer->AddField("asset_no",   'S', 16, 0);
  else if( !req.combi_no.empty() )
    packer->AddField("combi_no",   'S', 9, 0);
  else
    throwError("asset_no and combi_no, both not exist");
  
  packer->AddStr(req.user_token.data());
  packer->AddStr(req.account_code.data());
  if( !req.asset_no.empty() )
      packer->AddStr(req.asset_no.data());
  else
    packer->AddStr(req.combi_no.data());
  
  packer->EndPack();
  
  return packer;
}

IF2Packer* UFXUtil::dealComboQueryPacker(const DealComboQueryRequest& req)
{
  IF2Packer* packer = NewPacker(2);
  
  packer->AddRef();
  packer->BeginPack();
  packer->AddField("user_token",     'S', 40, 0);
  packer->AddField("account_code",   'S', 18, 0);
  if( !req.asset_no.empty() )
      packer->AddField("asset_no",   'S', 16, 0);
  else if( !req.combi_no.empty() )
    packer->AddField("combi_no",   'S', 9, 0);
  else
    throwError("asset_no and combi_no, both not exist");
  
  packer->AddStr(req.user_token.data());
  packer->AddStr(req.account_code.data());
  if( !req.asset_no.empty() )
      packer->AddStr(req.asset_no.data());
  else
    packer->AddStr(req.combi_no.data());
  
  packer->EndPack();
  
  return packer;
}

void UFXUtil::userToken(IF2UnPacker* unpacker, std::string& user_token)
{
  if( unpacker->FindColIndex("user_token")>=0 )
  {
    user_token = unpacker->GetStr("user_token");

    UFX_INFO <<"user token: " <<user_token;
  }
  else
  {
    throwError("user_token not exist in response message");
  }

  return;
}

void UFXUtil::depositComboQueryResponse(IF2UnPacker* unpacker,
                                        DepositComboQueryResponse& resp)
{
  if( unpacker->FindColIndex("occupy_deposit_balance")>=0 )
  {
    resp.occupy_deposit_balance = unpacker->GetDouble("occupy_deposit_balance");

    UFX_INFO <<"occupy deposit balance: " <<resp.occupy_deposit_balance;
  }
  else
  {
    throwError("occupy_deposit_balance not exist in response message");
  }

  if( unpacker->FindColIndex("enable_deposit_balance")>=0 )
  {
    resp.enable_deposit_balance = unpacker->GetDouble("enable_deposit_balance");

    UFX_INFO <<"enable deposit balance: " <<resp.enable_deposit_balance;
  }
  else
  {
    throwError("enable_deposit_balance not exist in response message");
  }

  return;
  
}

void UFXUtil::positionComboQueryResponse(IF2UnPacker* unpacker,
                                         PositionComboQueryResponse& resp)
{
  for(int i=0; i<unpacker->GetDatasetCount(); i++ )
  {
    unpacker->SetCurrentDatasetByIndex(i);

    for(int j=0; j<unpacker->GetRowCount(); j++)
    {
      SinglePositionInfo position;

      for(int k=0; k<unpacker->GetColCount(); k++)
      {
        std::string col_name = unpacker->GetColName(k);
        if( col_name=="stock_code" )
        {
          position.stock_code = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="position_flag" )
        {
          position.position_flag = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="current_amount" )
        {
          position.current_amount = unpacker->GetIntByIndex(k);
        }
      }  // end col count

      if( !position.stock_code.empty() )
        resp.push_back( position );
    }  // end row count
  }    // end data set count

  return;
}

void UFXUtil::entrustComboQueryResponse(IF2UnPacker* unpacker,
                                        EntrustComboQueryResponse& resp)
{
  for(int i=0; i<unpacker->GetDatasetCount(); i++ )
  {
    unpacker->SetCurrentDatasetByIndex(i);

    for(int j=0; j<unpacker->GetRowCount(); j++)
    {
      SingleEntrustInfo entrust;
      
      for(int k=0; k<unpacker->GetColCount(); k++)
      {
        std::string col_name = unpacker->GetColName(k);
        if( col_name=="stock_code" )
        {
          entrust.stock_code = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="entrust_direction" )
        {
          entrust.entrust_direction = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="futures_direction" )
        {
          entrust.futures_direction = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="entrust_price" )
        {
          entrust.entrust_price = unpacker->GetDoubleByIndex(k);
        }
        else if( col_name=="entrust_amount" )
        {
          entrust.entrust_amount = unpacker->GetIntByIndex(k);
        }
        else if( col_name=="entrust_status" )
        {
          entrust.entrust_status = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="deal_amount" )
        {
          entrust.deal_amount = unpacker->GetIntByIndex(k);
        }
      }  // end col count

      if( !entrust.stock_code.empty() )
        resp.push_back( entrust );
    }  // end row count
  }    // end data set count

  return;
}

void UFXUtil::dealComboQueryResponse(IF2UnPacker* unpacker,
                                     DealComboQueryResponse& resp)
{
  for(int i=0; i<unpacker->GetDatasetCount(); i++ )
  {
    unpacker->SetCurrentDatasetByIndex(i);

    for(int j=0; j<unpacker->GetRowCount(); j++)
    {
      SingleDealInfo deal;

      for(int k=0; k<unpacker->GetColCount(); k++)
      {
        std::string col_name = unpacker->GetColName(k);
        if( col_name=="stock_code" )
        {
          deal.stock_code = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="entrust_direction" )
        {
          deal.entrust_direction = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="futures_direction" )
        {
          deal.futures_direction = unpacker->GetStrByIndex(k);
        }
        else if( col_name=="deal_amount" )
        {
          deal.deal_amount = unpacker->GetIntByIndex(k);
        }
        else if( col_name=="deal_price" )
        {
          deal.deal_price = unpacker->GetDoubleByIndex(k);
        }
        else if( col_name=="deal_time" )
        {
          deal.deal_time = unpacker->GetIntByIndex(k);
        }
      }  // end col count

      if( !deal.stock_code.empty() )
        resp.push_back( deal );
      
    }  // end row count
  }    // end data set count

  return;
}

void UFXUtil::checkErrorInfo(IF2UnPacker* resp_unpacker)
{
  std::string error_msg;
  int error_code = resp_unpacker->GetInt("ErrorCode") ;
  
  if(resp_unpacker->GetStr("ErrorMsg"))
  {
    error_msg  = resp_unpacker->GetStr("ErrorMsg");
  }

  if( error_code!=0 )
  {
    std::stringstream sstream;
    sstream <<"error code: " <<error_code <<std::endl
            <<"error msg: " <<error_msg;
    
    throwError( sstream.str() );
  }

  return;
}


void UFXUtil::throwError(const std::string& hint)
{
  UFX_ERROR <<hint;
  
  throw std::runtime_error(hint);
}

void UFXUtil::throwError(CConnectionInterface* conn,
                         const std::string& hint, int error_code)
{
  std::stringstream error_stream;
  error_stream <<hint <<std::endl
               <<" error code: " <<error_code <<std::endl
               <<" error msg: "
               <<conn->GetErrorMsg(error_code);

  UFX_ERROR <<error_stream.str();
  
  throw std::runtime_error(error_stream.str());
}


void UFXUtil::showPacket(IF2UnPacker *unpack)
{
  std::stringstream pack_stream;
  
  int i = 0, t = 0, j = 0, k = 0;

  for (i = 0; i < unpack->GetDatasetCount(); ++i)
  {
    pack_stream <<"Record Set: " <<i+1 <<"/" <<unpack->GetDatasetCount() <<std::endl;
    
    unpack->SetCurrentDatasetByIndex(i);

    for (j = 0; j < (int)unpack->GetRowCount(); ++j)
    {
      pack_stream <<"\t" <<j+1 <<"/" <<unpack->GetRowCount() <<" record: " <<std::endl;

      for (k = 0; k < unpack->GetColCount(); ++k)
      {
        switch (unpack->GetColType(k))
        {
          case 'I':
            pack_stream <<"\t [INT] " <<unpack->GetColName(k) <<" = " <<unpack->GetIntByIndex(k) <<std::endl;
            break;

          case 'C':
            pack_stream <<"\t [CHAR] " <<unpack->GetColName(k) << " = " <<unpack->GetCharByIndex(k) <<std::endl;
            break;

          case 'S':
            if (NULL != strstr((char *)unpack->GetColName(k),"password"))
            {
              pack_stream <<"\t [STRING] " <<unpack->GetColName(k) <<" = ******" <<std::endl;
            }
            else
            {
              pack_stream <<"\t [STRING] " <<unpack->GetColName(k) <<" = " <<unpack->GetStrByIndex(k) <<std::endl;
            }
            break;

          case 'F':
            pack_stream <<"\t [NUMBER] " <<unpack->GetColName(k) <<" = " <<unpack->GetDoubleByIndex(k) <<std::endl;
            break;

          case 'R':
            {
              int nLength = 0;
              void *lpData = unpack->GetRawByIndex(k, &nLength);
              switch(nLength){
                case 0:
                  pack_stream <<"\t [DATA] " <<unpack->GetColName(k) <<" = (N/A)";
                  break;
                  
                default:
                  pack_stream <<"\t [DATA] " <<unpack->GetColName(k) <<" = 0x";

                  for(t = nLength; t < 11; t++)
                  {
                    pack_stream <<"   ";
                  }
                  unsigned char *p = (unsigned char *)lpData;
                  for(t = 0; t < nLength; t++)
                  {
                    pack_stream <<std::setw(3) <<std::hex <<*p++;
                  }
                  pack_stream <<std::endl;
                  break;						
              }
              break;
            }

          default:
            pack_stream <<"unknow data type." <<std::endl;
            break;
        }
      }

      pack_stream <<std::endl;
      unpack->Next();
    }

    pack_stream <<std::endl;
  }

  UFX_PDU <<pack_stream.str();
}


};  // namespace ufx
