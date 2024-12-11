#pragma once

#include "../model/condition_place.h"
#include "../model/texture_for_seats.h"

#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
	#include <Windows.h>

	// Function for setting padding for centering
	void set_padding(const int& size_text)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);

		int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

		int padding = (console_width + size_text) / 2;

		std::cout.width(padding);
	}

#elif __linux__
	#include <sys/ioctl.h>
	#include <unistd.h>

	// Function for setting padding for centering
	void set_padding(const int& size_text)
	{
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		int padding = (w.ws_col + size_text) / 2;

		std::cout.width(padding);
	}	

#endif

// Function for displaying seats in the cinema hall
void print_cinemahall(const std::vector<std::vector<int>>& hall)
{
	for (int i = 0; i < hall.size(); i++)
	{
		set_padding(hall[i].size() * 2);

		for (int j = 0; j < hall[i].size(); j++)
		{
			switch (hall[i][j])
			{
			case static_cast<int>(condition_place::empty):
			std::cout << "\033[93m" << static_cast<char>(texture_for_seats::empty) << "\033[39m" << ' ';
				break;

			case static_cast<int>(condition_place::seat):
				std::cout << "\033[91m" << static_cast<char>(texture_for_seats::seat) << "\033[39m" << ' ';
				break;

			case static_cast<int>(condition_place::yours):
				std::cout << "\033[92m" << static_cast<char>(texture_for_seats::yours) << "\033[39m" << ' ';
				break;
			}
		}
		std::cout << '\n';
	}
}

void center_print(const std::string& text)
{
	set_padding(text.length());
	std::cout << text << '\n';
}

void print_previw()
{
		std::string cinemaName = "Luxury Cinema";
		std::cout << "\033[2J\033[1;1H"; // ������� ������

		std::cout << "\033[1;31m"; // ������� ����

		std::cout << "_____________________________________________@@___________________________________________________________________________________________________________________________________________________________________________________\n";
		std::cout << "_____@@@@_________________________________@@@@@@______LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU_XXXXXXXX_____________XXXXXXXX_______________AAAAAAAAAAAA_______________RRRRRRRRRRRRRRRRRRRRRRR_YYYYYYY___________YYYYYYY______\n";
		std::cout << "_____@@@@@@@_____________*_______________@@@@@@@______LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU__XXXXXXXX___________XXXXXXXX_______________AAAAAAAAAAAAAA______________RRRRRRRRRRRRRRRRRRRRRRR__YYYYYYY_________YYYYYYY_______\n";
		std::cout << "______@@@@@@@@__________________________@@@@@@@@@@____LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU___XXXXXXXX_________XXXXXXXX_______________AAAAAAAAAAAAAAAA_____________RRRRRRR_________RRRRRRR___YYYYYYY_______YYYYYYY________\n";
		std::cout << "______@@@@@@@@@@_______________________@@@@@@@@@@@____LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU____XXXXXXXX_______XXXXXXXX_______________AAAAAAAAAAAAAAAAAA____________RRRRRRR_________RRRRRRR____YYYYYYY_____YYYYYYY_________\n";
		std::cout << "_______@@@@@@@@@@@@____________________@@@@@@@@@@@@___LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU_____XXXXXXXX_____XXXXXXXX_______________AAAAAAAA____AAAAAAAA___________RRRRRRR_________RRRRRRR_____YYYYYYY___YYYYYYY__________\n";
		std::cout << "_______@@@@@@@@@@@@@__________________@@@@@@@@@@@@@___LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU______XXXXXXXX___XXXXXXXX_______________AAAAAAAA______AAAAAAAA__________RRRRRRRRRRRRRRRRRRRRRRR______YYYYYYY_YYYYYYY___________\n";
		std::cout << "________@@@@@@@@@@@@@@________________@@@@@@@@@@@@@___LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU_______XXXXXXXX_XXXXXXXXX______________AAAAAAAA________AAAAAAAA_________RRRRRRRRRRRRRRRRRRRRRRR_______YYYYYYYYYYYYY____________\n";
		std::cout << "_________@@@@@@@@@@@@@@@@_____*_______@@@@@@@@@@@@@___LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU________XXXXXXXXXXXXXXXX______________AAAAAAAAAAAAAAAAAAAAAAAAAA________RRRRRRRRRRRRRRRR_______________YYYYYYYYYYY_____________\n";
		std::cout << "__________@@@@@@@@@@@@@@@@@__________@@@@@@@@@@@@@____LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU_______XXXXXXXX_XXXXXXXXX____________AAAAAAAAAAAAAAAAAAAAAAAAAAAA_______RRRRRRRRRRRRRRRRRR______________YYYYYYYYY______________\n";
		std::cout << "___________@@@@@@@@@@@@@@@@@________@@@@@@@@@@@@@@____LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU______XXXXXXXX___XXXXXXXXX__________AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA______RRRRRRRRRRRRRRRRRRR______________YYYYYYY_______________\n";
		std::cout << "______*______@@@@@@@@@@@@@@@@_______@@@@@@@@@@@@@@@___LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU_____XXXXXXXX_____XXXXXXXX_________AAAAAAAA________________AAAAAAAA_____RRRRRRR______RRRRRRRR____________YYYYYYY_______________\n";
		std::cout << "______________@@@@@@@@@@@@@@@@_____@@@@@@@@@@@@@@@____LLLLLLLLLL__________UUUUUUUU_________UUUUUUUU____XXXXXXXX_______XXXXXXXX_______AAAAAAAA__________________AAAAAAAA____RRRRRRR________RRRRRRRR__________YYYYYYY_______________\n";
		std::cout << "________________@@@@@@@@@@@@@@_____@@@@@@@@@@@@@@_____LLLLLLLLLLLLLLLLLLL_UUUUUUUUUUUUUUUUUUUUUUUUU___XXXXXXXX_________XXXXXXXX_____AAAAAAAA____________________AAAAAAAA___RRRRRRR__________RRRRRRRR________YYYYYYY_______________\n";
		std::cout << "__________________@@@@@@@@@@@@@@___@@@@@@@@@@@@@______LLLLLLLLLLLLLLLLLLL_UUUUUUUUUUUUUUUUUUUUUUUUU__XXXXXXXX___________XXXXXXXX___AAAAAAAA______________________AAAAAAAA__RRRRRRR____________RRRRRRRR______YYYYYYY_______________\n";
		std::cout << "______________________@@@@@@@@@@@@_@@@@@@@@@@@@_______LLLLLLLLLLLLLLLLLLL_UUUUUUUUUUUUUUUUUUUUUUUUU_XXXXXXXX_____________XXXXXXXX_AAAAAAAA________________________AAAAAAAA_RRRRRRR_____________RRRRRRRR_____YYYYYYY_______________\n";
		std::cout << "____________*____________@@@@@@@@@@@@@@@@@@@@_________LLLLLLLLLLLLLLLLLLL__UUUUUUUUUUUUUUUUUUUUUUU__XXXXXXXX_____________XXXXXXXX_AAAAAAAA________________________AAAAAAAA_RRRRRRR_______________RRRRRRRR___YYYYYYY_______________\n";
		std::cout << "________________________@@@@@@@@@@@@@@@@@@@@_____*________________________________________________________________________________________________________________________________________________________________________________\n";
		std::cout << "____________________@@@@@@@@@@@@@@@@@@@@@@@@______________________________________________________________________________________________________________________________________________________________________________________\n";
		std::cout << "_________________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___________________________________________________________________________________________________________________________________________________________________________________\n";
		std::cout << "____*__________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@_____CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNNNNN_______________NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMMMMMM________________MMMMMMMMMMMM________________AAAAAAAAAA_____________________\n";
		std::cout << "______________@@@@@@@@@@@_$__@@@@@@@@@@@@@@@@@@@@@____CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNNNNNN______________NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMMMMMMM______________MMMMMMMMMMMMM_______________AAAAAAAAAAAA____________________\n";
		std::cout << "____________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@__CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNNNNNNN_____________NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMMMMMMMM____________MMMMMMMMMMMMMM______________AAAAAAAAAAAAAA___________________\n";
		std::cout << "____________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@__CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNNNNNNNN____________NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMMMMMMMMM__________MMMMMMMMMMMMMMM_____________AAAAAAAAAAAAAAAA__________________\n";
		std::cout << "____________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@__CCCCCCCCC______________________NNNNNNNNNNNNNN___________NNNNNNN_EEEEEEEE_____________MMMMMMMMMMMMMMMM________MMMMMMMMMMMMMMMM____________AAAAAAAAAAAAAAAAAA_________________\n";
		std::cout << "____________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@__CCCCCCCCC______________________NNNNNNN___NNNNN__________NNNNNNN_EEEEEEEE_____________MMMMMMMM____MMMMM______MMMMM____MMMMMMMM___________AAAAAAAA____AAAAAAAA________________\n";
		std::cout << "____________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@__CCCCCCCCC___________IIIIIIIIII_NNNNNNN____NNNNN_________NNNNNNN_EEEEEEEE_____________MMMMMMMM_____MMMMM____MMMMM_____MMMMMMMM__________AAAAAAAA______AAAAAAAA_______________\n";
		std::cout << "____*_________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@__CCCCCCCCC___________IIIIIIIIII_NNNNNNN_____NNNNN________NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM______MMMMM__MMMMM______MMMMMMMM_________AAAAAAAA________AAAAAAAA______________\n";
		std::cout << "________________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___CCCCCCCCC___________IIIIIIIIII_NNNNNNN______NNNNN_______NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM_______MMMMMMMMMM_______MMMMMMMM________AAAAAAAAAAAAAAAAAAAAAAAAAA_____________\n";
		std::cout << "__________________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@____CCCCCCCCC___________IIIIIIIIII_NNNNNNN_______NNNNN______NNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM________MMMMMMMM________MMMMMMMM_______AAAAAAAAAAAAAAAAAAAAAAAAAAAA____________\n";
		std::cout << "______________________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@CCCCCCCCC___________IIIIIIIIII_NNNNNNN________NNNNN_____NNNNNNN_EEEEEEEE_____________MMMMMMMM________________________MMMMMMMM______AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA___________\n";
		std::cout << "_____________________@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@_CCCCCCCCC___________IIIIIIIIII_NNNNNNN__________NNNN____NNNNNNN_EEEEEEEE_____________MMMMMMMM________________________MMMMMMMM_____AAAAAAAA________________AAAAAAAA__________\n";
		std::cout << "____________*________@@@@@@@@@@@@__@@@@@@@@@@_________CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNN___________NNNN___NNNNNNN_EEEEEEEE_____________MMMMMMMM________________________MMMMMMMM____AAAAAAAA__________________AAAAAAAA_________\n";
		std::cout << "_________________@@@@@_" << cinemaName << "_@@@@@@@__________CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNN____________NNNNNNNNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM________________________MMMMMMMM___AAAAAAAA____________________AAAAAAAA________\n";
		std::cout << "__________________@@@@@@@@@@@@_@@@@@@@@@@@@@@@@_______CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNN_____________NNNNNNNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM________________________MMMMMMMM__AAAAAAAA______________________AAAAAAAA_______\n";
		std::cout << "____*_____________@@@@@@@@@@@@_@@@@___________________CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNN______________NNNNNNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM________________________MMMMMMMM_AAAAAAAA________________________AAAAAAAA______\n";
		std::cout << "__________________@@@@____@@@@@@______________________CCCCCCCCCCCCCCCCCCC_IIIIIIIIII_NNNNNNN_______________NNNNNNNNNN_EEEEEEEEEEEEEEEEEEEE_MMMMMMMM________________________MMMMMMMM_AAAAAAAA________________________AAAAAAAA______\n";
		std::cout << "__________________________@@______________________________________________________________________________________________________________________________________________________________________________________________________\n";

		std::cout << "\033[0m";   // Сброс цвета
		std::string address = "ул. Крутых Пмишников, 1";
		std::string phoneNumber = "+7 (123) 456-78-90";
		std::string website = "www.luxurycinema.com";
		std::cout << address << '\n';
		std::cout << phoneNumber << '\n';
		std::cout << website << '\n';

		std::cout << "Приятного просмотра!\n";
}