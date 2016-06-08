#include "ETFConfig.hh"
#include "ETFLog.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace etf
{

ETFConfig::ETFConfig(int argc, char* argv[])
{
  namespace po = boost::program_options;
  std::string config_file;
  
  // the options will be allowed only on command line
  po::options_description cmdline_options("Command line options");
  cmdline_options.add_options()
      ("version,v", "print version string")
      ("help", "produce help message")
      ("config,c", po::value<std::string>(&config_file)->default_value("etf.cfg"),
       "name of a file of a configuration.")
      ;

  // the options will be allowed only on config file
  po::options_description etf_config("ETFConfig");
  etf_config.add_options()
      ("etf.addr_rep", po::value<std::string>(&etf_cfg_.addr_rep), 
       "addr rep")
      ("etf.addr_pub", po::value<std::string>(&etf_cfg_.addr_pub), 
       "addr pub")
      ("etf.account_code", po::value<std::string>(&etf_cfg_.account_code), 
       "account code")
      ("etf.asset_no", po::value<std::string>(&etf_cfg_.asset_no), 
       "asset no")
      ("etf.combi_no", po::value<std::string>(&etf_cfg_.combi_no), 
       "combi no")
      ("etf.log_cfg", po::value<std::string>(&etf_cfg_.log_cfg), 
       "log config file")
      ;
  
  // the options will be allowed only on config file
  po::options_description ufx_config("UFXConfig");
  ufx_config.add_options()
      ("ufx.operator_no", po::value<std::string>(&ufx_cfg_.operator_no), 
       "operator no")
      ("ufx.password", po::value<std::string>(&ufx_cfg_.password), 
       "password")
      ("ufx.mac_address", po::value<std::string>(&ufx_cfg_.mac_address), 
       "mac address")
      ("ufx.op_station", po::value<std::string>(&ufx_cfg_.op_station), 
       "op station")
      ("ufx.ip_address", po::value<std::string>(&ufx_cfg_.ip_address), 
       "ip address")
      ("ufx.entrust_way", po::value<char>(&ufx_cfg_.entrust_way), 
       "entrust way")
      ("ufx.connection_timeout", po::value<int>(&ufx_cfg_.connection_timeout), 
       "connection timeout")
      ("ufx.receiver_timeout", po::value<int>(&ufx_cfg_.receiver_timeout), 
       "receiver timeout")
      ("ufx.t2sdk_cfg", po::value<std::string>(&ufx_cfg_.t2sdk_cfg), 
       "t2sdk config file")
      ;

  po::options_description config_file_options;
  config_file_options.add(etf_config).add(ufx_config);

  // parse command line
  po::variables_map vm;
  store(po::parse_command_line(argc, argv, cmdline_options), vm);
  notify(vm);

  if (vm.count("help")) 
  {
    std::cout << cmdline_options;
    return;
  }

  std::ifstream ifs(config_file.c_str());
  if (!ifs)
  {
    throw std::runtime_error("can not open config file: " + config_file);
  }
  else
  {
    store(parse_config_file(ifs, config_file_options), vm);
    notify(vm);
  }

  // init the log
  ETF_LOG_INIT( etf_cfg_.log_cfg );
  
  return;
}

ETFConfig::~ETFConfig()
{
}

};  // namespace ufx
