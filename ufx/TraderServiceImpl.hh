#ifndef TRADER_SERVICE_IMPL_HH
#define TRADER_SERVICE_IMPL_HH

#include "TraderService.hh"
#include "UFXDef.hh"
#include "UFXUtil.hh"
#include "t2sdk_interface.h"

#include <string>
#include <memory>

namespace ufx
{

class TraderServiceImpl : public TraderService
{
 public:
  TraderServiceImpl(const UFXCfg& cfg);

  ~TraderServiceImpl();

  virtual void depositComboQuery(const std::string& account_code,
                                 const std::string& asset_no,
                                 const std::string& combi_no,
                                 DepositComboQueryResponse& resp);

  virtual void positionComboQuery(const std::string& account_code,
                                  const std::string& asset_no,
                                  const std::string& combi_no,
                                  PositionComboQueryResponse& resp);

  virtual void entrustComboQuery(const std::string& account_code,
                                 const std::string& asset_no,
                                 const std::string& combi_no,
                                 EntrustComboQueryResponse& resp);

  virtual void dealComboQuery(const std::string& account_code,
                              const std::string& asset_no,
                              const std::string& combi_no,
                              DealComboQueryResponse& resp);

  
 protected:
  // function 
  void login();

  void CallService(int function_no, IF2Packer* req_packer, IF2UnPacker** resp_unpacker);
  
  // util function
  void freePacker(IF2Packer* packer);
  
 private:

  UFXCfg cfg_;
  
  CConfigInterface* ufx_config_;
  CConnectionInterface* ufx_connection_;

  int subsystem_no_;

  std::string user_token_;

  std::auto_ptr<UFXUtil> ufx_util_;
};

};  // namespace ufx

#endif
