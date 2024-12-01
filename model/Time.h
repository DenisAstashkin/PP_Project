#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;

int time_in_min(string time);
bool Check_time(string time);

int input_time() {
	string input_str;
	cin >> input_str;

	if (Check_time(input_str)) {
		return time_in_min(input_str);
	}
	else {
		return -1;
	}
}

bool is_only_number(string number)
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

	string hours_str = time.substr(0, index_sep);
	string minutes_str = time.substr(index_sep + 1);


	if (!(is_only_number(hours_str)) || !(is_only_number(minutes_str)) || hours_str.size() > 2 || minutes_str.size() > 2) {
		return false;
	}

	int hours_int = stoi(hours_str);
	int minutes_int = stoi(minutes_str);


	if (hours_int > 23 || minutes_int > 59 || hours_int < 0 || minutes_int < 0) {
		return false;
	}
	return true;
}

int time_in_min(string time) {
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
