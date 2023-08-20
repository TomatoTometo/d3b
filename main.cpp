
#include <windows.h>

#include <iostream>

#include "d3b/options.hpp"

int main(int argc, char** argv)
{
  d3b::parse_command_options(argc, argv);
  
  if(d3b::help_option_specified())
  {
    return -0;
  }

  Sleep(10000);

  return 0;
}
