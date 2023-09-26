#include "password.h"

constexpr size_t MinPasswordLength = 8;
constexpr size_t MaxPasswordLength = 14;
constexpr int8_t MinPasswordCharacterCode = 33;
constexpr int8_t MaxPasswordCharacterCode = 126;

bool ValidatePassword(const std::string& password) {
    bool lower_case_letters = false;
    bool capital_letters = false;
    bool digits = false;
    bool other_characters = false;
    if (password.size() < MinPasswordLength && password.size() > MaxPasswordLength) {
        return false;
    }
    for (size_t i = 0; i < password.size(); i++) {
        if (password[i] < MinPasswordCharacterCode || password[i] > MaxPasswordCharacterCode) {
            return false;
        }
        if (password[i] >= 'a' && password[i] <= 'z') {
            lower_case_letters = true;
        } else if (password[i] >= 'A' && password[i] <= 'Z') {
            capital_letters = true;
        } else if (password[i] >= '0' && password[i] <= '9') {
            digits = true;
        } else {
            other_characters = true;
        }
    }
    return (lower_case_letters + capital_letters + digits + other_characters) > 2;
}
