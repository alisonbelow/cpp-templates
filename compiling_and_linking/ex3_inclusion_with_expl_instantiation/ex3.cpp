#include "ex3_def.h"

// Explicit instantiation = can use with int, double, bool
template void f<int> ();
template void f<double> ();
template void f<bool> ();