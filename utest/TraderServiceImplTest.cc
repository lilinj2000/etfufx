#include <memory>

#include "ufx/TraderServiceImpl.hh"
#include "etf/ETFConfig.hh"
#include "gtest/gtest.h"

namespace ufx
{

class TraderServiceImplTest : public ::testing::Test
{
public:

  void SetUp()
  {
    etf::ETFConfig cfg;
  
    const UFXCfg& ufx_cfg = cfg.ufxCfg();
    service_.reset( TraderService::createService(ufx_cfg) );

    const etf::ETFCfg& etf_cfg = cfg.etfCfg();

    account_code_ = etf_cfg.account_code;
    asset_no_ = etf_cfg.asset_no;
    combi_no_ = etf_cfg.combi_no;
  }

  TraderServiceImplTest()
  {
  }
  
protected:
  std::string account_code_;
  std::string asset_no_;
  std::string combi_no_;

  std::auto_ptr<TraderService> service_;

};

TEST_F(TraderServiceImplTest, depositComboQueryTest)
{

  DepositComboQueryResponse resp;
  service_->depositComboQuery(account_code_, asset_no_, combi_no_, resp);

  ASSERT_TRUE( true );

}

TEST_F(TraderServiceImplTest, positionComboQueryTest)
{

  PositionComboQueryResponse resp;
  service_->positionComboQuery(account_code_, asset_no_,
                               combi_no_, resp);

  ASSERT_TRUE( true );
}

TEST_F(TraderServiceImplTest, entrustComboQueryTest)
{
  EntrustComboQueryResponse resp;
  service_->entrustComboQuery(account_code_, asset_no_,
                              combi_no_, resp);

  ASSERT_TRUE( true );
}

TEST_F(TraderServiceImplTest, dealComboQueryTest)
{
  DealComboQueryResponse resp;
  service_->dealComboQuery(account_code_, asset_no_,
                              combi_no_, resp);

  ASSERT_TRUE( true );
}

}  // namespace ufx
