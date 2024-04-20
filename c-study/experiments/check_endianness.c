#include <stdio.h>

// See:
//     https://developer.ibm.com/articles/au-endianc/
//     https://en.wikipedia.org/wiki/Endianness

int is_bigendian()
{
    int one = 0x01;
    return *(char *)&one == 0;
}

void show_endianness(int val)
{
    char *byte = (char *)&val;
    printf("Number %d in hex: %X\n", val, val);
    printf("Byte order in memory:");
    for (int i = 0; i < sizeof(int); i++)
        printf(" %X", byte[i]);
    puts("");
}

int main(void)
{
    if (is_bigendian())
        printf("Big-endian architecture!\n");
    else
        printf("Little-endian architecture!\n");
    show_endianness(0x12345678); // Assuming 4-byte integers
}
