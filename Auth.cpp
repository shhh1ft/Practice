#include "Auth.h"
#include <stdexcept>

void Auth::registerUser(const std::string& username, const std::string& password) {
    if (users.count(username) > 0) {
        throw std::runtime_error("User already exists");
    }
    users[username] = password;
}
// Auth 
bool Auth::login(const std::string& username, const std::string& password) const {
    auto it = users.find(username);
    if (it == users.end() || it->second != password) {
        return false;
    }
    return true;
}

