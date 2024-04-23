#include <stdio.h>


// See:
//     https://en.cppreference.com/w/c/language/initialization
//     https://en.cppreference.com/w/c/language/scalar_initialization
//     https://en.cppreference.com/w/c/language/array_initialization
//     https://en.cppreference.com/w/c/language/struct_initialization


struct example;
void print_struct(char message[], struct example *s);


// File scope objects have extern storage-class by default
// Thus static duration and are empty initialized
int i;      // initialized to 0
int arr[3]; // initialized to {0, 0, 0}

struct example
{
    unsigned char a;
    float b[2];
    union {
        int val;
        unsigned char bytes[sizeof(int)];
    } c;
    struct example *next;
} example0; // initialized to {0, {0.0, 0.0}, {0}, NULL}


int main(void)
{
    // Block scope objects have auto storage-class by default
    // Automatic storage objects are initialized to indeterminate values
    int i;        // initialized to garbage value
    static int j; // initialized to 0


    // ARRAY INITIALIZATION
    char name[] = "Cornelio"; // character arrays can be initialized using string literals
    printf("%s\n", name);

    // VLAs cannot be initialized
    // unsigned char bytes[prinft("1234")] = {0x12, 0x34, 0x56, 0x78};

    // The following is only available starting from the C23 standard
    // int values[3] = {};

    int trio[3] = {0};                     // initialized to {0, 0, 0}
    int quartet[4] = {[2]=3, 4, [0]=1, 2}; // initialized to {1, 2, 3, 4}


    // CODE EXTRACTED FROM https://en.cppreference.com/w/c/language/array_initialization
    // The following four array declarations are the same
    short q1[4][3][2] = {
        { 1 },
        { 2, 3 },
        { 4, 5, 6 }
    };

    short q2[4][3][2] = {1, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 4, 5, 6};

    short q3[4][3][2] = {
        {
            { 1 },
        },
        {
            { 2, 3 },
        },
        {
            { 4, 5 },
            { 6 },
        }
    };
 
    short q4[4][3][2] = {1, [1]=2, 3, [2]=4, 5, 6};

    // Character names can be associated with enumeration constants
    // using arrays with designators:
    enum { RED, GREEN, BLUE };
    const char *nm[] = {
        [RED] = "red",
        [GREEN] = "green",
        [BLUE] = "blue",
    };


    // STRUCT AND UNION INITIALIZATION
    print_struct("struct example0", &example0);

    struct example example1 = {
        .c=69, // initializes first union member
        .a=15, 
    }; // initialized to {15, {0.0, 0.0}, {69}, NULL}
    print_struct("struct example1", &example1);

    struct example example2 = {
        15,
        {40.0, 50.0},
        .c.bytes[0]=0x12, 0x34, 0x56, 0x78,
        &example1
    }; // initialized to {15, {40.0, 50.0}, {0x12, 0x34, 0x56, 0x78}, &example1}
    print_struct("struct example2", &example2);

    struct example example3 = {
        .c.bytes[2]=0x12, 0x34,
        &example2,
        .a=69,
        .b[1]=50.0
    }; // initialized to {69, {0.0, 50.0}, {0x00, 0x00, 0x12, 0x34}, &example2}
    print_struct("struct example3", &example3);

    struct example example4 = {
        .c.bytes={0x12, 0x34, 0x56, 0x78}, // initializes second union member to {0x12, 0x34, 0x56, 0x78}
        .c.bytes[1] = 0x00, // changes second element of second union member to 0x00
        .c.bytes={0x00} // changes all elements of second union member to 0x00
    }; // initialized to {0, {0.0, 0.0}, {0x00, 0x00, 0x00, 0x00}, NULL}
    print_struct("struct example4", &example4);
}


void print_struct(char message[], struct example *s)
{
    printf("%s : ", message);
    printf("{%d, {%f, %f}, {%d, {%X", s->a, s->b[0], s->b[1], s->c.val, s->c.bytes[0]);
    for (int i = 1; i < sizeof(int); i++)
        printf(", %X", s->c.bytes[i]);
    fputs("}}", stdout);
    printf(", %p}\n", (void *)s->next);
}
