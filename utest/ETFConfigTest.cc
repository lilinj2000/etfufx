#include <memory>

#include "etf/ETFConfig.hh"
#include "gtest/gtest.h"

namespace etf
{

class ETFConfigTest : public ::testing::Test
{
public:

  void SetUp()
  {
  }

protected:

};

TEST_F(ETFConfigTest, etfConfigTest)
{
  ETFConfig cfg;

  const ufx::UFXCfg& ufx_cfg = cfg.ufxCfg();

  const ETFCfg& etf_cfg = cfg.etfCfg();

  ASSERT_EQ( etf_cfg.addr_rep, "tcp://*:6555" );
  ASSERT_EQ( etf_cfg.addr_pub, "tcp://*:6556" );
  ASSERT_EQ( etf_cfg.account_code, "10002" );
  ASSERT_EQ( etf_cfg.asset_no, "" );
  ASSERT_EQ( etf_cfg.combi_no, "10002001" );
  ASSERT_EQ( etf_cfg.log_cfg, "log.cfg" );
  
  ASSERT_EQ( ufx_cfg.operator_no, "1023" );
  ASSERT_EQ( ufx_cfg.password, "00" );
  ASSERT_EQ( ufx_cfg.mac_address, "5C-26-0A-2F-82-4F" );
  ASSERT_EQ( ufx_cfg.op_station, "192.168.88.123|5C-26-0A-2F-82-4F" );
  ASSERT_EQ( ufx_cfg.ip_address, "192.168.88.123" );
  ASSERT_EQ( ufx_cfg.entrust_way, '7' );
  ASSERT_EQ( ufx_cfg.connection_timeout, 1000 );
  ASSERT_EQ( ufx_cfg.receiver_timeout, 3000 );
  ASSERT_EQ( ufx_cfg.t2sdk_cfg, "t2sdk.ini" );
  

}

}  // namespace etf
