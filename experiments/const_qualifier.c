#include <stdio.h>
#include <string.h>

#define BUF_SIZE 200

// Runned with: -pedantic -Wall -O0

// See:
//     https://en.cppreference.com/w/c/language/const

// `const` type qualifier places objects in read-only mode
// This qualifier applies only to lvalue expressions
// The qualifier is dropped when a const qualified object is used in non-lvalue context
// `const` type qualifier allows certain optimizations by the compiler


struct message
{
    unsigned char ip[4];
    char message[BUF_SIZE];
} online = { {127, 0, 0, 1}, "hello?" };

const struct message _abort = { {127, 0, 0, 1} , "abort" };

struct example {const int x; int y; } example = {20, 30};

typedef int M2x2[2][2];


int main(void)
{
    strncpy(online.message, "anyone there?", BUF_SIZE); // Ok

    // Warning -Wdiscarded-qualifiers and Segmentation fault
    // strncpy(_abort.message, "never mind...", BUF_SIZE);

    example.y = 40;                         // Ok
    // example.x = 15;                      // Error
    // example = (struct example) {20, 30}; // Error

    // `struct` and `union` members acquires the qualifier of the container
    const struct example origin = {0, 0};
    // origin.y = 0; // Error

    // Until C23 only the array elements are const qualified
    // The array itself isn't const qualified
    // Since C23 the array and its elements are indentically qualified
    const M2x2 identity = { {1, 0}, {0, 1} };
    // identity[0][1] = 5;       // Error
    int (*matrix)[2] = identity; // Warning -Wdiscarded-array-qualifiers
    int *row = identity[0];      // Warning -Wdiscarded-qualifiers
    void *array = identity;      // Warning -Wdiscarded-array-qualifiers

    int *p = NULL;
    const int *cp = NULL;
    const int i = 69;
    cp = &i;  // Ok, types match
    p = &i;   // Warning -Wdiscarded-qualifiers
    *p = 100; // Undefined behavior

    return 0;
}
