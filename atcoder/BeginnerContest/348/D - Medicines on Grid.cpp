// https://atcoder.jp/contests/abc348/tasks/abc348_d
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int h,w;
    cin >> h >> w;
    vector<string> grid(h);
    for (auto&v: grid) cin >> v;
    dbg(grid);
    int n;
    vector<vector<int>> dp(h, vector<int>(w, 0));
    cin >> n;
    for (int i=0;i<n;i++) {
        int r, c, v;
        cin >> r >> c >> v;
        dp[--r][--c] = v;
    }
    // Dùng bfs() để lan từ S sang tới T
    // get S
    pair<int,int> start;
    for (int i=0;i<h;i++) {
        for (int j=0;j<w;j++) {
            if (grid[i][j] == 'S') start = {i, j};
        }
    }
    pair<int,int> end;
    for (int i=0;i<h;i++) {
        for (int j=0;j<w;j++) {
            if (grid[i][j] == 'T') end = {i, j};
        }
    }
    // bfs()
    vector<vector<bool>> ok(h, vector<bool>(w, false));
    queue<pair<int,int>> Q;
    Q.push(start);
    ok[start.first][start.second] = true;

    vector<pair<int,int>> coor{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        if (dp[cur.first][cur.second] == 0) continue;
        // đi tới các ô tiếp theo
        // trái phải trên dưới
        for (auto c: coor) {
            if (!(cur.first + c.first >= 0 && cur.first + c.first < h && cur.second + c.second >= 0 && cur.second + c.second <w)) continue;
            if (grid[cur.first + c.first][cur.second + c.second] == '#') continue;
            // lớn hơn thì hãy tới hoặc chưa tới bao giờ thì hãy tới
            // >= sẽ gây ra việc đi qua lại 2 node bằng nhau nhiều lần
            if (dp[cur.first][cur.second]-1 > dp[cur.first + c.first][cur.second + c.second]
                || !ok[cur.first + c.first][cur.second + c.second]) {
                dp[cur.first + c.first][cur.second + c.second] = max(dp[cur.first + c.first][cur.second + c.second], dp[cur.first][cur.second]-1);
                ok[cur.first + c.first][cur.second + c.second] = true;
                Q.push({cur.first + c.first, cur.second + c.second});
            }
        }
        dbg(cur, Q);
    }
    if (ok[end.first][end.second]) cout << "Yes";
    else cout << "No";
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
