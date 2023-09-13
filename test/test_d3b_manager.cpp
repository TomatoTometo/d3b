#include <memory>

#include <gtest/gtest.h>

#include "d3b/manager.hpp"
#include "d3b/file_io_interface.hpp"

TEST(D3BManagerTest, NonExistingD3b)
{
  d3b::DBManager manager(std::make_unique<d3b::DbFileIO>());

  EXPECT_FALSE(manager.init("dummy.d3b"));
}

//////////////////////////////////////////////////////////////////
class EmptyD3BTester : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    manager_ = std::make_unique<d3b::DBManager>(std::make_unique<d3b::DbFileIO>());
  }
  
  std::unique_ptr<d3b::DBManager> manager_;
};


TEST_F(EmptyD3BTester, CanInitializeD3B) 
{
  EXPECT_TRUE(manager_->init(std::string(TEST_FILES_LOC).append("test_files/test_empty_d3b.d3b")));
}

//////////////////////////////////////////////////////////////////
class OneEntryD3BTester : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    manager_ = std::make_unique<d3b::DBManager>(std::make_unique<d3b::DbFileIO>());
  }
  
  std::unique_ptr<d3b::DBManager> manager_;
};


TEST_F(OneEntryD3BTester, CanInitializeD3B) 
{
  EXPECT_TRUE(manager_->init(std::string(TEST_FILES_LOC).append("test_files/test_one_entry_d3b.d3b")));
}

//////////////////////////////////////////////////////////////////
class FooTester : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    manager_ = std::make_unique<d3b::DBManager>(std::make_unique<d3b::DbFileIO>());
  }
  
  std::unique_ptr<d3b::DBManager> manager_;
};


TEST_F(FooTester, CanInitializeD3B) 
{
  EXPECT_FALSE(manager_->init("foo_tester.d3b"));

  manager_->add_entry("/foo.h", std::vector<std::string>{"foo", "bar", "baz"});
  manager_->add_entry("/wsome.pdf", std::vector<std::string>{"shh", "bar", "baz"});
  manager_->add_entry("path/to/my/heart.png", std::vector<std::string>{"foo", "bard", "badddz"});
  manager_->add_entry("pls.stop.now", std::vector<std::string>{"foddo", "dcc", "baz"});
  manager_->add_entry("pls.stop.nooooooooooooooooo");
  manager_->add_entry("pls.stop.now", std::vector<std::string>{"foddo", "dcc", "baz"});
  manager_->add_entry("pls.stop.nooooooooooooooooo");

  manager_->sync();
}


/* Compress a folder
#include <boost/filesystem.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <iostream>

namespace fs = boost::filesystem;
namespace io = boost::iostreams;

void compressFolder(const fs::path& folderPath, const fs::path& compressedFilePath) {
    std::ofstream outputFile(compressedFilePath.string(), std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "Failed to open the output file" << std::endl;
        return;
    }

    io::filtering_streambuf<io::output> filteringStream;
    filteringStream.push(io::gzip_compressor());
    filteringStream.push(io::file_sink(folderPath.string(), std::ios::binary));

    try {
        io::copy(filteringStream, outputFile);
        std::cout << "Folder compressed successfully" << std::endl;
    } catch(const std::exception& ex) {
        std::cout << "Compression failed: " << ex.what() << std::endl;
    }

    outputFile.close();
}

int main() {
    fs::path folderPath("path_to_folder"); // Replace with the actual folder path
    fs::path compressedFilePath("path_to_compressed_file.gz"); // Replace with the desired path for the compressed file

    compressFolder(folderPath, compressedFilePath);

    return 0;
}

---------------------

#include <boost/filesystem.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <iostream>

namespace fs = boost::filesystem;
namespace io = boost::iostreams;

void compressFile(const fs::path& filePath, const fs::path& compressedFilePath) {
    std::ofstream outputFile(compressedFilePath.string(), std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "Failed to open the output file" << std::endl;
        return;
    }

    io::filtering_streambuf<io::output> filteringStream;
    filteringStream.push(io::gzip_compressor());
    filteringStream.push(io::file_source(filePath.string(), std::ios::binary));

    try {
        io::copy(filteringStream, outputFile);
        std::cout << "File compressed successfully" << std::endl;
    } catch(const std::exception& ex) {
        std::cout << "Compression failed: " << ex.what() << std::endl;
    }

    outputFile.close();
}

int main() {
    fs::path filePath("path_to_file"); // Replace with the actual file path
    fs::path compressedFilePath("path_to_compressed_file.gz"); // Replace with the desired path for the compressed file

    compressFile(filePath, compressedFilePath);

    return 0;
}

*/