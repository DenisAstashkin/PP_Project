#include "lib/interface_design.h"
#include "lib/logic.h"
#include "lib/registration.h"
#include "model/Film.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

int main()
{
#ifdef _WIN32
#include <Windows.h>
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif // WIN32

	//registrate("loginsdada ", "passwordsdadas", "base.txt");
center_print("1. Вход");
	center_print("2. Регистрация");
	map<string, Film> seanses = get_file_info("/home/shadow_usr/C++/PP_Project/Data/Seanses.txt"); 	// пример строки в файле 01.12.2024;Doctor Who;11:00,12:00,16:00
	map<string, Film> coasts = get_file_info("/home/shadow_usr/C++/PP_Project/Data/Coasts.txt");		// пример строки в файле 01.12.2024;Doctor Who;00:00-390rub,15:15-450rub,20:20-500rub

	int choice = 1;

	

	cin >> choice;

	switch (choice)
	{
	case 1:

		break;
	case 2:

		break;
	default:
		break;
	}

	// for (auto i : seanses)
	// {
	// 	cout << i.first << '\n';
	// 	cout << i.second.name << ":\n";

	// 	vector<pair<string, string>> coasts_film;

	// 	for (auto j : coasts)
	// 	{
	// 		if (i.second.name == j.second.name)
	// 		{
	// 			for (int h = 0; h < j.second.data.size(); h++)
	// 			{
	// 				vector<string>time_coast = split(j.second.data[h], "-");
	// 				coasts_film.push_back(make_pair(time_coast[0], time_coast[1]));
	// 			}
	// 			break;
	// 		}
	// 	}

	// 	for (int j = 0; j < i.second.data.size(); j++)
	// 	{
	// 		string coast;
	// 		for (int h = 0; h < coasts_film.size(); h++)
	// 		{
	// 			if (fulltime(i.second.data[j]) > fulltime(coasts_film[h].first))
	// 			{
	// 				coast = coasts_film[h].second;
	// 			}
	// 		}
	// 		cout << i.second.data[j] << " - " << coast << '\n';
	// 	}
	// 	cout << "\n\n";
	// }

	getchar();

	return 0;
}