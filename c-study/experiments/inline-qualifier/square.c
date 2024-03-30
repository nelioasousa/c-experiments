#include "square.h"

// Removing the next code line produces a linker error in case
// the compiler didn't perform inline expansion (or calls to the
// address of square() exist in the code).
// Removing it is also a way to ensure inlining.
// If inline expansion is performed, this declaration will produce unreachable
// code, making the executable larger without necessity.
extern inline int square(int x);
