#include <gtest/gtest.h>

#include "packet_gen.hpp"
#include "utils.hpp"

// Test fixture for NullPtrCheck function
class NullPtrCheckTest : public ::testing::Test {
 protected:
  // This function will be called before each test
  void SetUp() override {
    // Initialize any resources needed for the tests
  }

  // This function will be called after each test
  void TearDown() override {
    // Clean up any resources allocated in SetUp
  }
};

// Test case to check NullPtrCheck function with a non-null pointer
TEST_F(NullPtrCheckTest, NonNullPtr) {
  auto* ptr = new int(42);
  EXPECT_TRUE(NullPtrCheck(ptr));
  delete ptr;  // Clean up allocated memory
}

// Test case to check NullPtrCheck function with a null pointer
TEST_F(NullPtrCheckTest, NullPtr) {
  int* ptr = nullptr;
  EXPECT_FALSE(NullPtrCheck(ptr));
}

// Test case to check NullPtrCheck function with other types
TEST_F(NullPtrCheckTest, OtherTypes) {
  const auto* packet_gen = new Packet_Generator();
  EXPECT_TRUE(NullPtrCheck(packet_gen));
  delete packet_gen;  // Clean up allocated memory
}