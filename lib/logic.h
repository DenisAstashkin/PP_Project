#pragma once
#include "../model/constants.h"
#include "../model/Film.h"
#include "../model/Date.h"
#include "../model/Ticket.h"
#include "Converter.h"

#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

std::vector<std::string> split(std::string s, const std::string& delimiter) 
{
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

bool validateSeat(const std::string& row, const std::string& seat) 
{
	if (!std::regex_match(row, std::regex(R"(\d+)")) || !std::regex_match(seat, std::regex(R"(\d+)"))) return false;
	int rowNum = std::stoi(row);
	int seatNum = std::stoi(seat);
	return rowNum >= 1 && rowNum <= MAX_ROW && seatNum >= 1 && seatNum <= MAX_COLUMN;
}

bool validateName(const std::string& name) 
{
	std::regex pattern(R"([A-Za-zА-Яа-яЁё]{2,50})");
	return std::regex_match(name, pattern);
}

bool validatePhone(const std::string& phone) 
{
	std::regex pattern(R"((\+7|8)\d{10})");
	return std::regex_match(phone, pattern);
}

bool validateEmail(const std::string& email) 
{
	std::regex pattern(R"([^@\s]+@[^@\s]+\.[A-Za-z]{2,})");
	return std::regex_match(email, pattern);
}

bool validateAge(const std::string& age) 
{
	if (!std::regex_match(age, std::regex(R"(\d+)"))) return false;
	int ageInt = std::stoi(age);
	return ageInt >= 1 && ageInt <= 120;
}

bool validateDate(const std::string& date) 
{
	std::regex pattern(R"(\d{2}\.\d{2}\.\d{4})");
	return std::regex_match(date, pattern);
}

bool validateTime(const std::string& time) 
{
	std::regex pattern(R"((0\d|1\d|2[0-3]):[0-5]\d)");
	return std::regex_match(time, pattern);
}

bool validateTicketCount(const std::string& count) 
{
	return std::regex_match(count, std::regex(R"(\d+)"));
}

bool validate_date(const std::string& _dd_mm_yyyy)
{
	auto count_dot = [](const std::string& date)
		{
			int cnt = 0;
			for (int i = 0; i < date.length(); i++)
			{
				if (date[i] == '.')
					cnt++;
				if (cnt > 3)
					return false;
			}
			if (cnt != 3)
				return false;
			return true;
		};

	if (_dd_mm_yyyy.size() != 10)
		return false;

	if (count_dot(_dd_mm_yyyy))
		return false;

	std::vector<std::string> dd_mm_yyyy = split(_dd_mm_yyyy, ".");

	int dd = 0;
	int mm = 0;
	int yyyy = 0;

	if (string_to_int(dd_mm_yyyy[0], dd) && string_to_int(dd_mm_yyyy[1], mm))
	{
		if (dd >= 1 && dd <= 31 && mm >= 1 && mm <= 12)
			return true;
	}

	dd_mm_yyyy.clear();

	return false;
}

std::map<std::string, std::vector<Film>> parser(std::vector<std::string> lines) 
{		//��������� � �������� �������� � ������� ������� � ��������� � ������������ �������
	std::map<std::string, std::vector<Film>> Film_dates;
	for (std::string separate_str : lines) {
		if (separate_str != "")
		{
			auto data = split(separate_str, ";");
			Film data_Film;
			data_Film.name = data[1];
			for (auto i : split(data[2], ","))
			{
				data_Film.data.push_back(split(i, "-")[0]);
				data_Film.subdata.push_back(split(i, "-")[1]);
			}
			Film_dates[data[0]].push_back(data_Film);
		}
	}
	/*12.12.2024; Аватар 2; 11:00, 12 : 00, 16 : 00
		13.12.2024; Принц Персии 1; 11:00, 12 : 00, 16 : 00
		13.12.2024; Принц Персии 2; 11:00, 12 : 00, 16 : 00
		13.12.2024; Принц; 11:00, 12 : 00, 16 : 00
		14.12.2024; Принц Персии 1; 11:00, 12 : 00, 16 : 00
		14.12.2024; Принц Персии 2; 11:00, 12 : 00, 16 : 00
		14.12.2024; Принц; 11:00, 12 : 00, 16 : 00*/
	return Film_dates;
}

std::map<std::string, std::vector<Film>> get_file_info(std::string path)		//�������� ����� � ������ � �������
{
	std::ifstream input_file;
	input_file.open(path);

	if (!(input_file.is_open()))		//���� �� ��������
	{
		std::cout << "Error file open";
		exit(1);
	}
	else
	{
		std::vector<std::string> lines;
		while (!input_file.eof())	//���� �� �������
		{
			std::string separate_str;
			getline(input_file, separate_str);
			lines.push_back(separate_str);
		}
		input_file.close();
		return parser(lines);	//��������� ������� �� ������ ��������� �������
	}

}

int fulltime(std::string time)
{
	std::vector<std::string> hh_mm = split(time, ":");
	return stoi(hh_mm[0]) * 60 + stoi(hh_mm[1]);
}

bool film_exist(const std::vector<Film>& seanses, const std::string& film_search, std::pair<std::string, Film>& info)
{
	for (int i = 0; i < seanses.size(); i++)
	{
		if (seanses[i].name == film_search)
		{
			info.second.name = seanses[i].name;
			info.second.data = seanses[i].data;
			info.second.subdata = seanses[i].subdata;
			return true;
		}
	}
	return false;
}

int get_filmIndex_time(const Film& film, const std::string& time)
{
	for (int i = 0; i < film.data.size(); i++)
	{
		if (film.data[i] == time)
			return i;
	}
	return -1;
}

void save_ticket(const Ticket& ticket, const std::string& path)
{
	std::ofstream fout(path, std::ios::app);
	if (!fout.is_open())
		return;

	fout << ticket.date << ';' << ticket.filmName << ';' << ticket.startTime << ';' << ticket.hallNumber << ';';
	for (int i = 0; i < ticket.raws.size(); i++)
	{
		fout << ticket.raws[i];
		if (i + 1 != ticket.raws.size())
			fout << ',';
		else
			fout << ';';
	}
	for (int i = 0; i < ticket.seats.size(); i++)
	{
		fout << ticket.seats[i];
		if (i + 1 != ticket.seats.size())
			fout << ',';
	}
	fout << '\n';
	fout.close();
}

bool find_time(const std::map<std::string, std::vector<Film>>& seanses, const std::string& time)
{
	for (auto i : seanses)
		if (i.first == time)
			return true;
	return false;
}

bool find_time(std::vector<std::string> times, std::string time)
{
	for (int i = 0; i < times.size(); i++)
	{
		if (times[i] == time)
			return true;
	}
	return false;
}

void reset(std::vector<std::vector<int>>& cinemahall)
{


	std::vector<int> tmp;
	for (int i = 1; i < 8; i++)
	{
		for (int j = 0; j < i * 4; j++)
		{
			tmp.push_back(0);
		}
		cinemahall.push_back(tmp);
		tmp.clear();
	}
}

void set_cinemahall(std::vector<std::vector<int>>& cinemahall, const std::pair<std::string, Film>& choose_film, const std::string& time_seanse, const std::string& path_tickets)
{
	std::ifstream fin(path_tickets);

	std::vector<Ticket> tickets;

	if (!fin.is_open())
		return;

	std::string line;



	std::vector<std::string> parse_line;

	while (getline(fin, line))
	{
		Ticket t;
		if (line == "")
			continue;

		parse_line = split(line, ";");

		t.date = parse_line[0];
		t.filmName = parse_line[1];
		t.startTime = parse_line[2];
		string_to_int(parse_line[3], t.hallNumber);
		int raw;
		for (auto i : split(parse_line[4], ","))
		{
			string_to_int(i, raw);
			t.raws.push_back(raw);
		}
		int seat;
		for (auto i : split(parse_line[5], ","))
		{
			string_to_int(i, seat);
			t.seats.push_back(seat);
		}
		tickets.push_back(t);
	}

	for (auto i : tickets)
	{
		if (i.date == choose_film.first && i.filmName == choose_film.second.name && i.startTime == time_seanse)
		{
			for (int j = 0; j < i.raws.size(); j++)
			{
				int raw = i.raws[j];
				int col = i.seats[j];
				cinemahall[i.raws[j]][i.seats[j]] = 1;
			}
		}
	}

	fin.close();
}


std::vector<std::pair<int, int>> many_people(std::vector<std::vector<int>> data, int count) {
	std::vector<std::pair<int, int>> cord(2);
	for (int row = 0; row < data.size(); ++row) {
		bool start = true;
		short start_cord = 0;
		int count_now = 0;
		for (int seat = 0; seat < data[row].size(); ++seat) {
			if (count_now == count) {
				cord[0].first = row;
				cord[0].second = start_cord;
				cord[1].first = row;
				cord[1].second = seat - 1;
				return cord;
			}
			if (data[row][seat] == 0) {
				++count_now;
				if (start) {
					start_cord = seat;
					start = false;
				}
			}
			else {
				count_now = 0;
				start = true;
			}
		}

	}
	return { {-1, -1}, {-1, -1} };
}

int get_coast(const std::pair<std::string, Film>&filmInfo, const std::string & time, const std::map<std::string, std::vector<Film>>&coasts)
{
	std::vector<std::pair<std::string, std::string>> coasts_film;
	std::string coast;
	for (auto i : coasts)
	{
		if (filmInfo.first != i.first)
			continue;
		for (auto j : i.second)
		{
			if (filmInfo.second.name == j.name )
			{
				for (int h = 0; h < j.data.size(); h++)
				{
					coasts_film.push_back(make_pair(j.data[h], j.subdata[h]));
				}
			}
		}
		for (int j = 0; j < filmInfo.second.data.size(); j++)
		{
			
			for (int h = 0; h < coasts_film.size(); h++)
			{
				if (fulltime(filmInfo.second.data[j]) > fulltime(coasts_film[h].first) && filmInfo.second.data[j] == time)
				{
					for (char c : coasts_film[h].second)
					{
						if ((int)c >= -1)
						{
							if (isdigit(c))
								coast += c;
						}
						else
							break;
					}
				}
			}
		}
	}
	if (coast == "")
		coast = "0";
	return stoi(coast);
}