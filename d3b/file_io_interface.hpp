
#ifndef D3B_FILE_IO_DB_HPP_
#define D3B_FILE_IO_DB_HPP_

#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "db_interface.hpp"
#include "detail/misc_helpers.hpp"
#include "types.hpp"

namespace d3b
{

class DbFileIO : public DbInterface
{
public:

  //////////////////////////////////////////////////////////////////
  ErrorCode init(const std::string& file_db) override
  {
    boost::filesystem::path path(file_db.c_str());

    if (!boost::filesystem::exists(path)) 
    {
      // @todo add return numbers
      return ErrorCode{};
    }

    file_db_loc_ = path;

    return ErrorCode{};
  }

  //////////////////////////////////////////////////////////////////
  ErrorCode read(std::vector<std::string>& v_out) override
  {
    if (file_db_loc_.empty())
    {
      return ErrorCode{};
    }

    boost::filesystem::fstream db_file(file_db_loc_, std::ios::in);

    if (db_file.is_open()) 
    {
      std::string entry_str;
      while (std::getline(db_file, entry_str)) 
      {
        v_out.push_back(entry_str);
      }

      db_file.close();
    }

    return ErrorCode{};
  }

  //////////////////////////////////////////////////////////////////
  ErrorCode sync(const std::vector<D3bEntry>& entries)
  {
    // @todo create a bak up
    if (file_db_loc_.empty())
    {
      return ErrorCode{};
    }
    
    // @todo move to create
    if (file_db_loc_.has_parent_path())
    {
      boost::filesystem::create_directories(file_db_loc_.parent_path());
    }

    boost::filesystem::ofstream outfile(file_db_loc_);

    if (!outfile.is_open()) 
    {
      return ErrorCode{};
    }
    
    for (const auto& entry : entries)
    {
      outfile << detail::to_str(entry) << std::endl;
    }

    outfile.flush();
    outfile.close();

    return ErrorCode{};
  }

private:

  boost::filesystem::path file_db_loc_;
};

}

#endif // D3B_FILE_IO_DB_HPP_
