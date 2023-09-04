#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

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
    for (auto &v: a) {
        cin >> v;
    }
    unordered_map<int, vector<int>> m;
    for (int i=0;i<n;i++) {
        m[a[i]].push_back(i);
    }
    dbg(m);
    int ans = 0; 
    for (auto u: m) {
        auto v = u.second;
        if (v.size() < 2) continue;
        for (int i=0;i< (int) v.size() -1;i++) {
            ans += (v[i+1] - v[i] -1) * (i+1) * ((int) v.size() - i -1);
        }
    }
    cout << ans;
    
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

Xét từng số một ví dụ
1121331
tách số 1 ra được 11_1__1
Tại đây với mỗi khoảng 2 số 1 cạnh nhau thì có số lần xuất hiện 
bằng số index trái số 1 thứ 1 và index phải từ số 1 thứ 2
*/
