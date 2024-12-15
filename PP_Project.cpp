#include "lib/interface_design.h"
#include "lib/logic.h"
#include "lib/registration.h"
#include "model/Film.h"
#include "model/Date.h"
#include "model/Ticket.h"
#include "lib/Converter.h"

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

#ifndef __linux__
#include <Windows.h>	
#endif

using namespace std;

int main()
{
#ifndef __linux__
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif // !__linux__

	string path_seanses = "E:\\C++\\PP_Project\\Data\\Schedule.txt";
	string path_coasts = "E:\\C++\\PP_Project\\Data\\Coast.txt";
	string path_tickets = "E:\\C++\\PP_Project\\Data\\Tickets.txt";

	vector<vector<int>> cinemahall;

	reset(cinemahall);

	auto seanses = get_file_info(path_seanses); 	// Пример входных данных: 13.12.2024;Аватар;13:10-2,16:15-1
	auto coasts = get_file_info(path_coasts);		// Пример входных данных: 01.12.2024;Doctor Who;00:00-390rub,15:15-450rub,20:20-500rub
	
	string console_buffer;

	bool check;

	string lastDate;
	int back = 0;
	int choice;

	pair<string, Film> choose_film;

	vector<Film> choose_film_for_date;

	Ticket ticket;
	do
	{
		

		switch (back)
		{
			case 0:
			{
				system("cls");
				ticket.date = "";
				ticket.filmName = "";
				ticket.hallNumber = 0;
				ticket.startTime = "";
				ticket.seats.clear();
				ticket.raws.clear();

				for (auto i : seanses)
				{
					if (validate_date(i.first) && i.second.size() != 0 && now_and_(now_date_str(), stodate(i.first)))
					{
						cout << i.first << "\n";
						print_films(seanses, stodate(i.first));
						cout << "\n\n";
					}
				}
				cout << "\n0 - Выход\nВведите дату сеансов (дд.мм.гггг): ";

				do
				{
					getline(cin, console_buffer);
					if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
						exit(0);
					check = validate_date(console_buffer);
					if (!check)
						cout << "Неверный формат даты, повторите попытку (дд.мм.гггг): ";
					else if (!find_time(seanses, console_buffer))
						cout << "Сенса с данной датой нет: ";

				} while (!check || !find_time(seanses, console_buffer));
				ticket.date = console_buffer;
				choose_film.first = ticket.date;
				back++;
				break;
			}
			case 1:
			{
				

				system("cls");

				print_films(seanses, stodate(ticket.date));

				choose_film_for_date = seanses[ticket.date];

				do
				{
					cout << "\n0 - Назад\nВведите название фильма: ";
					getline(cin, console_buffer);
					if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
					{
						back--;
						break;
					}
				} while (!film_exist(choose_film_for_date, console_buffer, choose_film));
				choose_film_for_date.clear();
				if (back == 1)
				{
					back++;
					ticket.filmName = choose_film.second.name;
				}
				break;
				
			}
			case 2:
			{
				system("cls");

				print_film(choose_film.second, choose_film.first);

				
				print_coasts(choose_film, coasts, "Цена скоро появится");

				do
				{
					cout << "\n0 - Назад\nВведите время сеанса (чч:мм): ";
					getline(cin, console_buffer);

					if (console_buffer == "0")
					{
						back--;
						break;
					}
					else if (!validateTime(console_buffer))
						cout << "Введён неверный формат времени\n";
					else if (!find_time(choose_film.second.data, console_buffer))
						cout << "Такого времени нет в расписании\n";

				} while (!validateTime(console_buffer) || !find_time(choose_film.second.data, console_buffer));
				if (back != 2)
					break;
				ticket.startTime = console_buffer;
				string_to_int(choose_film.second.subdata[get_filmIndex_time(choose_film.second, ticket.startTime)], ticket.hallNumber);
				if (back == 2 && find_time(choose_film.second.data, console_buffer))
				{
					
					set_cinemahall(cinemahall, choose_film, ticket.startTime, path_tickets);
					bool start = true;
					do
					{
						system("cls");

						set_padding(strlen("Экран") - 4);
						cout << "Экран\n\n";
						print_cinemahall(cinemahall);
						int raw = -1;
						do
						{
							cout << "\n0 - Назад\nВведите ряд: ";
							getline(cin, console_buffer);
							if (console_buffer == "0")
							{
								start = false;
								break;
							}
						} while (!string_to_int(console_buffer, raw) || raw < 1 || raw > cinemahall.size());
												
						if (raw >= 1 && raw <= cinemahall.size())
							ticket.raws.push_back(raw - 1);
						else
							break;

						int seat = -1;
						do
						{
							cout << "\n0 - Назад\nВведите место: ";
							getline(cin, console_buffer);
							if (console_buffer == "0")
							{
								start = false;
								break;
							}
						} while (!string_to_int(console_buffer, seat) || seat < 1 || seat > cinemahall[raw - 1].size());

						if (seat >= 1 && seat <= cinemahall[raw - 1].size())
						{
							ticket.seats.push_back(seat - 1);
							if (cinemahall[raw - 1][seat - 1] == static_cast<int>(condition_place::empty))
							{
								cinemahall[raw - 1][seat - 1] = static_cast<int>(condition_place::your);
							}
							else
							{
								ticket.raws.pop_back();
								ticket.seats.pop_back();
								cout << "Данное место занято\n";
								getchar();
							}
						}
						else
							break;

						
					} while (start);
					cinemahall.clear();
					reset(cinemahall);

					if (console_buffer == "0" && ticket.raws.size() != 0 && ticket.seats.size() != 0)
					{
						save_ticket(ticket, path_tickets);
						print_ticket(ticket);
						getchar();
					}
						
					back++;
				}
				break;
			}
			default:
				back = 0;
				break;
		}
	} while (true);
	
	


	return 0;
}