#include <iostream>
#include <Windows.h>
#include "Register.h"
#include "Captha.h"
#include "Auth.h"
#include "ParSystem.h"


int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "rus");
    try {
        // Регистрация
        RegistrationData regData;
        regData.setUsername("user1");
        regData.setPassword("qwerty123");

        // Капча
        Captcha captcha;
        std::string captchaCode = captcha.getCaptcha();
        std::cout << "Капча: " << captchaCode << std::endl;

        // Авторизация
        Auth auth;
        auth.registerUser(regData.getUsername(), regData.getPassword());
        bool loggedIn = auth.login("user2", "password123");
        std::cout << "В: " << std::boolalpha << loggedIn << std::endl;

        // Системные параметры
        SystemParameters sysParams;
        sysParams.setParameter("max_users", "100");
        int maxUsers = sysParams.getParameter<int>("max_users");
        std::cout << "Максимальное число пользователей: " << maxUsers << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
