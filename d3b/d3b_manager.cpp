#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <iostream> // delete
#include <fstream>

#include "d3b_manager.hpp"

namespace d3b
{

DBManager::DBManager(const std::string location) :
  location_(std::move(location))
{

}

bool DBManager::init()
{
  boost::filesystem::path d3b_path(location_.c_str());

  if (!boost::filesystem::exists(d3b_path)) 
  {
    // @todo add return numbers
    std::cout << "File does not exist!" << std::endl;
    return false;
  }

  boost::filesystem::fstream db(d3b_path, std::ios::in);

  if (db.is_open()) 
  {
    std::cout << "File created and read successfully!" << std::endl;
    // Read and print the content
    std::string line;
    while (std::getline(db, line)) {
        std::cout << line << std::endl;
    }
    db.close();

    return true;
  }

  return false;
}

void DBManager::sync()
{

}

void DBManager::update()
{

}

void DBManager::add_entry(const std::string& entry)
{

}

}
