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
    │    └── ex1.h       # Declaration and definitions
    └── test
         ├── src
         │   └── test_ex1.cpp
         └── bin
             └── test_ex1_inclusion.gtest

## Example Two: Explicit Instantiation

Concept: Declarations in header file, definitions in cpp file, explicit instantation in cpp file

Pros:  
- Faster build 
- Source code not exposed

Cons:  
- Limited to explicit instantiations

Source files:  

    ├── ex2_expl_instantiation
    │    ├── ex2.h          # Declaration
    │    └── ex2.cpp        # Definitions, explicit instantiations
    └── test
         ├── src
         │   └── test_ex2.cpp
         └── bin
             └── test_ex2_explInstantiation.gtest

## Example Three: Inclusion with Explicit Instantiation

Concept: Declarations in header file, definitions in another header file, explicit instantiations in cpp file.

Pros:
- Faster build
- Source code not exposed
- Explicit instantiations separated from source code 

Cons:
- Requires 3 total files 
- Limited to explicit instantiations

Source files:  

    ├── include
    │    ├── ex3_decl.h     # Declaration
    │    ├── ex3_def.h      # Definitions
    │    └── ex3.cpp        # Explicit instantiations
    └── test
         ├── src
         │   └── test_ex3.cpp
         └── bin
             └── test_ex3_inclusionWExplInstantiation.gtest