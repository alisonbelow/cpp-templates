## C++ Templates

### Vocab

**template instantiation**: process of actually creating a defition for a regular class, type alias, function, member function, or variable from a template by substituting concrete arguments in place of template parameters

**specialization**: the entity resulting from an instantiation or an incomplete instantiation (e.g. class, function, member, function, or variable)  
Example:  
`template <typename T> class myClass<T,T> {};   // partial specialization`  
`template <typename T> class myClass<bool,T> {};   // partial specialization`  
`template <> class myClass<std::string,int> {};   // explicit specialization`

**declarations** are a standard C++ concept meaning when name is introduced into a C++ scope.  

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

All can appear in the namespace scope or class scope. In the class scope they become nested class templates, member function templates, static data member templates, and member alias templates.

When defining a constructor template, the implicit declaration of the default constructor is disabled. You must add `= default` to force the compiler to default the constructor.

### ODR : The One Definition Rule

C++ has constraints on redeclarations of various entities, and this applies to templates. ODR basics for templates:

- Ordinary (not template) noninline functions and member functions, noninline global variables and static data members should only be defined once across the whole program
- Class types (incl structs and unions), templates (incl partial specializations but not full specializations), and inline functions/variables should be defined AT MOST once PER translation unit, and all those definitions should be indentical. (Translation unit = what results from pre-processing a file, AKA contents named by `#include` and macro expansions)
    - Since C++17, global/static variables and data members can be defined as inline, removing requirement that they should only be defined once in a translation unit 

### Difference between using `typename` and `class`

For **type template parameter declaration**, there is no difference between using `template<typename T> ...` or `template<class T> ...`. These keywords have the same meaning in this scenario.

There are, however, specific use cases where the keywords `class` and `typename` must be used specifically. 

1. Unlike type template parameter declaration, **template template parameter declaration** can only use the keyword `class` and not `typename`. This is changed after C++17, where `typename` can be used for template template parameters. An example of such (from en.cppreference.com):
    ```cpp
    template<typename T> class my_array {};
 
    // two type template parameters and one template template parameter:
    template<typename K, typename V, template<typename> typename C = my_array>
    class Map
    {
        C<K> key;
        C<V> value;
    };
    ``` 

    Another example of this is in defining template parameters for a Stack:

    ```cpp
    template<typename T, template<typename Elem> class Cont = std::deque>
    class Stack {
      private:
        Cont<T> elems;
      ...
    }
    ```

    In the above example, the `Cont` (contents) of template parameter has a template parameter `Elem`, making it a template template parameter.

2. Doing a `using` declaration with a type that depends on a previously defined template parameter necessitates using the keyword `typename`.

    ```cpp
    template<typename T>
    class Foo
    {
        typedef typename T::baz sub_t;
    };
    ```

### Template Arguments and Parameters 

There are 3 types of template parameters:

1. Type parameters (most common)

    Type parameters are declared with either `class` or `typename`. 

2. Nontype parameters
 
    Nontype parameters stand for constant values that can be determined at compile or link time. They must be of type: integer, enumeration, pointer, pointer-to-member type, lvalue ref, std::nullptr_t,  and since C++17 a type containing `auto`. More details below.

3. Template template parameters

    Template template parameters are placeholders for class or alias templates. They are declared much like class templates, but the keywords struct and union cannot be used. An example:

    ```cpp
    template<template<typename X> class C>          /* OK (if union or struct used, not OK). After C++17 you can use typename or class keyword */
    void f(C<int>* p);
    ```

For **class templates**, the arguments are either explicitly provided, deduced from the initializer, (since C++17) or defaulted.  

For **function templates**, the arguments are explicitly provided, deduced from the context, or defaulted.  

Overview:  

- Function templates define a family of functions for different template arguments.

- When you pass arguments to function parameters depending on template parameters, function templates deduce the template parameters to be instantiated for the corresponding parameter types.

- You can explicitly qualify the leading template parameters. This means if you have some function:

```cpp
template<typename T1, typename T2, typename T3>
void f(T1 a, T2, b, T3 c);

// You can do (in later code)
f<int>(3,4,8.9);
```
In this example T1 = set to int with template parameter, and T2 and T3 are decided to be int and double (perhaps) by the compiler when the arguments are seen.

- You can define default arguments for template parameters. These may refer to previous template parameters and be followed by parameters not having default arguments.

Example: 
```cpp
template<typename T1, typename T2 = double>
void f(T1 a, T2 b);

f<float>(1.0, 1.0);
```
In this example T1 is qualified to be a float, where the type of T2 is defaulted to double.

- You can overload function templates. However, you should follow the following rules:
    - When overloading function templates with other function templates, you should ensure that only one of them matches for any call.
    - When you overload function templates, limit your changes to specifying template parameters explicitly. 
    - Ensure the compiler sees all overloaded versions of function templates before you call them.

### Nontype Template Parameters

Template parameters do not have to be types for class and function templates - they can be ordinary values. **The detail that is open to interpretation by the compiler is the value, not the type**. This value must be specified when the template is used (then instantiated). 

For example, consider wanting to implement a templated Stack class that accepts template parameters as `typename T`, the data type of the Stack contents, and `std::size_t Maxsize`, the maximum number of elements the stack should hold. This templated class can be declared:

```cpp
template<typename T, std::size_t Maxsize>
class Stack {
  private:
    std::array<T,Maxsize> elems;
    std::size_t numElems;
  ...
}

// Using this class template:
Stack<int, 20> stack_datatypeInt_maxelem20;
Stack<std::string, 10> stack_datatypeString_maxelem10;
```

The above example is an example of a nontype class template, but the same concepts apply for function templates.

Nontype template parameters can be defaulted in both class and function templates.

Restrictions for nontype template parameters: can only be constant integral values (incl. enum), pointers to obj/functions/members, lvalue references to objecs/functions, or *std::nullptr_t*. Floating point numbers and class-type objects are NOT ALLOWED to be nontype template params.

Since C++17, you can define nontype template parameter to generically acept any type allowed for a nontype template parameter with keyword `auto`.

### Template Return Types

Options:  

- Introduce a third template parameter for the return type.
    ```cpp
    template<typename T1, typename T2, typename RT>
    RT max (T1 a, T2 b);
    ```

    ```cpp
    template<typename RT, typename T1, typename T2>
    RT max (T1 a, T2 b);
    ::max<double>(4, 7.2)        //OK: return type is double, T1 and T2 are deduced
    ```
- Let the compiler find out the return type.
    ```cpp
    template<typename T1, typename T2>
    auto max (T1 a, T2 b)
    ```
- Declare the return type to be the “common type” of the two parameter types. This approach uses `std::common_type()` to deduce the return type (since C++11). 

### Friends and Templates

A friend declaration is used when to identify classes or functions that have a privileged connection with the class in which the friend declaration appears. Rules:  

1. A friend declaration may be the only declaration of an entity
2. A friend function declaration can be a definition

A class member of a class template can be a a friend:

```cpp
template<typename T>
class Node;

template<typename T>
class Tree {
    friend class Factory;   // always allowed
    friend class Node<T>;   // only allowed when made visible (declared above)
    // ...
};
```
If `Node<T>` was not declared before (not visible) then it could not be instantiated in the class template. This **is not** a requirement for ordinary classes (see `Factory` above).

Member functions can be made friends by making sure the name of the friend function is followed by angle brackets. The angle brackets can contain the template arguments, but if the arguments can be deduced, the angle brackets can be left empty. Examples:  

```cpp
template<typename T1, typename T2> void f(T1, T2);

class Example {
  friend void f<>(int&, int&);        // allowed
  friend void f<int,int>(int, int);   // allowed
  friend void f<char>(char, int);     // allowed
  friend void f<>(double, double);    // not allowed, mismatch f declaration
};
```
Friend templates are when template functions, members, and classes are prefixed with the keyword `friend`.

### Alias templates

Alias templates make use of the keyword `using`. Alias templates are structured:  
`template<typename *>`  
`using AliasName = Type<*>`

### Specialization

Specialization of templates is qualifying template parameters and return types so that the template is customized. In templated functions, this can be called changing the signature of the function. Templated classes, functions, and variables can be specialized.

Function templates are specialized to tune code for better efficiency or correctness when dealing with different data types. Functions can be overloaded, but class and variable templates cannot be overloaded, only fully or partially specialized. Partial and full specializations provude alternative definitions for instances that are already implicitly declared in the generic/unspecialized template, they do not create a totally new template or template instance. This is the *key difference* with specializations and overloaded templates.

#### Full Specialization

Full specializations of class templates, function templates, and variable templates are prefixed with `template <>`, and include the specialization template parameter type in the `<>` following the function/class/variable name. Example:

```cpp
template<typename T> class S;       // Generic class template S

template <> class S<char**> {       // Full specialization of class template S
    public: 
        void print() const;
};

template<typename T> int f(T) { return 1; } // generic function template f()

template <> int f(int) { return 3; }        // full specialization of template function f()

template<typename T> constexpr std::size_t SZ = sizeof(T);  // generic template variable SZ
template<> constexpr std::size_t SZ<void> = 0;          // full specialization of template variable SZ
```

Class members can also be specialized.

#### Partial Specialization

**Rules for Partial Specialization of Class Templates:**  
1. args of partial specialization must match in kind (type, nontype, or template) the corresponding param of primary template
2. param list of partial specialization cannot have default arguments, the default args of the primary template are used
3. nontype args of partial specialization should either be nondependent values or plain nontype template params. Cannot be complex dependent statements like *2\*N*
4. List of template args of partial specialization should not be identical to list of params of primary template
5. If one of template args is pack expansion it must come at the end of the arg list

Partial specializations *are not* prefixed by `template <>`, they have the original template parameters and only change the template arguments. This syntax is true for all partial specializations.

### References

C++ Templates: The Complete Guide, 2nd Edition; Douglas Gregor, Nicolai M. Josuttis, David Vandevoorde; Publisher: Addison-Wesley Professional; September 2017  
https://en.cppreference.com/w/cpp/language/template_parameters

