#include <algorithm>
#include <fstream>
#include <string>
#include <iostream> // delete

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>

#include "detail/misc_helpers.hpp"
#include "manager.hpp"
#include "types.hpp"

namespace d3b
{

using tokenizer = boost::tokenizer<boost::char_separator<char>>;

//////////////////////////////////////////////////////////////////
DBManager::DBManager(const std::string d3b_location) :
  d3b_location_(std::move(d3b_location))
{

}

//////////////////////////////////////////////////////////////////
bool DBManager::init()
{
  boost::filesystem::path d3b_path(d3b_location_.c_str());

  if (!boost::filesystem::exists(d3b_path)) 
  {
    // @todo add return numbers
    return false;
  }

  boost::filesystem::fstream db_file(d3b_path, std::ios::in);

  if (db_file.is_open()) 
  {
    std::string entry_str;
    while (std::getline(db_file, entry_str)) 
    {
      const tokenizer tokens(entry_str, boost::char_separator<char>(";"));

      const bool has_tags = (std::distance(tokens.begin(), tokens.end()) > 4);

      auto token_itr = tokens.begin();

      D3bEntry entry;

      entry.entry_hash = (*token_itr);                    token_itr++;
      entry.compressed = detail::to_bool((*token_itr));   token_itr++;
      entry.filepah = (*token_itr);                       token_itr++;
      entry.file_hash = (*token_itr);                     token_itr++;

      // @todo check hash is good
      
      if (has_tags)
      {
        const tokenizer tags(*token_itr, boost::char_separator<char>(","));
      
        entry.tags = std::vector<std::string>(tags.begin(), tags.end());
      }


      db_.push_back(entry);
    }
  
    db_file.close();

    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////////
void DBManager::sync()
{
  // @todo create a bak up
  boost::filesystem::path d3b_path(d3b_location_.c_str());

  // if (!boost::filesystem::exists(d3b_path)) 
  // {
  //   // @todo add return numbers
  //   return;
  // }
  
  // boost::filesystem::create_directories(d3b_path.parent_path());

  std::ofstream db_file;
  db_file.open(d3b_path.string()); // Create/overwrite the file

  // boost::filesystem::ofstream db_file(d3b_path);

  if (db_file.is_open()) 
  {
    for (const auto& entry : db_)
    {
      db_file << detail::to_str(entry) << std::endl;
    }

    db_file.flush();
    db_file.close();
  }
}

//////////////////////////////////////////////////////////////////
void DBManager::update()
{

}

//////////////////////////////////////////////////////////////////
void DBManager::add_entry(const std::string& entry, const std::vector<std::string>& tags)
{
  if (entry.empty())
  {
    return;
  }

  D3bEntry db_entry;

  db_entry.entry_hash = "0xBEBECAFE";
  db_entry.compressed = false;
  db_entry.filepah = entry;
  db_entry.file_hash = "0xDEADBEEF";

  db_entry.tags = std::vector<std::string>(tags.begin(), tags.end());

  db_.push_back(db_entry);
}

}
