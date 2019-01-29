# Compiling and Linking

Three examples are provided for how you can compile/link templated classes. These three methods are discussed in detail in `doc/c++_templating`. The actual testing for this is done during the build. If the example files were not built/linked properly, the build would fail, specifically during the linking phase. Each of these methods can be used to create templated classes.  

## Example One: Inclusion Method

Concept: Declarations and definitions in same header file  

Pros:  
- One file

Cons:  
- Overhead during build
- Source code exposed

Source files:  

    ├── ex1_inclusion
    │    └── include
    │        └── ex1.h       # Declaration and definitions
    └── test
         ├── ex1_inclusion
         │   └── test_ex1.cpp
         └── bin
             └── test_ex1.gtest

## Example Two: Explicit Instantiation

Concept: Declarations in header file, definitions in cpp file, explicit instantation in cpp file

Pros:  
- Faster build 
- Source code not exposed

Cons:  
- Limited to explicit instantiations

Source files:  

    ├── ex2_expl_instantiation
    │    ├── include
    │    │   └── ex2.h          # Declaration
    │    └── src
    │        └── ex2.cpp        # Definitions, explicit instantiations
    └── test
         ├── ex2_expl_instantiation
         │   └── test_ex2.cpp
         └── bin
             └── test_ex2.gtest

## Example Three: Inclusion with Explicit Instantiation

Concept: Declarations in header file, definitions in another header file, explicit instantiations in cpp file.

Pros:
- Faster build
- Source code not exposed
- Explicit instantiations separated from source code 
- Can choose inclusion or explicit instantiation method by `#include` and cmake static library linking approach

Cons:
- Requires 3 total files 

Source files:  

    ├── ex3_inclusion_with_expl_instantiation
    │    ├── include 
    │    │   ├── ex3_decl.h     # Declaration
    │    │   └── ex3_def.h      # Definitions
    │    └── src 
    │        └── ex3.cpp        # Explicit instantiations
    └── test
         ├── ex3_inclusion_with_expl_instantiation
         │   ├── test_ex3a.cpp      # Test explicit instantiation
         │   └── test_ex3b.cpp      # Test inclusion
         └── bin
             ├── test_ex3a.gtest
             └── test_ex3b.gtest

There are two tests performed for this method. For test 3a, `ex3.cpp` is pre-compiled into a library for `test_ex3a.cpp` to use. This method uses explicit instantiation to limit what data types can be used with the `f()` function. Alternatively, test 3b takes the inclusion approach. Test 3b does not require a pre-compiled library. Instead `ex3_def.h` can be included and automatically instantiated by the compiler for an inclusion approach.  