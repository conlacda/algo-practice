// https://cses.fi/problemset/result/7186019/
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    /*
    cho từng số chạy từ 1->maxN
    Đánh dấu xem số nào được chia hết bởi 2 số khác
    In số đó ra
    */
    unordered_map<int, int> cnt;
    for (auto v: a) {
        cnt[v]++;
    }
    // dbg(cnt);
    int maxN = *max_element(a.begin(), a.end());
    vector<int> div(maxN + 1, 0);
    for (int i=1;i<=maxN;i++) {
        for (int j=1;j<= maxN/i;j++) {
            if (cnt.find(i * j) != cnt.end()) {
                div[i] += cnt[i*j];
                if (div[i] >= 2) break;
            }
        }
    }
    // dbg(div);
    for (int i=(int) div.size() -1;i>=0;i--) {
        if (div[i] >= 2) {
            cout << i << " ";
            break;
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
