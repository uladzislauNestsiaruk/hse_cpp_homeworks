#include "reduce_fraction.h"
#include <iostream>
using std::swap;
int64_t Gcd(int64_t a, int64_t b) {
    if (a > b) {
        swap(a, b);
    }
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t gcd = Gcd(numerator, denominator);
    return (numerator + denominator) / gcd;
}
