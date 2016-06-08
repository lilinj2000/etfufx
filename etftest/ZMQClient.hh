#ifndef ZMQ_CLIENT_HH
#define ZMQ_CLIENT_HH

#include "ETFClientOptions.hh"
#include <memory>

#include "boost/thread.hpp"

namespace etf
{

class ZMQClient
{
 public:
  
  ZMQClient(int argc, char* argv[]);

  ~ZMQClient();

  void run();

 protected:

  void receivePubData();
  
 private:

  ETFClientOptions etf_client_options_;

  bool done_;

  void* zmq_ctx_;
  void* zmq_req_;
  void* zmq_sub_;

  std::unique_ptr<boost::thread> receive_pub_thread_;
};

};  // namespace etf

#endif  // ZMQ_CLIENT_HH
