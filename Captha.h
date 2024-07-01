#pragma once
#include <string>

class Captcha {
public:
    Captcha();
    std::string getCaptcha() const;
    bool verifyCaptcha(const std::string& input) const;

private:
    void generateCaptcha();
    std::string captcha;
};
