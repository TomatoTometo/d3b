
#ifndef D3B_MANAGER_HPP_
#define D3B_MANAGER_HPP_

#include <map>
#include <string>
#include <vector>

#include "types.hpp"
#include "db_interface.hpp"

namespace d3b
{
  class DBManager
  {
    public:
      
      //////////////////////////////////////////////////////////////////
      DBManager(std::unique_ptr<DbInterface> db_interface);

      //////////////////////////////////////////////////////////////////
      ~DBManager() = default;

      //////////////////////////////////////////////////////////////////
      bool init(const std::string& d3b_location);

      //////////////////////////////////////////////////////////////////
      // void create();

      //////////////////////////////////////////////////////////////////
      void sync();

      //////////////////////////////////////////////////////////////////
      void update();

      //////////////////////////////////////////////////////////////////
      void add_entry(const std::string& entry, const std::vector<std::string>& tags = {});

    private:
      
      std::unique_ptr<DbInterface> db_interface_;

      std::vector<D3bEntry> db_;
      std::vector<std::string> updates_; /// @todo make this a std::pair ? first is index, second is actual update

      std::map<std::string, D3bEntry*> db_map_;

  };
}

#endif // D3B_MANAGER_HPP_
