#pragma once

#include <string>
#include <vector>

struct Ticket {
	std::string date;
	std::string filmName;
	std::string startTime;

	int hallNumber;

	std::vector<int> raws;
	std::vector<int> seats;
};