#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

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
    string s1, s2;
    cin >> s1 >> s2;
    /*
    Loai bo cac so 0 du thua o cuoi
    Tinh ra vi tri dat dau .
    Dat dau cham vao la xong
    */
    while (s1[(int)s1.size() -1] == '0' && s2[(int) s2.size() -1] == '0') {
        s1 = s1.substr(0, (int) s1.size()-1);
        s2 = s2.substr(0, (int) s2.size()-1);
    }
    if (s2 == "1") {
        cout << s1;
        return 0;
    }
    if ((int) s1.size() < (int) s2.size()) {
        cout << "0.";
        for (int i=0;i<(int) s2.size() - (int) s1.size() -1;i++) {
            cout << "0";
        }
        cout << s1;
        return 0;
    }
    dbg(s1, s2);
    for (int i=0;i<=(int) s1.size() - (int) s2.size();i++) {
        cout << s1[i];
    }
    cout << '.';
    for (int i=(int) s1.size() - (int) s2.size()+1;i<(int) s1.size();i++) {
        cout << s1[i];
    }

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
*/