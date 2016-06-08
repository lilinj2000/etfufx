#ifndef ETF_CONFIG_HH
#define ETF_CONFIG_HH

#include "TraderService.hh"

namespace etf
{

typedef struct
{
  std::string addr_rep;
  std::string addr_pub;
  std::string account_code;
  std::string asset_no;
  std::string combi_no;
  
  std::string log_cfg;
}ETFCfg;

class ETFConfig
{
 public:
  
  ETFConfig(int argc=0, char* argv[]=NULL);
  ~ETFConfig();

  const ETFCfg& etfCfg() const
  {
    return etf_cfg_;
  }

  const ufx::UFXCfg& ufxCfg() const
  {
    return ufx_cfg_;
  }

 private:
  ETFCfg etf_cfg_;
  
  ufx::UFXCfg ufx_cfg_;
};

}  // namespace etf


#endif // ETF_CONFIG_HH_
