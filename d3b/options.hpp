
#ifndef D3B_OPTIONS_HPP_
#define D3B_OPTIONS_HPP_

class std::string;

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
  struct option_as
  {
    static T get(const std::string &arg)
    {
      return T{};
    }
  };

  ///////////////////////////////////////////////////////////////////
  template <>
  struct option_as<std::string>
  {
    static std::string get(const std::string &arg)
    {
      return detail::get_string_option(arg);
    }
  };

  ///////////////////////////////////////////////////////////////////
  template <>
  struct option_as<uint32_t>
  {
    static uint32_t get(const std::string &arg)
    {
      return detail::get_uint32_option(arg);
    }
  };
}

#endif // D3B_OPTIONS_HPP_
