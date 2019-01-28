## C++ Templates

### Vocab

**template instantiation**: process of actually creating a defition for a regular class, type alias, function, member function, or variable from a template by substituting concrete arguments in place of template parameters

**specialization**: the entity resulting from an instantiation or an incomplete instantiation (e.g. class, function, member, function, or variable)  
Example:  
`template <typename T> class myClass<T,T> {};   // partial specialization`  
`template <typename T> class myClass<bool,T> {};   // partial specialization`  
`template <> class myClass<std::string,int> {};   // explicit specialization`

**declarations** become **definitions** when details of their structure are made known, and/or where storage space must be allocated. For class types, a brace-enclosed bod must be provided, be `= default;` or `= delete;` For a variable, absence of keyword `extern` causes a declaration to become a definition.

**Template parameters**:  names listed after the keyword `template` in the template declaration/definition

**Template arguments**: items that are substituted for template parameters, can be more than just names

**Template id**: combination of template name, followed by arguments in angle brackets (this is the substitution of template param by template args)

### Template Fundamentals

C++ supports 4 types of templates:

1. class templates
2. function templates
3. variable templates
4. alias templates

All can appear in the namespace scope or class scropt. In the class scope they become nested class templates, member function templates, static data member templates, and member alias templates.

When defining a constructor template, the implicit declaration of the default constructor is disabled. You must add `= default` to force the compiler to default the constructor.

### Using Templates in Practice - Declarations, Definitions, Compiling, and Linking

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

### Parameterized Declarations in Templates

Starting from C++17, variables (including static data members) and variable templates can be defined inline, meaning that their definition can be repeated across translation units. It is not enough to be defined in enclosing class, it must be defined using keyword `inline`.

There can be Nontemplate members of class templates. Example:  

```cpp
template<int I>
class CupBoard {
  class Shelf;    // ordinary class in class template
  void open();    // ordinary function in class template
  static double totalWeight;  // ordinary static data member in class template
}
```

The definition must look like:

```cpp
template<int I> class CupBoard<I>::Shelf{};
template<int I> class CupBoard<I>::open() {};
```

The static member can be initialized in class template with keyword `inline`:

```cpp
template<int I>
class CupBoard {
  // ...
  inline static double totalWeight = 0.0;
}
```

Member function templates **cannot** be declared virtual.


### References


C++ Templates: The Complete Guide, 2nd Edition; Douglas Gregor, Nicolai M. Josuttis, David Vandevoorde; Publisher: Addison-Wesley Professional; September 2017