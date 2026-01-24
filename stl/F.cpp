#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <string>
#include <iomanip>
using namespace std;

struct StudentCmp {
    bool operator()(const tuple<string, int, int>& a, const tuple<string, int, int>& b) const {
        if (get<2>(a) != get<2>(b)) {
            return get<2>(a) > get<2>(b);
        }
        if (get<1>(a) != get<1>(b)) {
            return get<1>(a) < get<1>(b);
        }
        return get<0>(a) < get<0>(b);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();
    // {name, total_scores, solved_count}
    vector<tuple<string, int, int>> students;
    string line;
    while (getline(cin, line) && line != "") {
        string name;
        int total_scores = 0;
        int solved_count = 0;
        stringstream ss(line);
        ss >> name;
        string temp_score;
        for (int i = 0; i < n; ++i) {
            ss >> temp_score;

            int score = 0;
            if (temp_score[0] == '-' || temp_score == "0") {
                //haven't solved
                continue;
            }
            auto pos = temp_score.find('('); 
            solved_count++;
            if (pos != string::npos) {
                //has solved but had failed
                score = stoi(temp_score.substr(0, pos));
                auto pos2 = temp_score.find(')', pos);
                if (pos2 != string::npos) {
                    score += m * stoi(temp_score.substr(pos + 1, pos2 - pos - 1));
                }
            } else {
                score = stoi(temp_score);
            }
            total_scores += score;
        }

        students.push_back(make_tuple(name, total_scores, solved_count));
    }
    // solved_count > total_scores > name
    sort(students.begin(), students.end(), StudentCmp{});
    for (size_t i = 0; i < students.size(); ++i) {
        cout << setfill(' ') << setw(10) << left << get<0>(students[i]) 
             << ' ' << setw(2) << right << get<2>(students[i]) 
             << ' ' << setw(4) << right << get<1>(students[i]) << endl;
    }
    return 0;
}