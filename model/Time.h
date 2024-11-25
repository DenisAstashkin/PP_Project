#pragma once
#include <iostream>
#include <sstream>
#include <string>

struct Time
{
	int hour = -1, min = -1;
};

using std::string;

bool is_only_number(string number) //в строке только числа?
{
	for (int i = 0; i < number.length(); i++) {
		int char_in_ascii = number[i];
		if (char_in_ascii < 48 || char_in_ascii > 57) {
			return false;
		}
	}
	return true;
}

bool Check_time(string time)
{
	int index_sep = time.find(':');
	if (index_sep <= 0) { return false; }

	string hours_str = time.substr(0, index_sep); //взятие символов, отвечающих за часы
	string minutes_str = time.substr(index_sep + 1); //взятие символов, отвечающих за минуты

	if (!(is_only_number(hours_str)) || !(is_only_number(minutes_str)) || hours_str.size() > 2 || minutes_str.size() > 2) {
		return false;
	}

	int hours_int = stoi(hours_str); //перевод строки, содержащую символы часов, в int
	int minutes_int = stoi(minutes_str); //перевод строки, содержащую символы минут, в int

	if (hours_int > 23 || minutes_int > 59 || hours_int < 0 || minutes_int < 0) {
		return false;
	}
	return true;
}

Time Normal_view_time_struct(string time) {// время в стракте (в интах) с проверкой 
	if (Check_time(time)) {
		int index_sep = time.find(':');

		string hours_str = time.substr(0, index_sep);
		string minutes_str = time.substr(index_sep + 1);

		Time return_time;
		return_time.hour = stoi(hours_str);
		return_time.min = stoi(minutes_str);

		return return_time;
	}
}

int Normal_view_time_min(string time) {//время в минутах с проверкой
	if (Check_time(time)) {
		int index_sep = time.find(':');

		string hours_str = time.substr(0, index_sep);
		string minutes_str = time.substr(index_sep + 1);

		int return_time(0);
		return_time += stoi(hours_str) * 60;
		return_time += stoi(minutes_str);

		return return_time;
	}
	else {
		return -1;
	}
}