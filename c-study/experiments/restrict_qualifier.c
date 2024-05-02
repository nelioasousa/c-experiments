#include <stdio.h>


// Runned with: -pedantic -Wall -O2


// See:
//     https://en.cppreference.com/w/c/language/restrict
//     https://developers.redhat.com/blog/2020/06/02/the-joys-and-perils-of-c-and-c-aliasing-part-1
//     https://developers.redhat.com/blog/2020/06/03/the-joys-and-perils-of-aliasing-in-c-and-c-part-2


// Comments:
//     All objects in C must have a unique identity (address), i.e. any two objects cannot have the same
//     address. Aggregate types are an exception, since the address of the container object equals the address
//     of its first member.
//
//     In contrast to this, we can access the same object using different identifiers (references). The most
//     obvius example of this are pointers. An alias is a way of referencing an object using an identifier
//     other than it's name. Aliasing is a feature that comes with many risks, since accessing an object throw
//     many routes can led to unpredicted changes of state. This can impact performance and correctness of a
//     program. From the performance point-of-view, it can confuse the compiler and make it unable to optimize
//     certain portions of the code. From the correctness point-of-view, an with the help of already buggy code,
//     the compiler can make optimizations assuming the programmer did follow some general rules.
//
//     The `restrict` keyword exist to hint the compiler that an object (or a memory space) can be accessible
//     throw more than one route, but just one of those routes is used. That is, if both A and B can access a
//     certain object, the use of `restrict` tells the compiler to not worry because operations with A won't
//     influentiate operations on B and the other way around.


// `dst` and `org` represent two blocks of memory.
// These blocks can overlap depending on the args passed by the caller.
// If this overlap occurs in an ascending way, that is writes from `org` to `dst`
// overwrites upstream adresses of `org`, the result is unexpected.
// The use of `restrict` hints the compiler AND the programmer that `dst` and `org`
// do not (should not) overlap, so the compiler can optimize the code.
char *my_memcpy(char * restrict dst, const char * restrict org, size_t n)
{
    char *d = dst; // restrict qualifier isn't lost
    while (n-- > 0)
        *d++ = *org++;
    return dst;
}


// Snipper from https://developers.redhat.com/blog/2020/06/02/the-joys-and-perils-of-c-and-c-aliasing-part-1
// `a` and `b` can point to the same object
// Without the use of `restrict` the compiler will note that and be aware that the write `*b = 0;`
// can possibly alter the value of *a.
// Using `restrict` hints the compiler that this will never be the case and it can optimize freely.
// The first line could be removed and the return expression could be fouded to a constant 0.
int f (int * restrict a, int * restrict b)
{
    int t = *a;
    *b = 0;          // cannot change *a
    return *a - t;   // can be folded to zero
}


char m[50] = "I'm unique";
char n[50] = "We all are!";

int main(void)
{
    my_memcpy(m, n, 50);       // Ok
    my_memcpy(m + 20, m, 20);  // Ok
    my_memcpy(m + 20, m, 25);  // Ascending copy. Undefined behavior. No compiler warning!

    int p = 40;
    int q = 90;
    f(&p, &q); // Ok
    f(&p, &p); // Undefined behavior. Trigger a warning from gcc.
}
