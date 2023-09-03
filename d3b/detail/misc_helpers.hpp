
#ifndef D3B_DETAIL_HELPERS_HPP_
#define D3B_DETAIL_HELPERS_HPP_

#include <algorithm>
#include <string>
#include <sstream>

#include <boost/uuid/detail/sha1.hpp>
#include <boost/tokenizer.hpp>

#include "d3b/types.hpp"

namespace d3b
{

namespace detail
{

//////////////////////////////////////////////////////////////////
inline bool to_bool(std::string str) 
{
  std::for_each(str.begin(), str.end(), [](char& c){ return std::tolower(c); });
  return (str == "true");
}

//////////////////////////////////////////////////////////////////
inline std::string to_str(const bool b)
{
  return (b) ? "true" : "false";
}

//////////////////////////////////////////////////////////////////
inline std::string hash1(const std::string& str, uint32_t hash_length = 8)
{
  const uint32_t digest_size = 5;
  hash_length = ( hash_length > (digest_size * sizeof(unsigned int))) ? (digest_size * sizeof(unsigned int)) : hash_length;

  boost::uuids::detail::sha1 sha1;
  sha1.process_bytes(str.data(), str.size());

  uint32_t digest[digest_size];
  sha1.get_digest(digest);

  std::stringstream strout;
  for (uint32_t i = 0; i < digest_size; ++i) 
  {
    strout << std::hex << digest[i];
  }
  return strout.str().substr(0,hash_length);
}

//////////////////////////////////////////////////////////////////
inline std::string to_str(const D3bEntry& entry) 
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
inline D3bEntry to_D3bEntry(const std::string& str) 
{
  using tokenizer = boost::tokenizer<boost::char_separator<char>>;

  const tokenizer tokens(str, boost::char_separator<char>(";"));

  const bool has_tags = (std::distance(tokens.begin(), tokens.end()) > 4);

  auto token_itr = tokens.begin();

  D3bEntry entry;

  entry.entry_hash = (*token_itr);            token_itr++;
  entry.compressed = to_bool((*token_itr));   token_itr++;
  entry.filepah = (*token_itr);               token_itr++;
  entry.file_hash = (*token_itr);             token_itr++;
  
  if (has_tags)
  {
    const tokenizer tags(*token_itr, boost::char_separator<char>(","));
  
    entry.tags = std::vector<std::string>(tags.begin(), tags.end());
  }

  return entry;
}

}

}

#endif // D3B_DETAIL_HELPERS_HPP_
