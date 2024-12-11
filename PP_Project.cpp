#include "lib/interface_design.h"
#include "lib/logic.h"
#include "lib/registration.h"
#include <iostream>
#include <string>

using namespace std;




int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	registrate("loginsdada", "passwordsdadas", "base.txt");
	


	//auto seanses = get_file_info("путь до файла с сеансами"); 	// пример строки в файле 01.12.2024;Doctor Who;11:00,12:00,16:00
	//auto coasts = get_file_info("путь до файла с ценами");		// пример строки в файле 01.12.2024;Doctor Who;00:00-390rub,15:15-450rub,20:20-500rub

	//for (auto i : seanses)
	//{
	//	cout << i.first << '\n';
	//	cout << i.second.name << ": ";

	//	vector<pair<string, string>> coasts_film;

	//	for (auto j : coasts)
	//	{
	//		if (i.second.name == j.second.name)
	//		{
	//			for (int h = 0; h < j.second.times.size(); h++)
	//			{
	//				vector<string>time_coast = split(j.second.times[h], "-");
	//				coasts_film.push_back(make_pair(time_coast[0], time_coast[1]));
	//			}
	//			break;
	//		}
	//	}

	//	for (int j = 0; j < i.second.times.size(); j++)
	//	{
	//		string coast;
	//		for (int h = 0; h < coasts_film.size(); h++)
	//		{
	//			if (fulltime(i.second.times[j]) > fulltime(coasts_film[h].first))
	//			{
	//				coast = coasts_film[h].second;
	//			}
	//		}
	//		cout << i.second.times[j] << " - " << coast << '\n';
	//	}
	//	cout << "\n\n";
	//}

	//system("pause");
	return 0;
}