#ifndef UFX_UTIL_HH
#define UFX_UTIL_HH

#include <string>
#include "TraderService.hh"
#include "UFXDef.hh"

class IF2Packer;
class IF2UnPacker;
class CConnectionInterface;

namespace ufx
{

class UFXUtil
{
 public:
  
  UFXUtil() {}
  
  ~UFXUtil() {}

  IF2Packer* loginPacker(const LoginRequest& req);

  IF2Packer* depositComboQueryPacker(const DepositComboQueryRequest& req);

  IF2Packer* positionComboQueryPacker(const PositionComboQueryRequest& req);

  IF2Packer* entrustComboQueryPacker(const EntrustComboQueryRequest& req);

  IF2Packer* dealComboQueryPacker(const DealComboQueryRequest& req);
  
  void userToken(IF2UnPacker* unpacker, std::string& user_token);

  void depositComboQueryResponse(IF2UnPacker* unpacker,
                                 DepositComboQueryResponse& resp);

  void positionComboQueryResponse(IF2UnPacker* unpacker,
                                  PositionComboQueryResponse& resp);

  void entrustComboQueryResponse(IF2UnPacker* unpacker,
                                 EntrustComboQueryResponse& resp);

  void dealComboQueryResponse(IF2UnPacker* unpacker,
                              DealComboQueryResponse& resp);

  void checkErrorInfo(IF2UnPacker* resp_unpacker);
  
  void throwError(CConnectionInterface* conn,
                  const std::string& hint, int error_code);
  
  void throwError(const std::string& hint);

  
  void showPacket(IF2UnPacker *unpack);

 protected:

  
 private:
};

};  // namespace ufx

#endif  // UFX_UTIL_HH
