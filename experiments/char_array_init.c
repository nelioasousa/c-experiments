#include <stdio.h>
#include <string.h>

int main(void)
{
    // char str[] = "Fox";
    //     Compiler bounds str to 4 elements
    //     strlen returns 3
    //     str[3] is NUL
    // char str[3] = "Fox";
    //     Debugger doesn't complain
    //     NUL char do not overflow -> str[3] isn't NUL
    //     strlen returns 3
    // char str[3] = "Fox\0";
    //     Debugger complains about the size of the string
    //     strlen returns 3
    //     NUL char do not overflow -> str[3] isn't NUL
    // char str[5] = "Fox";
    //     strlen returns 3
    //     str[3] is NUL

    char str[] = "Fox";

    // Sizes of arrays are stored where?
    size_t str_size = sizeof(str) / sizeof(char);

    // strlen checks both the array bound and the NUL terminator
    size_t str_len = strlen(str);

    printf("str = %s; size = %d; len = %d\n", str, str_size, str_len);
    printf("3rd char is %c; 4th is NUL? %d", str[2], str[3] == '\0');
}
