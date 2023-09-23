#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t right_pos = str.size() - 1;
    size_t string_size = str.size();
    for (size_t i = 0; i < string_size; ++i) {
        if (str[i] == ' ') {
            continue;
        }
        while (str[right_pos] == ' ') {
            --right_pos;
        }
        if (str[i] != str[right_pos]) {
            return false;
        }
        --right_pos;
    }
    return true;
}
