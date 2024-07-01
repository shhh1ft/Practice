#include "Register.h"
#include <regex>
#include <stdexcept>

void RegistrationData::setUsername(const std::string& username) {
    if (!std::regex_match(username, std::regex("^[a-zA-Z0-9_]{3,20}$"))) {
        throw std::runtime_error("Некорректный ввод");
    }
}

void RegistrationData::setPassword(const std::string& password) {
    if (password.length() < 6) {
        throw std::runtime_error("Пароль слишком короткий (минимальная длина пароля - 6 с.) ");
    }
}

std::string RegistrationData::getUsername() const {
    return username;
}

std::string RegistrationData::getPassword() const {
    return password;
}
