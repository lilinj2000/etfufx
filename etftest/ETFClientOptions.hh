#ifndef ETF_CLIENT_OPTIONS_HH
#define ETF_CLIENT_OPTIONS_HH

#include "soil/Config.hh"

#include <string>

namespace etf
{
namespace po = boost::program_options;

class ETFClientOptions : public soil::Options
{
 public:

  ETFClientOptions();
  
  virtual ~ETFClientOptions();

  virtual po::options_description* cmdOptions();

  virtual po::options_description* configOptions();
  
  std::string addr_req;
  std::string addr_sub;;

 private:

  boost::program_options::options_description options_;
};

}  // namespace etf


#endif 
