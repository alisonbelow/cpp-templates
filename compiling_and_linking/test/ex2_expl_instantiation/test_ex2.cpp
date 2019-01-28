#include "ex2_expl_instantiation/ex2.h"

#include "gtest/gtest.h"

TEST(TEMPLATES_LINKING_AND_COMPILING, ex2_explInstantiation) 
{
    f<int>();
    f<bool>();
    f<double>();

    /*
     * If you uncomment the line below, the linking portion of the 'make' command will fail!
     * This is because the function f was ONLY explicitly instantiated for int, bool, and double, NOT std::string
     */
    // f<std::string>();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}