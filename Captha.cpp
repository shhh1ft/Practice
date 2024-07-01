#include "Captha.h"
#include <random>

Captcha::Captcha() {
    generateCaptcha();
}

std::string Captcha::getCaptcha() const {
    return captcha;
}

bool Captcha::verifyCaptcha(const std::string& input) const {
    return input == captcha;
}

void Captcha::generateCaptcha() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    captcha.clear();
    for (int i = 0; i < 6; ++i) {
        captcha += alphanum[dis(gen)];
    }
}
