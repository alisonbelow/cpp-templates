#include "ex1_inclusion/ex1.h"

#include "gtest/gtest.h"

TEST(TEMPLATES_LINKING_AND_COMPILING, ex1_inclusion) 
{
    f<int>();
    f<bool>();
    f<double>();
    f<std::string>();
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}