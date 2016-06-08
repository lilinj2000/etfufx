#include <memory>
#include "ETFLog.hh"
#include "ZMQService.hh"

int main(int argc, char* argv[])
{
  try
  {

    std::auto_ptr<etf::ZMQService> service( new etf::ZMQService(argc, argv) );

    service->run();
  }
  catch(std::exception& e )
  {
    ETF_ERROR <<e.what();
  }

  return 0;
}
