#pragma once
#include <string>

class RegistrationData {
public:
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);

    std::string getUsername() const;
    std::string getPassword() const;

private:
    std::string username;
    std::string password;
};
