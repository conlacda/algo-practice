// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

struct X {
    int start, end, len;
};

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    từ 1 điểm i bất kỳ
    mở rộng điểm đó qua 2 phía khác nhau với cùng 1 character
    khi đó ta có những cụm đường đi đối xứng.
    */
    int n;
    cin >> n;
    vector<string> grid(n);
    for (auto&v: grid) cin >> v;
    dbg(grid);
    vector<vector<int>> res(n, vector<int>(n, INF));
    for (int i=0;i<n;i++) {
        res[i][i] = 0;
    }

    std::function<void(int)> cal = [&](int u) {
        map<char, vector<int>> in, out;
        for (int i=0;i<n;i++) {
            if (grid[i][u] != '-') {
                in[grid[i][u]].push_back(i);
            }
            if (grid[u][i] != '-') {
                out[grid[u][i]].push_back(i);
            }
        }
        queue<X> Q;
        for (char c = 'a';c<='z';c++) {
            for (auto&v: in[c]) {
                for (auto&u: out[c]) {
                    if (res[v][u] > 2) {
                        Q.push({v, u, 2});
                        res[v][u] = 2;
                    }
                }
            }
        }
        for (int i=0;i<n;i++) {
            if (grid[i][u] != '-' and i != u) {
                Q.push({i, u, 1});
                res[i][u] = 1;
            }
            if (grid[u][i] != '-' and i != u) {
                Q.push({u, i, 1});
                res[u][i] = 1;
            }
        }
        while (!Q.empty()) {
            // tiếp tục mở rộng
            auto [start, end, len] = Q.front();
            Q.pop();
            map<int, vector<int>> in, out;
            for (int i=0;i<n;i++) {
                if (grid[i][start] != '-') {
                    in[grid[i][start]].push_back(i);
                }
                if (grid[end][i] != '-') {
                    out[grid[end][i]].push_back(i);
                }
            }
            for (char c = 'a';c<='z';c++) {
                for (auto&v: in[c]) {
                    for (auto&u: out[c]) {
                        if (res[v][u] > len + 2) {
                            res[v][u] = len + 2;
                            Q.push({v, u, len + 2});
                        }
                    }
                }
            }
        }
    };
    for (int i=0;i<n;i++) {
        cal(i);
    }
    for (auto&v: res) {
        for (auto&u: v) {
            if (u == INF) u = -1;
            cout << u << ' ';
        }
        cout << "\n";
    }


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
