
#ifndef D3B_OPTIONS_HPP_
#define D3B_OPTIONS_HPP_

#include <string>

namespace d3b
{
  //////////////////////////////////////////////////////////////////
  void parse_command_options(int argc, char *argv[]);

  //////////////////////////////////////////////////////////////////
  bool help_option_specified();

  namespace detail
  {
    /////////////////////////////////////////////////////////////////
    std::string get_string_option(const std::string &arg);

    /////////////////////////////////////////////////////////////////
    uint32_t get_uint32_option(const std::string &arg);
  }

  ///////////////////////////////////////////////////////////////////
  template<typename T>
  struct options_as
  {
    static T get_argument(const std::string &arg)
    {
      return T{};
    }
  };

  ///////////////////////////////////////////////////////////////////
  template <>
  struct options_as<std::string>
  {
    static std::string get_argument(const std::string &arg)
    {
      return detail::get_string_option(arg);
    }
  };

  ///////////////////////////////////////////////////////////////////
  template <>
  struct options_as<uint32_t>
  {
    static uint32_t get_argument(const std::string &arg)
    {
      return detail::get_uint32_option(arg);
    }
  };
}

#endif // D3B_OPTIONS_HPP_
