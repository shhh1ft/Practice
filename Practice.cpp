#include <iostream>
#include <limits>
#include <Windows.h>
#include "Register.h"
#include "Captha.h"
#include "Auth.h"
#include "ParSystem.h"

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "rus");

    try {
        int choice;
        while (true) {
            std::cout << "Меню:" << std::endl;
            std::cout << "1. Регистрация" << std::endl;
            std::cout << "2. Авторизация" << std::endl;
            std::cout << "3. Системные параметры" << std::endl;
            std::cout << "4. Выход из меню" << std::endl;
            std::cout << "Выберите действие (1-4): ";
            std::cin >> choice;

            switch (choice) {
            case 1: {
                RegistrationData regData;
                std::string user_name;
                std::string user_pass;
                std::cout << "Введите имя пользователя" << '\n';
                std::cin >> user_name;
                std::cout << "Введите пароль" << '\n';
                std::cin >> user_pass;
                regData.setUsername(user_name);
                regData.setPassword(user_pass);

                // Капча
                Captcha captcha;
                std::string captchaCode = captcha.getCaptcha();
                std::cout << "Капча: " << captchaCode << std::endl;

                std::string input;
                std::cout << "Введите капчу: ";
                std::cin >> input;

                bool captchaPassed = captcha.verifyCaptcha(input);
                if (!captchaPassed) {
                    std::cerr << "Неверная капча. Регистрация не удалась." << std::endl;

                    // Капча попытки
                    int attempts = 0;
                    bool captchaPassed = false;
                    while (attempts < 3 && !captchaPassed) {
                        try {
                            Captcha captcha;
                            std::string captchaCode = captcha.getCaptcha();
                            std::cout << "Капча: " << captchaCode << std::endl;

                            std::string input;
                            std::cout << "Введите капчу: ";
                            std::cin >> input;

                            captchaPassed = captcha.verifyCaptcha(input);
                            if (!captchaPassed) {
                                std::cout << "Неверная капча. Попробуйте ещё раз." << std::endl;
                                attempts++;
                            }
                        }
                        catch (const std::exception& e) {
                            std::cerr << "Ошибка капчи: " << e.what() << std::endl;
                            attempts++;
                        }
                    }

                    if (!captchaPassed) {
                        throw std::runtime_error("Превышено количество попыток ввода капчи.");
                    }
                    break;
                }

                std::cout << "Пользователь зарегистрирован." << std::endl;
                break;
            }
            case 2: {
                Auth auth;
                std::string username, password;
                std::cout << "Введите имя пользователя: ";
                std::cin >> username;
                std::cout << "Введите пароль: ";
                std::cin >> password;

                bool loggedIn = auth.login(username, password);
                std::cout << "Успешная авторизация: " << std::boolalpha << loggedIn << std::endl;
                break;
            }
            case 3: {
                SystemParameters sysParams;
                sysParams.setParameter("max_users", "100");
                int maxUsers = sysParams.getParameter<int>("max_users");
                std::cout << "Максимальное число пользователей: " << maxUsers << std::endl;
                break;
            }
            case 4: {
                return 0;
                break;
            }
            default:
                std::cerr << "Неверный выбор. Попробуйте ещё раз." << std::endl;
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                continue;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
