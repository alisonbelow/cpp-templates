## C++ Templates - Compiling and Linking

A **compiler** translates source code to object files, which contain machine code with symbolic annotations (cross-referencing other object files and libraries). The **linker** creates executable programs or libraries by combining the object files and resolving the symbolic cross-references they contain.  

Templates are “compiled” in two phases:

1. Without instantiation at definition time, the template code itself is checked for correctness ignoring the template parameters. This includes:
    – Syntax errors are discovered, such as missing semicolons.
    – Using unknown names (type names, function names, …) that don’t depend on template parameters are discovered.
    – Static assertions that don’t depend on template parameters are checked.

2. At instantiation time, the template code is checked (again) to ensure that all code is valid. That is, now especially, all parts that depend on template parameters are double-checked.

Two-phase translation leads to an important problem in the handling of templates in practice: When a function template is used in a way that triggers its instantiation, a compiler will (at some point) need to see that template’s definition. This breaks the usual compile and link distinction for ordinary functions, when the declaration of a function is sufficient to compile its use.

### Using Templates in Practice - Declarations, Definitions

Basics: A class template by itself is not a type, or an object, or any other entity. No code is generated from a source file that contains only template definitions. In order for any code to appear, a template must be instantiated: the template arguments must be provided so that the compiler can generate an actual class (or function, from a function template). 

Problem: Writing templated header file, and templated cpp file where implementations/instantiations occur will compile, but it fails to link. Error output = "... no definition ...". 

1. Inclusion Model (section 9.1 - C++ Templates: The Complete Guide 2nd Edition)
    Place declaration and definition in same header file
    This solves the linking problem, but it increases time needed for compile to compile. This is only a build-time problem.
    
2. Explicit Template Instantation (section 14.5 - C++ Templates: The Complete Guide 2nd Edition)  

    An **explicit instantiation directive** id the point of instantiation for a template specialization. It consists of the keyword `template` followed by declaration of specialization to be instantiated.  

    All the members of a class template specialization can be explicitly instantiated by explicitly instantiating the class template specialization. Because these explicit instantiation directives ensure that a definition of the named template specialization (or member thereof) is created, the explicit instantiation directives above are more accurately referred to as explicit instantiation definitions.  

    Issues = must carefully keep track of which entities to instantiate. For large projects this quickly becomes an excessive burden

3. Pre-compiled headers (section 9.3 - C++ Templates: The Complete Guide 2nd Edition  
   
   When compiler translates file, works from beginning to end processing all tokens (including those in `#include`d files), adapts to internal state, and generates code. Pre-compiled header technique = files start with max number of common lines of code (same `#include` directives and so on). Put this matching code in own header file for optimization, assuming system has sufficient memory.  

4. *module* Mechanism (section 17.11 - C++ Templates: The Complete Guide 2nd Edition)

### Instantiation 

#### On-demand Instantiation

When a C++ compiler encounters the use of a template specialization, it will create that specialization by substituting the required arguments for the template parameters.2 This is done automatically and requires no direction from the client code (or from the template definition, for that matter). This is also known as *implicit instantiation* or *automatic instantiation*.

On-demand instantiation necessitates both declaration and definition - thus the inclusion technique above.

#### Lazy Instantiation

A compiler is lazy when instantiating templates. This means only what is needed is covered. 

*Partial instantiation* occurs when the compiler does not need the full definition. This can be when a function's name is "good enough", and the full definition is not needed to be translated. This can also happen when an instance of a class template is referred to without the need for that instance to be a complete type. Variable templates can partially instantiated, but alias templates (`using ...`) cannot.

#### Class Instantiation

When a class template is fully instantiated:

- declarations of members are fully instantiated
- definitions of member are partially instantiated

Except for:

- class member unions are fully instantiated
- virtual member functions may or may not be fully instantiated (generally are)
- default function call arguments are not instantiated unless there is a call to that function that makes use of the default argument
- Exception specifiers and default member initializers are also partially initialized

#### Points of Instantiation

POI = when a code construct referes toa  template specializatio in such a way that the definition of the corresponding template meeds to be instantiated to create that specialization. It is the point in the source where the subsituted template could be inserted.

#### Greedy, Queried, Iterated Instantiation

**Problem:** a templated member function is instantiated once in 2 cpp files. The linker handles this template member function instantiation similarly to an ordinary member function/function.  The compiler must ensure that code is enerated at only one of the locations, and not both. The compiler therefore must carry information from one translation unit to another. 

**Solution One = greedy instantiation:** assumes the linker is aware of certain entities (linkable itemplate instantiations). Compiler marks these duplications across the various object files/libraries. When linker comes across each instance, it keeps once and discards the rest.

Problems: (1) compiler wastes time on generating/optimizing *N* instantiations, where only one will be kept, (2) linker may not recnognize subtle differences between multiple instances of template specializations, (3) sum of all object files can be much larger wth alternatives because of code duplication

**Solution Two = queried instantiation:** no longer used. Uses database to keep track of specialization instantiations and their source code, updating as necessary when a new specialization is encountered

**Solution Three = iterated instantiation:** used less than greedy. Sources are compiled without instantiated linkable specializations, object files are linked with a prelinker, prelinker invokes linker and determines (through error messages) where instantitations are needed, prelinker invokes compiler on sources for needed template definitions to generate missing instantiations. 

Problems: (1) overhead in time to link and cost of recompilation/linking, (2) diagnostics/warnings delayed until link time, (3) must remember where particular source containing definition is located

#### Explicit Instantiation 

As discussed above, syntax = one of three ways:
`template function<type>(type)`
`template function<>(type)`
`template function(type)`   (template arguments can be deduced)

### Deduction Process

Types of an argument of a functional call are compared to the corresponding parameterized type of a function template in an attempt to conconlude the correct substitution for 1+ of the deduced arguments

Example template function:  `template<typename T> T max(T a, T b) { return b < a ? a : b; }`  
Example call: `auto g = max(1, 1.0);`  
In this example, the first arg is type `int`, so parameter T is deduced to be `int`. When the second arg type is `double`, the previous conclusion is contradicted. This deduction process fails/is invalid. 

The deduction process can also fail during analyzing return arguments. Most notably, as discussed in 0_c++_template_basics, C++14 allows deducible `auto` placeholder for return types.

C++17 allows nontype parameters to be deducible and allows deduction of the template parameters of a class type from the arguments specified in an initializer of a variable declaration OR a functional-notation type conversion.

### References

https://en.cppreference.com/w/cpp/language/class_template  
C++ Templates: The Complete Guide, 2nd Edition; Douglas Gregor, Nicolai M. Josuttis, David Vandevoorde; Publisher: Addison-Wesley Professional; September 2017  
