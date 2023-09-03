
#ifndef D3B_DB_INTERFACE_HPP_
#define D3B_DB_INTERFACE_HPP_

#include <string>
#include <vector>

#include "types.hpp"

namespace d3b
{

class DbInterface
{
public:

  //////////////////////////////////////////////////////////////////
  virtual ErrorCode init(const std::string&) = 0;
  //////////////////////////////////////////////////////////////////
  virtual ErrorCode read(std::vector<std::string>&) = 0;
  //////////////////////////////////////////////////////////////////
  virtual ErrorCode sync(const std::vector<D3bEntry>& entries) = 0;
};

}

#endif // D3B_DB_INTERFACE_HPP_
