#include <fstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

static const long long LIMIT = 1000000000LL;

static void dfs(const string &cur, const vector<string> &pieces, set<int> &good) {
    if (!cur.empty()) {
        int v = stoi(cur);
        if (v <= LIMIT) good.insert(v);
    }
    if ((int)cur.size() >= 10) return;
    for (const string &p : pieces) {
        string nxt = cur + p;
        if (nxt.size() > 10) continue;
        if (stoll(nxt) > LIMIT) continue;
        dfs(nxt, pieces, good);
    }
}

int main() {
    vector<string> pieces;
    for (int i = 0;; i++) {
        long long x = 1LL << i;
        if (x > LIMIT) break;
        pieces.push_back(to_string(x));
    }

    set<int> good;
    dfs("", pieces, good);
    vector<int> a(good.begin(), good.end());

    ofstream out("data.txt", ios::out | ios::trunc);
    if (!out) return 1;
    for (size_t i = 0; i < a.size(); i++) {
        int d = (i == 0) ? a[0] : (a[i] - a[i - 1]);
        out << d << '\n';
    }
    out.close();
    return 0;
}
