#include <stdio.h>
#include <time.h>


// Runned with: -pedantic -Wall -Werror -O2


// See:
//     https://youtu.be/6tIWFEzzx9I?si=sTn9WeO090n_eMTB
//     https://youtu.be/W3pFxSBkeJ8?si=UN25iQsDFFEwLjqF
//     https://en.cppreference.com/w/c/language/eval_order
//     https://stackoverflow.com/q/62150971/16969525
//     https://stackoverflow.com/q/51130081/16969525
//     https://en.cppreference.com/w/c/language/volatile


// Note:
//     A good read. Is simple to understand, but kinda complex to use effectively.
//     For now I will just share a code snippet from cppreference.


// Extracted from https://en.cppreference.com/w/c/language/volatile
int main(void)
{
    clock_t t = clock();
    double d = 0.0;
    for (int n = 0; n < 10000; ++n)
        for (int m = 0; m < 10000; ++m)
            d += d * n * m; // reads from and writes to a non-volatile 
    printf("Modified a non-volatile variable 100m times. "
           "Time used: %.2f seconds\n",
           (double)(clock() - t)/CLOCKS_PER_SEC);
 
    t = clock();
    volatile double vd = 0.0;
    for (int n = 0; n < 10000; ++n)
        for (int m = 0; m < 10000; ++m) {
            double prod = vd * n * m; // reads from a volatile
            vd += prod; // reads from and writes to a volatile
        } 
    printf("Modified a volatile variable 100m times. "
           "Time used: %.2f seconds\n",
           (double)(clock() - t)/CLOCKS_PER_SEC);
}
