#include <iostream>

#include <boost/program_options.hpp>

#include "options.hpp"

namespace po = boost::program_options;

namespace d3b
{
  namespace
  {
    po::variables_map vm_;
    po::options_description desc_;
  }

  namespace detail
  {
    //////////////////////////////////////////////////////////////////
    uint32_t get_uint32_option(const std::string &arg)
    {
      return vm_[arg.c_str()].as<uint32_t>();
    }

    //////////////////////////////////////////////////////////////////
    std::string get_string_option(const std::string &arg)
    {
      return vm_[arg.c_str()].as<std::string>();
    }

    po::options_description setup_program_options()
    {
      po::options_description desc("Allowed options");
      desc.add_options()
        ("help", "produce help message")
        ("input", po::value<std::string>(), "input file")
        ("output", po::value<std::string>(), "output file");

      return desc;
    }
  }
  
  //////////////////////////////////////////////////////////////////
  void parse_command_options(int argc, char* argv[])
  {
    const auto desc = detail::setup_program_options();

    po::store(po::parse_command_line(argc, argv, desc), vm_);
    po::notify(vm_);
  }

  //////////////////////////////////////////////////////////////////
  bool help_option_specified()
  {
    if (vm_.count("help"))
    {
      std::cout << detail::setup_program_options() << std::endl;
      return true;
    }
    return false;
  }
}
