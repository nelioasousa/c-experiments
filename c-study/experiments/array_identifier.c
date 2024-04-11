#include <stdio.h>

// See:
//     https://stackoverflow.com/q/2528318/16969525
//     https://stackoverflow.com/q/17820755/16969525
//     https://stackoverflow.com/q/17687429/16969525

int main(void)
{
    int arr[3] = {0, 1, 2};
    // `arr` is of type `int[3]` (array of 3 elements of type int)
    // `arr` isn't a common variable, it acts like a constant
    // It's hasn't its own address
    // `&arr` returns the address of the first element
    // The `int` type usually has a stride of 4 bytes:
    printf("arr      = %p -> %d\n", arr, *arr);
    printf("arr + 0  = %p -> %d\n", arr + 0, *(arr + 0));
    printf("arr + 1  = %p -> %d\n", arr + 1, *(arr + 1));
    printf("arr + 2  = %p -> %d\n", arr + 2, *(arr + 2));
    printf("arr + 3  = %p -> %d\n", arr + 3, *(arr + 3)); // Out of bounds
    // `&arr` is of type `int (*)[3]`
    // `&arr` is a pointer to array of 3 elements of type int
    // `&arr + 1` is the address of the next byte after the whole array
    printf("&arr + 1 = %p\n", &arr + 1);
    // `sizeof(arr)` is the size of the array
    printf("sizeof(arr)  = %i\n", sizeof(arr));
    // `sizeof(&arr)` is the size of a pointer
    printf("sizeof(&arr) = %i\n", sizeof(&arr));
}
