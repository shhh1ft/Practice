#pragma once
#include <string>
#include <map>

class Auth {
public:
    void registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password) const;

private:
    std::map<std::string, std::string> users;
};
