#ifndef ZMQ_PUB_SERVICE_HH
#define ZMQ_PUB_SERVICE_HH

#include <iostream>
#include "boost/scoped_ptr.hpp"
#include "boost/thread.hpp"

#include "zmq.h"

class ZMQPubService
{
 public:
  ZMQPubService(const std::string& addr_pub):
      addr_pub_(addr_pub),
      zmq_ctx_(NULL),
      zmq_pub_(NULL),
      done_(false)
  {
    zmq_ctx_ = zmq_ctx_new();
    
    zmq_pub_ = zmq_socket(zmq_ctx_, ZMQ_PUB);

    int ret = zmq_bind(zmq_pub_, addr_pub_.data());
    assert( ret==0 );

    recv_thread_.reset(new boost::thread(&ZMQPubService::sendData, this));
  }
  
  ~ZMQPubService()
  {
    done_ = true;

    zmq_close( zmq_pub_ );

    recv_thread_->join();
  }

  void stop()
  {
    done_ = true;

    // zmq_close( zmq_pub_ );

    recv_thread_->join();
  }

  void sendData()
  {
    std::cout <<"sendData()" <<std::endl;

    std::string data = "test data for pub ...";
    
    while(!done_)
    {
      std::cout <<"send data: " <<data <<std::endl;
      int ret = zmq_send_const(zmq_pub_, data.data(), data.length(), 0);
      assert(ret!=-1);

      sleep(1);
    }
  }


 private:

  std::string addr_pub_;
  
  void * zmq_ctx_;
  void * zmq_pub_ ;

  boost::scoped_ptr<boost::thread> recv_thread_;

  volatile bool done_;
};

#endif
