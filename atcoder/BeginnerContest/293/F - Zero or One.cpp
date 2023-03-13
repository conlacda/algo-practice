// https://atcoder.jp/contests/abc293/tasks/abc293_f
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif

// Base 10 to base N
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
// base N to base 10
ll toDecimal(vector<ll> s, ll base) {
    __int128 ans = 0;
    __int128 power = 1;    
    for (int i=(int)s.size()-1;i>=0;i--) {
        if (ans > LLONG_MAX || power > LLONG_MAX) return LLONG_MAX;
        ans += s[i] * power;
        power *= base;
    }
    return ans;
}

void solve() {
    ll n; cin >> n;
    // Bruteforce cho 1000 số đầu tiên
    ll res = 0;
    for (ll i=2;i<=min(1000 * 1LL, n);i++) {
        vector<ll> baseN = toBaseN(n, i);
        bool isGood = true;
        for (auto v: baseN) {
            if (v != 0 && v != 1) {
                isGood = false;
                break;
            }
        }
        if (isGood) res++;
    }    
    if (n <= 1000) {
        cout << res <<'\n';
        return;
    }
    // Từ số thứ 1000 trở đi do 1000^7 = 10^21 > LLONG_MAX nên mọi số đều chỉ có 7 số là tối đa tại hệ k
    // Cho số n và số n sau khi đã chuyển đổi theo hệ k. Tìm k?
    // Dùng binary search cho k
    for (ll i=0;i<1<<8;i++) {
        vector<ll> base2 = toBaseN(i, 2);
        ll left = 1001, right = n; // left = 1001 vì ở trên đã tính 1000 số đầu rồi
        while (left != right) {
            ll mid = (left + right) /2;
            if (toDecimal(base2, mid) >= n) right = mid;
            else left = mid+1;
        }
        if (toDecimal(base2, left) == n) res++;
    }
    cout << res << '\n';
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();   
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Phần này phải rất cẩn thận đoạn tràn số do đổi sang base 10
*/
