#include <math.h>
#include <stdio.h>


// See:
//     https://en.cppreference.com/w/c/language/name_space
//     https://stackoverflow.com/questions/51028650/why-does-c-have-separate-name-spaces-for-tags-and-identifiers
//     https://en.cppreference.com/w/c/language/enum


// Namespaces:
// (1) Label namespace
//     Identifiers used as operands of the goto operator
// (2) Tag namespace
//     Namespace for identifiers introduced by `struct`, `union`, and `enum` keywords
// (3) Member namespace
//     Namespace for identifiers that are members of `struct` or `union` objects
//     Each `struct` and `union` object introduces its own member namespace
// (4) Global attribute namespace
//     Namespace for standard and implementation-defined attributes
// (5) Attribute prefix namespace
//     Namespace for attribute prefixes
// (6) Ordinary namespace
//     Namespace for all other identifiers
//     Function names, object names, typedef names, enumeration constants


struct node { // introduces `node` to tag namespace (file-scope)
    // `value`, `left`, and `right` are in the `struct node` members namespace
    int value;
    struct node *left;
    struct node *right;
} root = {0, NULL, NULL}; // `root` is in the ordinary namespace (file-scope)


// introduces `node` in the ordinary namespace (file-scope)
// `struct node` and `node` are equivalent, but are names inside different namespaces
// `node` is easier to hide by a local-scope identifier in the ordinary namespace
// `struct node` can be hidden only by local-scope struct, union, or enum no-typedef definitions
typedef struct node node;


// enum constants aren't struct/union members
// enum definitions inside struct/union have the same scope as the struct/union
typedef struct {
    int numerator;
    unsigned int denominator;
    unsigned short precision;
    // `diverror` introduced in tag namespace (file-scope)
    enum diverror {ZERO_DIV, NOT_EXACT, DENOM_OVERFLOW, NUMER_OVERFLOW} errortype;
} rational; // introduces `rational` to ordinary namespace (file-scope)

enum diverror diverror;


// name collision in ordinary namespace
// float root(float value) { return sqrtf(value); }


int main(void)
{
    int loop = 0;
loop:
    loop++;
    if (loop < 10) { goto loop; }
    printf("loop = %d\n", loop);

    // hides file-scope `node`
    node node = { 50, NULL, NULL };
    root.right = &node;
    printf("root = { value=%d, left=%p, right=%p }\n",
           root.value, root.left, root.right);

    // `enum diverror` is available at file-scope
    diverror = NOT_EXACT;
    rational adivision = { 1, 3, 10, diverror };
    printf("adivision = { numer=%d, denom=%u, precision=%u, error=%u }\n",
           adivision.numerator, adivision.denominator,
           adivision.precision, adivision.errortype);
}
