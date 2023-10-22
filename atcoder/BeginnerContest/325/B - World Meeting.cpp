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

struct X {
    int w, x;
    friend bool operator<(X a, X b) {
        return a.x < b.x;
    }
    friend std::ostream& operator<<(std::ostream& os, const X s) { return os << destructure(s);}
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    vector<X> a(n);
    for (int i=0;i<n;i++) {
        cin >> a[i].w >> a[i].x;
    }
    sort(a.begin(), a.end());
    dbg(a);
    std::function<bool(int, int, int)> inRange = [&](int start, int end, int hour){
        if (start <= end) return start <= hour && hour <= end;
        if (start <= hour && hour < 24) return true;
        if (0 <= hour && hour <= end) return true;
        return false;
    };
    std::function<int(int)> cal = [&](int start){
        int ans = 0;
        int end = (start + 8) % 24; 
        for (auto v: a) {
            if (inRange(start, end, v.x)) ans += v.w;
        }
        return ans;
    };
    /*
    Trong vòng 9->17 giờ thì phải tổ chức được số nhiều nhất
    */
    int ans = 0;
    for (int i=0;i<24;i++) {
        ans = max(ans, cal(i));
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
RE:
    binary search - INF ??
*/