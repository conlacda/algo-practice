// https://atcoder.jp/contests/abc323/tasks/abc323_c
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Point {
    int index, point;
    friend bool operator<(Point a, Point b) {
        return a.point > b.point;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    vector<Point> point(m);
    for (int i=0;i<m;i++) {
        int x;
        cin >> x;
        point[i] = Point{i, x};
    }
    vector<int> users;
    vector<string> solved;
    for (int i=0;i<n;i++) {
        string s;
        cin >> s; solved.push_back(s);
        int cur = i+1;
        for (int j=0;j<(int) s.size();j++) {
            if (s[j] == 'o') {
                cur += point[j].point;
            }
        }
        users.push_back(cur);
    }
    int max_point = *max_element(users.begin(), users.end());
    sort(point.begin(), point.end());
    for (int i=0;i<n;i++) {
        int p = users[i];
        if (p >= max_point) {
            cout << 0 <<'\n';
            continue;
        }

        int cnt = 0;
        for (int j=0;j<m;j++) {
            if (solved[i][point[j].index] == 'o') continue;
            p += point[j].point;
            cnt++;
            if (p >= max_point) {
                cout << cnt <<'\n';
                break;
            }
        }
    }
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/