#ifndef TRADER_SERVICE_HH
#define TRADER_SERVICE_HH

#include <string>
#include <vector>

namespace ufx
{

typedef struct
{
  std::string operator_no;
  std::string password;
  std::string mac_address;
  std::string op_station;
  std::string ip_address;

  char entrust_way;

  int connection_timeout;
  int receiver_timeout;
  
  std::string t2sdk_cfg;
}UFXCfg;

typedef struct
{
  double occupy_deposit_balance;
  double enable_deposit_balance;
}DepositComboQueryResponse;

typedef struct
{
  std::string stock_code;
  std::string position_flag;
  long long current_amount;
}SinglePositionInfo;
typedef std::vector<SinglePositionInfo> PositionComboQueryResponse;

typedef struct
{
  std::string stock_code;
  std::string entrust_direction;
  std::string futures_direction;
  double entrust_price;
  long long entrust_amount;
  std::string entrust_status;
  long long deal_amount;
}SingleEntrustInfo;
typedef std::vector<SingleEntrustInfo> EntrustComboQueryResponse;

typedef struct
{
  std::string stock_code;
  std::string entrust_direction;
  std::string futures_direction;
  long long deal_amount;
  double deal_price;
  long long deal_time;
}SingleDealInfo;
typedef std::vector<SingleDealInfo> DealComboQueryResponse;

class TraderService
{
 public:

  virtual void depositComboQuery(const std::string& account_code,
                                 const std::string& asset_no,
                                 const std::string& combi_no,
                                 DepositComboQueryResponse& resp) = 0;

  virtual void positionComboQuery(const std::string& account_code,
                                  const std::string& asset_no,
                                  const std::string& combi_no,
                                  PositionComboQueryResponse& resp) = 0;

  virtual void entrustComboQuery(const std::string& account_code,
                                 const std::string& asset_no,
                                 const std::string& combi_no,
                                 EntrustComboQueryResponse& resp) = 0;

  virtual void dealComboQuery(const std::string& account_code,
                              const std::string& asset_no,
                              const std::string& combi_no,
                              DealComboQueryResponse& resp) = 0;


  static TraderService* createService(const UFXCfg& cfg);

};

}  // namespace ufx

#endif
