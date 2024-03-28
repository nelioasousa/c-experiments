#include <stdio.h>

// Compiler does not complain about the following redeclaration
// See:
//     https://en.cppreference.com/w/c/language/declarations#Redeclaration
static int n;       // zero-initialized
static int n = 10;  // first initialization


// inline const int get(void) { return 2; }


int main(void)
{
    // Attempt to skip declarations
    goto bypass;

    // Only const expressions can initialize a static object
    // See:
    //     https://stackoverflow.com/q/3025050/16969525
    //     https://stackoverflow.com/q/30962512/16969525
    static int x;  // zero-initialized
    static int y = 69;
    // static int z = get();  // error or warning

    // See:
    //     https://stackoverflow.com/q/18140552/16969525
bypass:
    printf("x = %d\n", x);
    printf("y = %d\n", y);
}
