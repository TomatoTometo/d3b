
#include <windows.h>

#include <iostream>

#include "d3b/options.hpp"
#include "d3b/manager.hpp"

int main(int argc, char** argv)
{
  d3b::parse_command_options(argc, argv);
  
  if(d3b::help_option_specified())
  {
    return -0;
  }

  const auto d3b_file = d3b::option_as<std::string>::get("d3b-database");

  std::cout << "d3b_file is " << d3b_file.c_str() << std::endl;

  d3b::DBManager manager(d3b_file.c_str());

  if(!manager.init())
  {
    std::cout << "Failed to initialize database" << std::endl;
  }

  return 0;
}
