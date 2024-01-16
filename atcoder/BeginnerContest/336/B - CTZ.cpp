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
    auto x = toBaseN(n, 2);
    dbg(x);
    int ans = 0;
    for (int i=(int) x.size()-1;i>=0;i--) {
        if (x[i] == 0) ans++;
        else break;
    }
    cout << ans;

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
