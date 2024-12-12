#pragma once 

#include <fstream>
#include <string>
#include "../model/constants.h"
#include <iostream>
#include <sstream>
std::string encode(std::string text) {
    std::string result;
    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            char encodedChar = (c - 'A' + KEY) % 26 + 'A';
            result += encodedChar;
        }
        else if (c >= 'a' && c <= 'z') {
            char encodedChar = (c - 'a' + KEY) % 26 + 'a';
            result += encodedChar;
        }
        else if (c >= 'А' && c <= 'Я') {
            char encodedChar = (c - 'А' + KEY) % 32 + 'А';
            result += encodedChar;
        }
        else if (c >= 'а' && c <= 'я') {
            char encodedChar = (c - 'а' + KEY) % 32 + 'а';
            result += encodedChar;
        }
        else if (isdigit(c)) {
            char encodedChar = (c - '0' + KEY) % 10 + '0'; 
            result += encodedChar;
        }
        else {
            char encodedChar = c; 
            result += encodedChar;
        }
    }
    return result;
}

std::string decode(std::string text) {
    std::string result;
    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            char decodedChar = (c - 'A' - KEY + 26) % 26 + 'A';
            result += decodedChar;
        }
        else if (c >= 'a' && c <= 'z') {
            char decodedChar = (c - 'a' - KEY + 26) % 26 + 'a';
            result += decodedChar;
        }
        else if (c >= 'А' && c <= 'Я') {
            char decodedChar = (c - 'А' - KEY + 32) % 32 + 'А';
            result += decodedChar;
        }
        else if (c >= 'а' && c <= 'я') {
            char decodedChar = (c - 'а' - KEY + 32) % 32 + 'а';
            result += decodedChar;
        }
        else if (isdigit(c)) {
            char decodedChar = (c - '0' - KEY + 10) % 10 + '0'; 
            result += decodedChar;
        }
        else {
            char decodedChar = c;
            result += decodedChar;
        }
    }
    return result;
}
bool isLoginInBase(const std::string& login, std::ifstream& fout) {
    std::string line;
    std::string currentLogin, password;

    while (std::getline(fout, line)) {  // Читаем файл построчно
        std::istringstream iss(line);
        iss >> currentLogin >> password;  // Извлекаем логин и пароль из строки
        if (currentLogin == login) {
            return true; 
        }
    }
    return false;  // Логин не найден
}
int login_account(std::string login, std::string pass, std::string fileName) {
    std::ifstream fin(fileName);
    
    std::string currentLogin, currentPassword;
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        iss >> currentLogin >> currentPassword;
        if (decode(currentLogin) == login && decode(currentPassword) != pass) {
            fin.close();
            std::cout << "Неверный пароль\n";
            return 0;
        }
        if (decode(currentLogin) == login && decode(currentPassword) == pass) {
            std::cout << "Вы успешно вошли в аккаунт!\n";
            fin.close();
            return 1;
        }
    }
    fin.close();
    std::cout << "Такого пользователя нет в базе\n";
    return 0;
}

void login_interface() {
    std::string fileName = registrationFilename;
    
    while (true) {
        std::cout << "Вход в приложение....\n";
        std::string line;
        std::string login;
        std::string password;
        std::cout << "Введите логин и пароль: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> login >> password;
        int flag = login_account(login, password, registrationFilename);
        if (flag) break;

    }
}







