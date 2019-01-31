## Polymorphism

### Basics of C++ Polymorphism: Dynamic vs Static

#### Dynamic Polymorphism

Polymorphic design started with the concept of inheritence through virtual functions. Common capabilities between related object types are noted and declarted as virtual function interfaces in a common base class.

```cpp
// Classic Inheritance example:
class GeoObj {
  public:
    virtual void draw() const = 0;
    virtual Coord center_of_grav() const = 0;
    virtual ~GeoObj = default;
};

class Circle : public GeoObj {
  // same methods as above, all with keyword `override` after 
  ...
}
```

#### Static Polymorphism

Templates can be used to implement polymorphism. However, common behavior is not implemented through base classes. Instead, the commonality is supported by all related class having operations (functions, variables) that have the same syntax, are defined independently, and are enabled when templates are instantiated. The common functions and variables are templated instead of virtual members in a base class. In this way, all concrete classes are related "horizontally", instead of "vertically connected" with a common base class.  

#### Comparison

Inheritance Polymorphism: bounded and dynamic
- Bounded = interfaces of the types participating in the polymorphic behavior are predetermined by the design of the common base class
- Dynamic = binding of interfaces done at run time
- Pros = 
    - heterogeneous collections handled elegantly
    - executable code size is smaller
    - code can be entirely compiled, no implementation source published

Template Polymorphism: unbounded and static
- Unbounded = interfaces of the types participating in the polymorphic behavior are not predetermined
- Static = binding of interfaces done at compile time
- Pros = 
    - collections of built-in types easily implemented (no interface commonality expressed via base class)
    - generated code is potentially faster
    - concrete types provide only partial interfaces that will only be used it exercised by application
    - more type safe (all bindings checked at compile time)

These two types **do not** have to be separated. Inheritance and templates can work together, but have rules. See section below (Templates and Inheritance).

In terms of C++: generic programming is programming with templates, where object-oriented proramming is programming with virtual functions. Generic programming is most often used with STL (Standard Template Library). STL is the "best" example of generic programming that most C++ developers make use of regularly, container types being the primary motivation for the introduction of templates with C++.

### Derived Class `using` declarations

With the keyword `using`, derived classes can make use of base class functions. This is not unique to templates. Example:

```cpp
class Base {
  public:
    void f(int);
    void f(char*);
};

class Derived : class Base {
  public:
    using Base::f;
};
```

### Nondependent Base Class

A nondependent base class is one with a complete type that can be determined without knowing the template arguments. The name of this base is denoted using a nondependent name.

Nondependent bases in templates behave like bases in ordinary nontemplate classes. However, when an unqualified name is looked up in the templated derivation, the nondependent bases are considered before the list of template parameters! You can see this in the below `class D2`, where `T strange` is of the derived template class argument type, double, not the Base class template parameter.

```cpp
template<typename X>
class Base {
  public:
    int basefield;
    using T = int;
};

class D1: public Base<Base<void>> {   //not a template case really
  public:
    void f() { basefield = 3; }       //usual access to inherited member
};

template<typename T>
class D2 : public Base<double> {      //nondependent base
  public:
    void f() { basefield = 7; }        //usual access to inherited member
    T strange;        // T is Base<double>::T, not the template parameter!
};
```

### Dependent Base Class

In nondependent example above, the base class is fully determined. It does not depend on a template parameter. This means a C++ compiler can look up nondependent names in those base classes as soon as the template definition is seen. An alternative — not allowed by the C++ standard — would consist in delaying the lookup of such names until the template is instantiated. This has a disadvantage: it also delays any error messages resulting from missing symbols until instantiation. Therefore, the C++ standard specifies that a nondependent name appearing in a template is looked up as soon as it is encountered.

Look at this example:
```cpp
template<typename T>
class Base {
  public:
    enum E { e1 = 6, e2 = 28, e3 = 496 };
    virtual void zero(E e = e1);
    virtual void one(E&);
    int basefield;
};

template<typename T>
class Derived : public Base<T> {
  public:
    void f() {
        typename Derived<T>::E e;   // this->E would not be valid syntax
        this->zero();               // D<T>::zero() would inhibit virtuality
        one(e);                     // one is dependent because its argument id dependent
    }
    using Base<T>::basefield;    // #1 dependent name now in scope
    void f() { basefield = 0; }  // #2 fine                          
};
```

### Implementing Traits

A trait is a small object whose main purpose is to carry infromation used by another object/alg to determine policy or implmentation details. Also defined as a distinctive feature characterizing a thing, or representation of additional properties of a template parameter. A *Traits class* is used in place of template parameters - it aggregates useful types and constants.

**Fixed traits** - additional information, or characteristics, that cannot be changed, such as defining/identifying `type` of a template parameter.

**Value traits** - constants and other classes of values that can be associated with a type as well (e.g. defining constexpr static member variables with specializations of template classes)

**Parameterized traits** - adding trait into template parameters

**Predicate traits** - type functions yielding a boolean value that depend on multiple template args

**Result type traits** - useful for operator templates, giving traits to return type

### Templates and Inheritance

#### CRTP: Curiously Recurring Template Pattern

Passing a derived class as a template argument to one of its own base classes

```cpp
template<typename D>
class CuriousBase {};

class CuriousNonDep : public CuriousBase<CuriousNonDep> {
  // ...
};    // Nondependent base class

template<typename T>
class CuriousDep : public CuriousBase<CuriousDep<T>> {
  // ...
};    // Dependent base class
```

In the dependent base class exmaple, the derived class is passed down to its base class via template parameter, allowing the base class to customize its own behavior to the derive class wthout use of virtual functions. 

This allows CRTP to factor out implementations that can only be member functions (e.g. constructor, destructor, subscript operators) or are dependent on the derived class' identity.

#### Barton Nackman trick

Also known as restricted template expansion. See example below for operator `==` in custom `Array` class, called restricted because it avoids the use of template operator `==(T,T)`.

```cpp
template<typename T>
class Array {
  static bool areEqual(Array<T> const& a, Array<T> const& b);
  public:
    friend bool operator==(Array<T> const& a, Array<T> const& b) {
      return areEqual(a,b);
    }
};
```

### References

C++ Templates: The Complete Guide, 2nd Edition; Douglas Gregor, Nicolai M. Josuttis, David Vandevoorde; Publisher: Addison-Wesley Professional; September 2017  
http://thad.frogley.info/archive/cpp_traits_intro.html