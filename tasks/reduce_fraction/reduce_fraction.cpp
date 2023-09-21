#include "reduce_fraction.h"

#include <algorithm>

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    return (numerator + denominator) / std::__gcd(numerator, denominator);
}