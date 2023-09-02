#include <memory>

#include <gtest/gtest.h>

#include "d3b/manager.hpp"

TEST(D3BManagerTest, NonExistingD3b)
{
  d3b::DBManager manager("dummy.d3b");

  EXPECT_FALSE(manager.init());
}

//////////////////////////////////////////////////////////////////
class EmptyD3BTester : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    manager_ = std::make_unique<d3b::DBManager>(std::string(TEST_FILES_LOC).append("test_files/test_empty_d3b.d3b"));
  }
  
  std::unique_ptr<d3b::DBManager> manager_;
};


TEST_F(EmptyD3BTester, CanInitializeD3B) 
{
  EXPECT_TRUE(manager_->init());
}

//////////////////////////////////////////////////////////////////
class OneEntryD3BTester : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    manager_ = std::make_unique<d3b::DBManager>(std::string(TEST_FILES_LOC).append("test_files/test_one_entry_d3b.d3b"));
  }
  
  std::unique_ptr<d3b::DBManager> manager_;
};


TEST_F(OneEntryD3BTester, CanInitializeD3B) 
{
  EXPECT_TRUE(manager_->init());
}

//////////////////////////////////////////////////////////////////
class FooTester : public ::testing::Test 
{
protected:
  void SetUp() override 
  {
    manager_ = std::make_unique<d3b::DBManager>("foo_tester.d3b");
  }
  
  std::unique_ptr<d3b::DBManager> manager_;
};


TEST_F(FooTester, CanInitializeD3B) 
{
  EXPECT_FALSE(manager_->init());

  manager_->add_entry("/foo.h", std::vector<std::string>{"foo", "bar", "baz"});
  manager_->add_entry("/wsome.pdf", std::vector<std::string>{"shh", "bar", "baz"});
  manager_->add_entry("path/to/my/heart.png", std::vector<std::string>{"foo", "bard", "badddz"});
  manager_->add_entry("pls.stop.now", std::vector<std::string>{"foddo", "dcc", "baz"});
  manager_->add_entry("pls.stop.nooooooooooooooooo");
  manager_->add_entry("pls.stop.now", std::vector<std::string>{"foddo", "dcc", "baz"});
  manager_->add_entry("pls.stop.nooooooooooooooooo");

  manager_->sync();
}
