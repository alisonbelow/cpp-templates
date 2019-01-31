## Class Templates

Class templates are must be instantiated with template arguments explicitly specified, up through C++17. Since C++17, you do not have to specify template arguments explicitly: you can skip those specifications if the constructor is able to *deduce* all template parameters (without a default value).  

For class template member function, code is instantiated only for those (template member functions) that are called. This means for class templates, member functions are instantiated only if they are used. This saves time and space and allows use of class templates only partially.

### Specialization of Class Templates

Specializing class templates allows you to *optimize implementations for certain types* or to *fix a misbehavior of certain types* for an instantiation of the class template.  
Rules:  
(1) If you specialize a class template you **must** specialize all member functions  
(2) You can specialize a member function of a class template, but then you **lose** the ability to specialize the whole class instance the specialized member function belongs to 

Syntax: 
- declare class or function with leading `template <>` 
- give specification in following `<>` for what type the class template is specialized to

```cpp
template <>         // preceding "template <>"
class Stack<std::string> {};   // we are specializing template class Stack for data type `std::string`

/* NOW all member functions must be explicitly defined with each occurence of T replaced with std::string */
```

Partial specializations occur when the `template<typename T>` or `template<class T>` is left before the class/member function declaration, but the type is specified in the following `<>`. An example of such is given for the Stack class example for pointer type `T*`:  

```cpp
template<typename T>
class Stack<T*> { ... }
```

Specializations occur when a templated argument is given a default value. The default value will be selected when the instance of the class does not name a type.

```cpp
template<typename T, typename contents = std::vector<T>>
class Stack { ... }
```

Partial specializations can occur in combination when there are multiple template parameters. Template parameters can be non-specialized, specialized, or defaulted.

### Class Member Templates

See example details/definitions3.cpp for examples of template class member functions, template class member variables

```cpp
template <typename T>  // a namespace scope class template
class List {
 public:
  List() = default;       // because a template constructor is defined

  template <typename U>   // another member class template,
  class Handle;           //  without its definition

  template <typename U>   // a member function template
  List(List<U> const&);   //  (constructor)

  template <typename U>   // a member variable template (since C++14)
  static U zero;
};

template <typename T>  // out-of-class member class template definition
template <typename U>
class List<T>::Handle {};

template <typename T>  // out-of-class member function template definition
template <typename T2>
List<T>::List(List<T2> const& b) {}

template <typename T>  // out-of-class static data member template definition
template <typename U>
U List<T>::zero = 0;
```

**Template constructor:** a constructor template (a special kind of member function template) disables the implicit declaration of the default constructor (because it is only implicitly declared if no other constructor is declared). Adding a defaulted declaration such as `List() = default;` ensures an instance of `List<T>` is default-constructible with the semantics of an implicitly declared constructor.

**Non-template members of classes**: these members of templated classes are not necessarily templates themselves, but *temploids* or *templated entities*.  This consists of member class, member function, member enumeration, and static data members. The declaration of is not proceeded by a template-id, but the definition is. Example:

```cpp
// Declarations
template<int I>
class CupBoard
{
    class Shelf;                // ordinary class in class template
    void open();                // ordinary function in class template
    enum Wood : unsigned char;  // ordinary enumeration type in class template
    static double totalWeight;  // ordinary static data member in class template
    // In C++17+, the totalWeight static data member can be declared inline
    inline static double totalWeight2 = 0.0;
};

// Definitions
template<int I>         // definition of ordinary class in class template
class CupBoard<I>::Shelf {};

template<int I>         // definition of ordinary function in class template
void CupBoard<I>::open() {}

template<int I>         // definition of ordinary enumeration type class in class template
enum CupBoard<I>::Wood { Maple, Cherry, Oak };

template<int I>         // definition of ordinary static member in class template
double CupBoard<I>::totalWeight = 0.0;
```

#### Virtual Member Functions

Member function templates cannot be declared virtual. Ordinary functions can be declared virtual.

**Why?** The usual implementation of the virtual function call mechanism uses a fixed-size table with one entry per virtual function. However, the number of instantiations of a member function template is **not fixed** until the entire program has been translated. Therefore, supporting virtual member function templates would require support for a whole new kind of mechanism in C++ compilers and linkers.

Ordinary members of class templates can be virtual because their number is fixed when a class is instantiated:

```cpp
template<typename T>
class Dynamic {
  public:
    virtual ~Dynamic();  // OK: one destructor per instance of Dynamic<T>

    template<typename T2>
    virtual void copy (T2 const&);   /* ERROR: unknown number of instances of copy() given an instance of Dynamic<T>*/
};
```

### References

C++ Templates: The Complete Guide, 2nd Edition; Douglas Gregor, Nicolai M. Josuttis, David Vandevoorde; Publisher: Addison-Wesley Professional; September 2017  
