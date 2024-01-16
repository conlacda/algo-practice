// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

vector<ll> toBaseN(ll n, ll base, int fixed_len = -1){
    if (n == 0) return {0};
    vector<ll> ans;
    while (n > 0) {
        ans.push_back(n % base);
        n= n/base;  
    }
    while ((int) ans.size() < fixed_len) ans.push_back(0);
    reverse(ans.begin(), ans.end());
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    n--;
    // /*
    // Số thứ N trong hệ bậc 5 là bao nhiêu
    // */
    auto x =toBaseN(n, 5);
    dbg(x);
    map<int, int> m;
    m[0] = 0;
    m[1] = 2;
    m[2] = 4;
    m[3] = 6;
    m[4] = 8;
    for (auto v: x) {
        cout << m[v];
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
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
