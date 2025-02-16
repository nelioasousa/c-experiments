#include <stdio.h>
#include <stdalign.h>

// See:
//     https://cse.buffalo.edu/~eblanton/course/cse220-2020-2f/materials/11-alignment.pdf
//     https://en.cppreference.com/w/c/language/object
//     https://www.quora.com/Computer-Architecture-How-does-hardware-support-for-unaligned-memory-access-work-on-modern-processors

// required size is 1 + 8 + 4 * 2 = 17 bytes
// 7 padding bytes after `errcode` member
// packed size is 24 bytes
typedef struct {
    char errcode;    // 1 byte
    double result;   // usually 8 bytes
    int numerator;   // usually 4 bytes
    int denominator; 
} division; // aligment is 8, stride is 24

// required size is 1 * 3 = 3 bytes
// no padding is added at the end of struct color
// packed size is also 3 bytes
typedef struct {
    unsigned char red;   // 1 byte
    unsigned char green; // 1 byte
    unsigned char blue;  // 1 byte
} color; // aligment is 1 byte, stride is 3

// required size is 4 + 1 = 5 bytes
// no padding between elements
// 3 bytes of padding at the end of struct
// packed size is 8 bytes
typedef struct {
    int size;  // usually 4 byte
    char elem; // 1 byte
} charcount;   // aligment is 4, stride is 8

int main(void)
{
    division divisions[2];
    divisions[0].numerator = 64;
    divisions[0].denominator = 16;
    divisions[0].result = 64.0 / 16.0;
    divisions[0].errcode = 0;
    divisions[1].numerator = 78;
    divisions[1].denominator = 0;
    divisions[1].errcode = 1;

    color colors[2];
    colors[0].red = 0;
    colors[0].green = 0;
    colors[0].blue = 0;
    colors[1].red = 255;
    colors[1].green = 255;
    colors[1].blue = 255;

    charcount reps[2];
    reps[0].size = 20;
    reps[0].elem = 'K';
    reps[1].size = 50;
    reps[1].elem = 'A';

    printf("size of   struct division: %i\n", sizeof(division));
    printf("align of  struct division: %i\n", alignof(division));
    printf("stride of struct division: %i\n\n", (size_t) &divisions[1] - (size_t) &divisions[0]);

    printf("size of   struct color: %i\n", sizeof(color));
    printf("align of  struct color: %i\n", alignof(color));
    printf("stride of struct color: %i\n\n", (size_t) &colors[1] - (size_t) &colors[0]);

    printf("size of   struct charcount: %i\n", sizeof(charcount));
    printf("align of  struct charcount: %i\n", alignof(charcount));
    printf("stride of struct charcount: %i\n", (size_t) &reps[1] - (size_t) &reps[0]);
}

/* Possible output:

size of   struct division: 24
align of  struct division: 8
stride of struct division: 24

size of   struct color: 3
align of  struct color: 1
stride of struct color: 3

size of   struct color: 8
align of  struct color: 4
stride of struct color: 8

*/
