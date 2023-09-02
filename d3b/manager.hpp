
#ifndef D3B_MANAGER_HPP_
#define D3B_MANAGER_HPP_

#include <string>
#include <vector>

#include "types.hpp"

namespace d3b
{
  class DBManager
  {
    public:
      
      //////////////////////////////////////////////////////////////////
      DBManager(const std::string location);

      //////////////////////////////////////////////////////////////////
      ~DBManager() = default;

      //////////////////////////////////////////////////////////////////
      bool init();

      //////////////////////////////////////////////////////////////////
      // void create();

      //////////////////////////////////////////////////////////////////
      void sync();

      //////////////////////////////////////////////////////////////////
      void update();

      //////////////////////////////////////////////////////////////////
      void add_entry(const std::string& entry, const std::vector<std::string>& tags = {});

    private:
      
      std::string d3b_location_;

      std::vector<D3bEntry> db_;
      std::vector<std::string> updates_; /// @todo make this a std::pair ? first is index, second is actual update
  };
}

#endif // D3B_MANAGER_HPP_
