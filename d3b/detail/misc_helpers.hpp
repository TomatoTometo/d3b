
#ifndef D3B_DETAIL_HELPERS_HPP_
#define D3B_DETAIL_HELPERS_HPP_

#include <boost/uuid/detail/sha1.hpp>
#include <algorithm>
#include <string>
#include <sstream>

#include "d3b/types.hpp"

namespace d3b
{

namespace detail
{

//////////////////////////////////////////////////////////////////
bool to_bool(std::string str) 
{
  std::for_each(str.begin(), str.end(), [](char& c){ return std::tolower(c); });
  return (str == "true");
}

//////////////////////////////////////////////////////////////////
std::string to_str(const bool b) 
{
  return (b) ? "true" : "false";
}

//////////////////////////////////////////////////////////////////
std::string hash1(const std::string& str) 
{
  boost::uuids::detail::sha1 sha1;
  sha1.process_bytes(str.data(), str.size());
  
  uint32_t digest[5];
  sha1.get_digest(digest);

  std::stringstream strout;
  for (uint32_t i = 0; i < 5; ++i) 
  {
    strout << std::hex << digest[i];
  }
  return strout.str().substr(0,8);
}

//////////////////////////////////////////////////////////////////
std::string to_str(const D3bEntry& entry) 
{
  std::string str;

  str =  to_str(entry.compressed) + ";" +
          entry.filepah           + ";" +
          entry.file_hash         + ";";

  std::string tags;

  for (const auto& tag : entry.tags)
  {
    tags += (tag + ",");
  }

  // if (tags.empty())
  // {
  //   tags = " "; // @todo resolve this case
  // }

  str += tags;

  return hash1(str) + ";" + str;
}

//////////////////////////////////////////////////////////////////
D3bEntry to_D3bEntry(const std::string& str) 
{
  D3bEntry e;
  return e;
}

}

}

#endif // D3B_DETAIL_HELPERS_HPP_
