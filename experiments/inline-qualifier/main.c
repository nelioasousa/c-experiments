#include "square.h"
#include <stdio.h>

// See:
//     https://en.cppreference.com/w/c/language/inline
//     https://en.cppreference.com/w/c/language/storage_duration
//     https://stackoverflow.com/q/216510/16969525
//     https://stackoverflow.com/q/62475308/16969525
//     https://stackoverflow.com/q/51533082/16969525
//     https://stackoverflow.com/q/51737002/16969525

int main(void)
{
    int value = 3;

    // square() is implemented for inlining,
    // but it's up to the compiler to perform inline expansion or not.
    // If it does not perform inlining and function calls remain in the code,
    // the C standard requires an external definition to exist.
    // From what I understand, this definition is needed because functions with only
    // the `inline` qualifier do not generate a function object visible to the linker
    // and the compiler let's those identifier to be resolved by the linker.
    printf("Square of %d is %d\n", value, square(value));

    // square_accumulator() is defined as `static inline`.
    // `inline` functions declared with `static` or `extern` generates
    // a function object with internal or external linkage, respectively.
    // If inlining is not performed, there'll be a internal reference to square_accumulator()
    printf("Accumulator is now in %d\n", square_accumulator(value));
    return 0;
}
