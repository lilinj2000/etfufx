#ifndef UFX_DEF_HH
#define UFX_DEF_HH

namespace ufx
{
#define FuncClientLogin                10001
#define FuncDepositComboQuery          34003
#define FuncPositionComboQuery         35001
#define FuncEntrustComboQuery          35006
#define FuncDealComboQuery             35007

typedef struct
{
  std::string operator_no;
  std::string password;
  std::string mac_address;
  std::string op_station;
  std::string ip_address;
}LoginRequest;

typedef struct
{
  std::string user_token;
  std::string account_code;
  std::string asset_no;
  std::string combi_no;
}DepositComboQueryRequest;

typedef struct
{
  std::string user_token;
  std::string account_code;
  std::string asset_no;
  std::string combi_no;
}PositionComboQueryRequest;

typedef struct
{
  std::string user_token;
  std::string account_code;
  std::string asset_no;
  std::string combi_no;
}EntrustComboQueryRequest;

typedef struct
{
  std::string user_token;
  std::string account_code;
  std::string asset_no;
  std::string combi_no;
}DealComboQueryRequest;



};  // namespace ufx

#endif
