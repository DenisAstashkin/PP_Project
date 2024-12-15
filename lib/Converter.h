#pragma once
#include <string>

inline bool string_to_double(const std::string& _s_num, double& _num)
{
	if (_s_num.empty())
		return false;

	if (_s_num.find_first_not_of("0123456789.-") != std::string::npos || _s_num.find(".") != _s_num.rfind(".") || _s_num.size() == 0)
		return false;

	try
	{
		_num = stod(_s_num);
	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}

inline bool string_to_float(const std::string& _s_num, float& _num)
{
	if (_s_num.empty())
		return false;

	if (_s_num.find_first_not_of("0123456789.-") != std::string::npos || _s_num.find(".") != _s_num.rfind(".") || _s_num.size() == 0)
		return false;

	try
	{
		_num = stof(_s_num);
	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}

inline bool string_to_int(const std::string& _s_num, int& _num)
{
	if (_s_num.empty())
		return false;

	if (_s_num.find_first_not_of("0123456789-") != std::string::npos || _s_num.size() == 0)
		return false;

	try
	{
		_num = stoi(_s_num);
	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}