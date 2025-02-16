#include <stdio.h>
#include <stdlib.h>

typedef int array_t[5];

int main(void)
{
    // 1-dimensional array
    // `my_array_1d` evaluates to the address of it's first element
    // I.e. the address of an object of type `int`
    array_t my_array_1d;
    for (int i = 0; i < 5; i++)
    {
        my_array_1d[i] = i * i;
        printf("my_array_1d[%d] = %d\n", i, my_array_1d[i]);
    }
    // 2-dimensional array
    // De-referencing `my_array_2d` returns an array of `int` elements
    // An array of `int` elements is the same as the address of it's first element
    // I.e. the address of an object of type `int`
    array_t *my_array_2d = calloc(2, sizeof(array_t));
    for (int i = 0; i < 2; i++)
    {
        printf("[Row %d]\n", i);
        for (int j = 0; j < 5; j++)
        {
            if (!i)
                my_array_2d[i][j] = my_array_1d[j];
            else
                my_array_2d[i][j] = i + j;
            printf("my_array_2d[%d][%d] = %d\n", i, j, my_array_2d[i][j]);
        }
    }
    // Acessing `my_array_2d[1][0]` in different ways using pointer notation
    printf("[Row 1 / Column 0]\n");
    printf("my_array_2d[1][0] = %d\n", *(*(my_array_2d + 1) + 0));
    printf("my_array_2d[1][-] = %d\n", *(int *)(my_array_2d + 1));
    printf("my_array_2d[0][5] = %d\n", *(*(my_array_2d + 0) + 5));
    printf("my_array_2d[-][5] = %d\n", *((int *) my_array_2d + 5));
    free(my_array_2d);
}
