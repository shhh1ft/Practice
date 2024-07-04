#include <iostream>
#include <Windows.h>
#include "Register.h"
#include "Captha.h"
#include "Auth.h"
#include "ParSystem.h"


void showInitialMenu() {
    std::cout << "\nМеню:\n"
        "1. Регистрация\n"
        "2. Авторизация\n"
        "3. Выход\n"
        "Выберите действие: ";
}

void showMainMenu() {
    std::cout << "\nМеню:\n"
        "1. Установить системный параметр\n"
        "2. Получить системный параметр\n"
        "3. Выход\n"
        "Выберите действие: ";
}

void handleRegistration(Auth& auth) {
    try {
        std::string username, password;
        std::cout << "Введите имя пользователя для регистрации: ";
        std::cin >> username;
        std::cout << "Введите пароль: ";
        std::cin >> password;

        RegistrationData regData;
        regData.setUsername(username);
        regData.setPassword(password);

        auth.registerUser(regData.getUsername(), regData.getPassword());
        
        std::cout << "Регистрация успешна. Пожалуйста, авторизуйтесь.\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка регистрации: " << e.what() << std::endl;
    }
}


bool handleLogin(Auth& auth) {
    try {
        std::string username, password;
        std::cout << "Введите имя пользователя: ";
        std::cin >> username;
        std::cout << "Введите пароль: ";
        std::cin >> password;

        bool loggedIn = auth.login(username, password);
        std::cout << loggedIn;
        if (loggedIn) {
            std::cout << "Авторизация успешна.\n";
            return true;
        }
        else {
            std::cout << "Ошибка авторизации.\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка авторизации: " << e.what() << std::endl;
        return false;
    }
}

bool handleCaptcha() {
    try {
        Captcha captcha;
        std::string captchaCode = captcha.getCaptcha();
        std::string input;

        std::cout << "Капча: " << captchaCode << "\n";
        std::cout << "Введите капчу: ";
        std::cin >> input;

        if (captcha.verifyCaptcha(input)) {
            std::cout << "Капча введена правильно.\n";
            return true;
        }
        else {
            std::cout << "Капча введена неправильно.\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка проверки капчи: " << e.what() << std::endl;
        return false;
    }
}

void handleSetSystemParameter(SystemParameters& sysParams) {
    try {
        std::string key, value;
        std::cout << "Введите имя параметра: ";
        std::cin >> key;
        std::cout << "Введите значение параметра: ";
        std::cin >> value;

        sysParams.setParameter(key, value);
        std::cout << "Параметр установлен.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка установки параметра: " << e.what() << std::endl;
    }
}

void handleGetSystemParameter(SystemParameters& sysParams) {
    try {
        std::string key;
        std::cout << "Введите имя параметра: ";
        std::cin >> key;

        std::string value = sysParams.getParameter<std::string>(key);
        std::cout << "Значение параметра " << key << ": " << value << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка получения параметра: " << e.what() << std::endl;
    }
}

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "rus");

    Auth auth;
    SystemParameters sysParams;

    bool isAuthenticated = false;
    bool isCaptchaPassed = false;

    while (true) {
        if (!isAuthenticated) {
            showInitialMenu();
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                handleRegistration(auth);
                break;
            case 2:
                if (handleLogin(auth)) {
                    if (handleCaptcha()) {
                        isAuthenticated = true;
                        isCaptchaPassed = true;
                    }
                    else {
                        std::cout << "Повторите авторизацию.\n";
                    }
                }
                break;
            case 3:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cerr << "Неверный выбор. Пожалуйста, выберите снова.\n";
            }
        }
        else if (isAuthenticated && isCaptchaPassed) {
            showMainMenu();
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                handleSetSystemParameter(sysParams);
                break;
            case 2:
                handleGetSystemParameter(sysParams);
                break;
            case 3:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cerr << "Неверный выбор. Пожалуйста, выберите снова.\n";
            }
        }
    }
    return 0;
}
