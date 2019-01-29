#include "ex3_inclusion_with_expl_instantiation/ex3_def.h"

#include "gtest/gtest.h"

TEST(TEMPLATES_LINKING_AND_COMPILING, ex3_inclWExplInstantiation_b) 
{
    f<int>();
    f<bool>();
    f<double>();

    /*
     * We are allowed to use f<std::string> because we are taking the inclusion and automatic instantiation approach
     * in this test. 
     */
    f<std::string>();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}