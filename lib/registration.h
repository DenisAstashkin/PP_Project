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
        else if (c >= '�' && c <= '�') {
            char encodedChar = (c - '�' + KEY) % 32 + '�';
            result += encodedChar;
        }
        else if (c >= '�' && c <= '�') {
            char encodedChar = (c - '�' + KEY) % 32 + '�';
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
        else if (c >= '�' && c <= '�') {
            char decodedChar = (c - '�' - KEY + 32) % 32 + '�';
            result += decodedChar;
        }
        else if (c >= '�' && c <= '�') {
            char decodedChar = (c - '�' - KEY + 32) % 32 + '�';
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

    while (std::getline(fout, line)) {  // ������ ���� ���������
        std::istringstream iss(line);
        iss >> currentLogin >> password;  // ��������� ����� � ������ �� ������
        if (currentLogin == login) {
            return true; 
        }
    }
    return false;  // ����� �� ������
}
void registrate(std::string login, std::string pass, std::string registrationFile) {
    std::ifstream fin(registrationFile);
    if (isLoginInBase(encode(login), fin)) {
        std::cerr << "Login is already exist";
        fin.close();
        return;
    }
    fin.close();
    std::ofstream fout(registrationFile, std::ios_base::app);
    if (!fout.is_open()) {
        std::cerr << "Error opening file: " << registrationFile << std::endl;
        return;
    }

    std::string first = encode(login);
    std::string second = encode(pass);

    if (first.empty() || second.empty()) {
        std::cerr << "Error: encoded login or password is empty." << std::endl;
        return;
    }

    fout << first << " " << second << "\n";
    if (!fout) {
        std::cerr << "Error writing to file." << std::endl;
    }
}






