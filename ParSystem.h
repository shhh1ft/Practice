#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>

class SystemParameters {
public:
    void setParameter(const std::string& key, const std::string& value);
    template<typename T>
    T getParameter(const std::string& key) const;

private:
    std::map<std::string, std::string> systemParams;
};


template<typename T>
T SystemParameters::getParameter(const std::string& key) const {
    auto it = systemParams.find(key);
    if (it == systemParams.end()) {
        throw std::runtime_error("Системный параметр не найден");
    }
    std::istringstream iss(it->second);
    T result;
    if (!(iss >> result)) {
        throw std::runtime_error("Неверный ввод");
    }
    return result;
}
