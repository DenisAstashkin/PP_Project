#pragma once

#include "../lib/logic.h"

#include <string>
#include <vector>
#include <ctime>
#pragma warning(disable : 4996)

struct Date
{
public:
	unsigned int day;
	unsigned int month;
	unsigned int year;

	std::string fulldate() const
	{
		return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
	}

};

bool validate_two_date(const Date& now, const Date& next)
{
	if (next.year * 365 + next.month * 31 + next.day - now.year * 365 - now.month * 31 - now.day <= 7)
		return true;
	return false;
}

bool now_and_(const Date& now, const Date& next)
{
	long long d = next.year * 365 + next.month * 31 + next.day;
	long long f = now.year * 365 + now.month * 31 + now.day;
	long long h =d - f;
	if (h < 0)
		return false;
	return true;
}

Date& stodate(std::string date)
{
	std::vector<std::string> dd_mm__hhhh = split(date, ".");
	Date _date;
	_date.day = stoi(dd_mm__hhhh[0]);
	_date.month = stoi(dd_mm__hhhh[1]);
	_date.year = stoi(dd_mm__hhhh[2]);
	return _date;
}


Date now_date_str()
{
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	Date now_date;

	now_date.day = now->tm_mday;
	now_date.month = now->tm_mon + 1;
	now_date.year = now->tm_year + 1900;

	now = nullptr;

	return now_date;
}