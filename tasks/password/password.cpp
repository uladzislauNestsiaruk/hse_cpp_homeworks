#include "password.h"

constexpr size_t MinPasswordLength = 8;
constexpr size_t MaxPasswordLength = 14;
constexpr int8_t MinPasswordCharacterCode = 33;
constexpr int8_t MaxPasswordCharacterCode = 126;

bool ValidatePassword(const std::string& password) {
    int8_t lower_case_letters = 0;
    int8_t capital_letters = 0;
    int8_t digits = 0;
    int8_t other_characters = 0;
    for (size_t i = 0; i < password.size(); i++) {
        if (password[i] < MinPasswordCharacterCode || password[i] > MaxPasswordCharacterCode) {
            return false;
        }
        if (password[i] >= 'a' && password[i] <= 'z') {
            lower_case_letters = 1;
        } else if (password[i] >= 'A' && password[i] <= 'Z') {
            capital_letters = 1;
        } else if (password[i] >= '0' && password[i] <= '9') {
            digits = 1;
        } else {
            other_characters = 1;
        }
    }
    return ((lower_case_letters + capital_letters + digits + other_characters) > 2) &&
           password.size() >= MinPasswordLength && password.size() <= MaxPasswordLength;
}
