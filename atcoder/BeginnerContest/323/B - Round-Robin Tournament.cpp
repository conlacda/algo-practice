// https://atcoder.jp/contests/abc323/tasks/abc323_b
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

struct Player {
    int index, point;
    bool friend operator<(Player a, Player b) {
        if (a.point == b.point) return a.index < b.index;
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
    int n;
    cin >> n;
    vector<Player> p;
    for (int i=0;i<n;i++) {
        string s;
        cin >> s;
        int cnt = 0;
        for (auto v: s) {
            if (v == 'o') cnt++;
        }
        p.push_back(Player{i+1, cnt});
    }
    sort(p.begin(), p.end());
    for (auto v: p ) cout << v.index <<" ";

    
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