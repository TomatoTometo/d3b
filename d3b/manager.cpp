#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <iostream> // delete

#include "detail/misc_helpers.hpp"
#include "manager.hpp"
#include "types.hpp"

namespace d3b
{

//////////////////////////////////////////////////////////////////
DBManager::DBManager(std::unique_ptr<DbInterface> db_interface) :
  db_interface_(std::move(db_interface))
{

}

//////////////////////////////////////////////////////////////////
bool DBManager::init(const std::string& d3b_location)
{
  // @todo check for error
  db_interface_->init(d3b_location);

  std::vector<std::string> entries;
  db_interface_->read(entries);

  for (const auto& entry_str :entries)
  {
    if (entry_str.empty()) continue;
    
    const size_t hash_delimiter = entry_str.find_first_of(";");
    if (hash_delimiter == std::string::npos)
    {
      // @todo send this one to jail too
      continue;
    }
    if (entry_str.substr(0, hash_delimiter) != detail::hash1(entry_str.substr(hash_delimiter + 1, entry_str.size())))
    {
      // @todo if hash doesn't match, add to other array and warn the user
      continue;
    }

    D3bEntry entry = detail::to_D3bEntry(entry_str);

    db_.push_back(std::move(entry));
    db_map_.emplace(entry.filepah, &db_.back());
  }

  return true;
}

//////////////////////////////////////////////////////////////////
void DBManager::sync()
{
  // @todo check return
  db_interface_->sync(db_);
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

  // @todo check if entry is already in the db
  // @todo check if entry is a valid file
  // @todo get the entry hash
  // @todo ask user if they want to compress
  //       if so, get the size of message, and provide status on process

  D3bEntry db_entry;

  db_entry.entry_hash = "0xBEBECAFE";
  db_entry.compressed = false;
  db_entry.filepah = entry;
  db_entry.file_hash = "0xDEADBEEF";

  db_entry.tags = std::vector<std::string>(tags.begin(), tags.end());

  db_.push_back(db_entry);
}

}
