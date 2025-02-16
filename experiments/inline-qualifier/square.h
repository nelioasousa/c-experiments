#ifndef SQUARE_H
#define SQUARE_H

inline int square(int x) { return x * x; }

static inline int square_accumulator(int value)
{
    static int total = 0;
    total += square(value);
    return total;
}

#endif
