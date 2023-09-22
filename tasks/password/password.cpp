#include "password.h"

bool ValidatePassword(const std::string& password) {
    const size_t min_password_length = 8;
    const size_t max_password_length = 14;
    const int8_t min_password_character_code = 33;
    const int8_t max_password_character_code = 126;
    const int8_t a_ascii = 97;
    const int8_t z_ascii = 122;
    const int8_t capital_a_ascii = 65;
    const int8_t capital_z_ascii = 90;
    const int8_t zero_ascii = 48;
    const int8_t nine_ascii = 57;
    if (password.size() < min_password_length || password.size() > max_password_length) {
        return false;
    }
    int8_t lower_case_letters = 0;
    int8_t capital_letters = 0;
    int8_t digits = 0;
    int8_t other_characters = 0;
    for (size_t i = 0; i < password.size(); i++) {
        if (password[i] < min_password_character_code || password[i] > max_password_character_code) {
            return false;
        }
        if (password[i] >= a_ascii && password[i] <= z_ascii) {
            lower_case_letters = 1;
        } else if (password[i] >= capital_a_ascii && password[i] <= capital_z_ascii) {
            capital_letters = 1;
        } else if (password[i] >= zero_ascii && password[i] <= nine_ascii) {
            digits = 1;
        } else {
            other_characters = 1;
        }
    }
    return (lower_case_letters + capital_letters + digits + other_characters) > 2;
}
