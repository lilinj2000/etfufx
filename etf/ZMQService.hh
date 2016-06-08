#ifndef ZMQ_SERVICE_HH
#define ZMQ_SERVICE_HH

#include "ETFConfig.hh"
#include <memory>

namespace etf
{

class ZMQService
{
 public:
  
  ZMQService(int argc, char* argv[]);

  ~ZMQService(){}

  void run();

 protected:
  
  void qryAccount();

  void qryPosition();

  void qryOrder();

  void qryTrade();

  void pubMsg(const std::string& msg);

 private:

  ETFCfg etf_cfg_;
  std::auto_ptr<ufx::TraderService> ufx_service_;

  void* zmq_ctx_;
  void* zmq_rep_;
  void* zmq_pub_;
};

};  // namespace etf

#endif  // ZMQ_SERVICE_HH
