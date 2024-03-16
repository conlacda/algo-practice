// [Atcoder|Codeforces].abcxxx.F
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
#define show_exec_time()
#define destructure(a) #a
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    // swap 2 vị trí i, j bất kỳ -> có bao nhiêu string khác nhau được tạo ra
    int ans = 0;
    int n = s.size();
    map<char, int> counter;
    for (auto&v: s) counter[v]++;
    dbg(counter);
    bool e = false;
    string apb = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0;i<(int) apb.size()-1;i++) {
        for (int j=i+1;j<(int) apb.size();j++) {
            ans += counter[apb[i]] * counter[apb[j]];
        }
    }
    for (auto&v: apb) 
        if (counter[v] >= 2) e = true;
    cout << ans + e;

    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
