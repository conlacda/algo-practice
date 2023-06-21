// https://codeforces.com/problemset/problem/1775/C
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
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

vector<ll> toBaseN(ll n, ll base, int fixed_len = -1){
    vector<ll> ans;
    while (n > 0) {
        ans.push_back(n % base);
        n= n/base;  
    }
    if (fixed_len != -1)
        while ((int) ans.size() < fixed_len) ans.push_back(0);
    reverse(ans.begin(), ans.end());
    return ans;
}
ll toDecimal(vector<ll> s, ll base) {
    __int128 ans = 0;
    __int128 power = 1;    
    for (int i=(int)s.size()-1;i>=0;i--) {
        if (ans > LLONG_MAX || power > LLONG_MAX) return LLONG_MAX; // tràn ll gây ra lỗi
        ans += s[i] * power;
        power *= base;
    }
    return ans;
}

void solve() {
    int n, x;
    cin >> n >> x;
    if (n < x) {
        cout << -1<<'\n';
        return;
    }
    if (n == x) {
        cout << n << '\n';
        return;
    }
    // Tim phan dau chung dai nhat
    // Tu phan do tro di thi moi so cua x phai bang 0??
    // Số đầu tiên phải là từ 1 về 0
    // 20 = 10100
    // 16 = 10000 -> số trước số 1 đó phải là số 0.
    // common01....
    // Binary search tìm ra số cần tìm
    /*
    Tính được and(m, k) - bằng phần chung của m,k và theo sau đó là các số 0
    */
    std::function<int(int, int)> And = [&](int f, int t){
        vector<int> fb = toBaseN(f, 2, 61);
        vector<int> tb = toBaseN(t, 2, 61);
        int i =0;
        vector<int> ans = {};
        for (;i<61;i++) {
            if (fb[i] != tb[i]) {
                while (i < (int) fb.size()) {
                    ans.push_back(0);
                    i++;
                }
            } else {
                ans.push_back(fb[i]);
            }
        }
        return toDecimal(ans, 2);
    };
    int l = n, r = 5 *(int) 1e18;
    while (l < r) {
        int mid = (l + r) /2;
        if (And(n, mid) <= x) {
            r = mid;
        } else {
            l = mid+1;
        }
    }
    if (And(n, r) == x) {
        cout << r << '\n';
    } else {
        cout << -1<<'\n';
    }
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    show_exec_time();
}
