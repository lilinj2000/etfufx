#include "ETFClientOptions.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace etf
{

ETFClientOptions::ETFClientOptions():
    options_("ETFClientOptions")
{
  namespace po = boost::program_options;

  options_.add_options()
      ("etf.addr_req", po::value<std::string>(&addr_req), 
       "addr req")
      ("etf.addr_sub", po::value<std::string>(&addr_sub), 
       "addr sub")
      ;

  return;
  
}

ETFClientOptions::~ETFClientOptions()
{
}

po::options_description* ETFClientOptions::cmdOptions()
{
  return NULL;
}

po::options_description* ETFClientOptions::configOptions()
{
  return &options_;
}

};  // namespace etf
