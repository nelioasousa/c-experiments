#include <stdio.h>

// See: https://stackoverflow.com/q/2528318/16969525

int main(void)
{
    int arr[3] = {0, 1, 2};
    // `arr` is of type `int *`
    // stride is (usually) 4 byte
    printf("arr      = %p -> %d\n",    arr, *arr);
    printf("arr + 0  = %p -> %d\n",    arr + 0, *(arr + 0));
    printf("arr + 1  = %p -> %d\n",    arr + 1, *(arr + 1));
    printf("arr + 2  = %p -> %d\n",    arr + 2, *(arr + 2));
    printf("arr + 3  = %p -> %d\n", arr + 3, *(arr + 3));
    // `&arr` is of type `int (*)[3]`
    // stride is (usually) 3 * 4 = 12 bytes
    // `&arr + 1` is the address of the next byte after the array
    printf("&arr + 1 = %p\n", &arr + 1);
    // `sizeof(arr)` is the size of the array
    printf("sizeof(arr)  = %i\n", sizeof(arr));
    // `sizeof(&arr)` is the size of a pointer
    printf("sizeof(&arr) = %i\n", sizeof(&arr));
}
