// https://codeforces.com/contest/1928/problem/B
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    dbg(a);
    /*
    Sort array
    Dựng với từng số 1.
    Số nhỏ nhất phải lấy cái số n.
    Trong khoảng từ số đó -> số đó + n có bao nhiêu số distinct?? thì là bằng đó số = nhau
    =>
    Nếu trong cùng 1 dãy có 2 số giống nhau thì 2 số đó ko thể tạo ra 2 số bằng nhau
    sau khi cộng với pi, pj -> loại bỏ toàn bộ các số trùng nhau
    Sắp xếp lại dãy.
    Xét số ai ta thấy số nhỏ nhất thì được cộng số n (lớn nhất của permutation) là tốt nhất
    khi này những số < a[i] + n sẽ có thể cộng với 1 số trong permutation để tạo ra
    a[i] + n
    Thế thì bản chất là với mỗi số ai thì ta đếm số lượng số trong khoảng ai ->ai+n-1
    rồi lấy max là xong
    */
    int ans = 0;
    for (int i=0;i<(int) a.size();i++) {
        int cnt = std::upper_bound(a.begin(), a.end(), a[i] + n-1) - a.begin();
        dbg(a[i] + n, cnt);
        ans = max(ans, cnt - i);
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    while (n--) solve();

    show_exec_time();
}
