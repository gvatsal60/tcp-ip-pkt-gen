#include <gtest/gtest.h>

#include "packet_gen.hpp"
#include "utils.hpp"

class NullPtrCheckTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize any resources needed for the tests
    packet_gen_test_ = std::make_unique<Packet_Generator>();
  }

  // This function will be called after each test
  void TearDown() override {
    // Clean up any resources allocated in SetUp
  }

  Packet_Generator *GetPacketGen() const { return packet_gen_test_.get(); }

private:
  std::unique_ptr<Packet_Generator> packet_gen_test_;
};

// Test case to check NullPtrCheck function with a null pointer
TEST_F(NullPtrCheckTest, NullPtrTest) { EXPECT_FALSE(NullPtrCheck(nullptr)); }

// Test case to check NullPtrCheck function with non-null pointer
TEST_F(NullPtrCheckTest, NonNullPtrTest) {
  EXPECT_TRUE(NullPtrCheck(GetPacketGen()));
}
