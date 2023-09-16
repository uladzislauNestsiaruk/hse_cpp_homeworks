#include "is_leap.h"
#include <cstdint>
const int16_t FOUR = 4;
const int16_t HUNDRED = 100;
const int16_t FOUR_HUNDRED = 400;
bool IsLeap(int year) {
    return (year % FOUR_HUNDRED == 0) || (year % FOUR == 0 && year % HUNDRED > 0);
}
