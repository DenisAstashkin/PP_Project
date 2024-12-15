#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> many_people(vector<vector<short>> data, int count) {
    vector<pair<int, int>> cord(2);
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
