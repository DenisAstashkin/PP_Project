#pragma once

#include "../model/constants.h"
#include "../model/Film.h"
#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>


bool validateName(const std::string& name) {
    std::regex pattern(R"([A-Za-zА-Яа-яЁё]{2,50})");
    return std::regex_match(name, pattern);
}
bool validatePhone(const std::string& phone) {
    std::regex pattern(R"((\+7|8)\d{10})");
    return std::regex_match(phone, pattern);
}
bool validateEmail(const std::string& email) {
    std::regex pattern(R"([^@\s]+@[^@\s]+\.[A-Za-z]{2,})");
    return std::regex_match(email, pattern);
}
bool validateAge(const std::string& age) {
    if (!std::regex_match(age, std::regex(R"(\d+)"))) return false;
    int ageInt = std::stoi(age);
    return ageInt >= 1 && ageInt <= 120;
}
bool validateDate(const std::string& date) {
    std::regex pattern(R"(\d{2}\.\d{2}\.\d{4})");
    return std::regex_match(date, pattern);
}
bool validateTime(const std::string& time) {
    std::regex pattern(R"((0\d|1\d|2[0-3]):[0-5]\d)");
    return std::regex_match(time, pattern);
}
bool validateSeat(const std::string& row, const std::string& seat) {
    if (!std::regex_match(row, std::regex(R"(\d+)")) || !std::regex_match(seat, std::regex(R"(\d+)"))) return false;
    int rowNum = std::stoi(row);
    int seatNum = std::stoi(seat);
    return rowNum >= 1 && rowNum <= MAX_ROW && seatNum >= 1 && seatNum <= MAX_COLUMN;
}
bool validateTicketCount(const std::string& count) {
    return std::regex_match(count, std::regex(R"(\d+)"));
}

std::vector<std::string> split(std::string s, const std::string& delimiter) {
	std::vector<std::string> tokens;
	std::size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);

	return tokens;
}


std::map<std::string, Film> parser(std::vector<std::string> lines) {		//Разделить и закинуть название и времена сеансов в структуру и сформировать словарь
	std::map<std::string, Film> Film_dates;
	for (std::string separate_str : lines) {

		std::string element;		//Элемент, который формируется посимвольно до знака ;
		Film data_Film;
		std::string date;
		short flag = 0;		//Флаг на первых два слова
		unsigned i = 0;

		while (flag < 2) {
			if (separate_str[i] != ';') {
				element.push_back(separate_str[i]);		//Дописать символ, если он не ;
			}
			else {
				switch (flag)
				{
				case 0:		//Дата
					date = element;
					break;
				case 1:		//Название фильма
					data_Film.name = element;
					break;
				default:
					break;
				}
				element = "";
				flag++;
			}
			i++;
		}
		separate_str.erase(0, i);		//Оставляем только время
		std::string time;
		std::vector<std::string> times;

		for (std::string time : split(separate_str, ","))
			data_Film.times.push_back(time);
		
		Film_dates[date] = data_Film;
	}

	return Film_dates;
}


std::map<std::string, Film> get_file_info(std::string path)		//Открытие файла и запись в словарь
{
	std::ifstream input_file;
	input_file.open(path);

	if (!(input_file.is_open()))		//Файл не открылся
	{
		std::cout << "Error file open";
		exit(1);
	}
	else {
		std::vector<std::string> lines;
		while (!input_file.eof())	//Пока не опустел
		{
			std::string separate_str;
			getline(input_file, separate_str);
			lines.push_back(separate_str);

		}
		input_file.close();
		return parser(lines);	//Составить словарь на основе множества фильмов
	}

}

int fulltime(std::string time)
{
	std::vector<std::string> hh_mm = split(time, ":");
	return stoi(hh_mm[0]) * 60 + stoi(hh_mm[1]);
}