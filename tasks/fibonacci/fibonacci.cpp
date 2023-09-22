#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t fibonacci_previous = 0;
    int64_t fibonacci_current = 1;
    for (int64_t i = 2; i <= n + 1; ++i) {
        fibonacci_current += fibonacci_previous;
        fibonacci_previous = fibonacci_current - fibonacci_previous;
    }
    return fibonacci_previous;
}
