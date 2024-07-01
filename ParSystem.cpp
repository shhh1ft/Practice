#include "ParSystem.h"

void SystemParameters::setParameter(const std::string& key, const std::string& value) {
    systemParams[key] = value;
}
