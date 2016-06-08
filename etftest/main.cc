#include <memory>
#include <iostream>
#include "ZMQClient.hh"

int main(int argc, char* argv[])
{
  try
  {

    std::auto_ptr<etf::ZMQClient> client( new etf::ZMQClient(argc, argv) );

    client->run();
  }
  catch(std::exception& e )
  {
    std::cout <<e.what();
  }

  return 0;
}
