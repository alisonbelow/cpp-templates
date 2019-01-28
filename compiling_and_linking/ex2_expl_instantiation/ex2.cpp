#include "ex2.h" 

// Definition
template<typename T> 
void f() {}

// Explicit instantiation = can use with int, double, bool
template void f<int> ();
template void f<double> ();
template void f<bool> ();