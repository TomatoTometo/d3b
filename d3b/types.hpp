
#ifndef D3B_TYPES_HPP_
#define D3B_TYPES_HPP_

#include <string>
#include <vector>

namespace d3b
{
  enum class ErrorCode : std::uint32_t
  {
    ENTRY_GOOD          = 0x00000000,
    FILE_HASH_INVALID   = 0x00000001,
    ENTRY_HASH_INVALID  = 0x00000002,
    FILE_DOES_NOT_EXIST = 0x00000003
  };

  struct D3bEntry
  {
    bool compressed;
    ErrorCode entry_code;
    std::string filepah;
    std::string entry_hash;
    std::string file_hash;
    std::vector<std::string> tags;
  };

  /// ??
  struct D3bHeader
  {
    std::string hash;
    uint32_t entries;
    uint32_t longest_entry;
  };
}

#endif // D3B_TYPES_HPP_
