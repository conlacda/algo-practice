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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Với mỗi phần tử duyệt left -> độ dài left tối đa là bao nhiêu
    Tương tự duyệt right xem độ dài right tối đa là bao nhiêu
    -> độ dài của 1 phần tử đc xác định
    -> lấy max là xong
    */    
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v: a) cin >> v;
    vector<int> l(n, 1), r(n, 1);
    // tính left
    int cur = 1;
    for (int i=0;i<n;i++) {
        if (a[i] >= cur) {
            l[i] = cur;
        } else {
            cur = a[i];
            l[i] = cur;
        }
        cur ++;
    }
    // tính right
    cur = 1;
    for (int i=n-1;i>=0;i--) {
        if (a[i] >= cur) {
            r[i] = cur;
        } else {
            cur = a[i];
            r[i] = cur;
        }
        cur++;
    }
    dbg(l);
    dbg(r);
    int ans = 0;
    for (int i=0;i<n;i++) {
        ans = max(ans, min(l[i], r[i]));
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
