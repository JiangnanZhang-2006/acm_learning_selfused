#include <bits/stdc++.h>

using namespace std;

struct VNode {
    int val;              // >0 当前值；0 表示转发到 to；-1 已废弃
    VNode *to;
    list<list<VNode *>::iterator> pos; // 指向 seq 里存放本 VNode* 的迭代器
};

static VNode *resolve(VNode *v) {
    while (v && v->val == 0) v = v->to;
    return v;
}

static int resolve_val(VNode *v) {
    v = resolve(v);
    return v ? v->val : -1;
}

static void solve() {
    int n, x, y, cmd;
    cin >> n;
    unordered_map<int, VNode *> rep;
    list<VNode *> seq;
    rep.reserve((size_t)n * 2 + 100000);

    auto ensure = [&](int v) -> VNode * {
        auto f = rep.find(v);
        if (f != rep.end()) return f->second;
        VNode *p = new VNode{v, nullptr, {}};
        rep[v] = p;
        return p;
    };

    for (int i = 0; i < n; i++) {
        cin >> x;
        VNode *vx = ensure(x);
        seq.push_back(vx);
        vx->pos.push_back(prev(seq.end()));
    }

    int m;
    cin >> m;
    while (m--) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> x >> y;
                if (x == y) break;
                if (!rep.count(x)) break;
                VNode *nx = rep[x];
                if (rep.count(y)) {
                    VNode *ny = rep[y];
                    nx->val = 0;
                    nx->to = ny;
                    ny->pos.splice(ny->pos.end(), nx->pos);
                    rep.erase(x);
                } else {
                    nx->val = y;
                    rep[y] = nx;
                    rep.erase(x);
                }
                break;
            }
            case 2: {
                cin >> x;
                VNode *vx = ensure(x);
                seq.push_back(vx);
                vx->pos.push_back(prev(seq.end()));
                break;
            }
            case 3: {
                cin >> x;
                if (!rep.count(x)) break;
                VNode *vx = rep[x];
                vector<list<VNode *>::iterator> cut(vx->pos.begin(), vx->pos.end());
                vx->pos.clear();
                for (auto lit : cut) seq.erase(lit);
                vx->val = -1;
                rep.erase(x);
                break;
            }
            default:
                break;
        }
    }

    bool first = true;
    for (VNode *p : seq) {
        int v = resolve_val(p);
        if (v <= 0) continue;
        if (first) {
            cout << v;
            first = false;
        } else {
            cout << ' ' << v;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
