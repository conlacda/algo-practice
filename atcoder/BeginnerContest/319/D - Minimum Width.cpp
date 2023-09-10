// https://atcoder.jp/contests/abc319/tasks/abc319_d
/*
Bài này chỉ đơn giản là dùng binary search để
tìm xem độ dài nào là phù hợp
Độ dài min là 0 (hoặc 1), max là ghép toàn bộ line vào 1 line
Giống 1 bài ở codeforces đã từng làm trước đây
*/
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    /*
    Tìm độ dài ngắn nhất của dòng
    -> binary search
    */
    std::function<int(int)> isGood = [&](int len){
        int line = 1;
        int cur_len = len;
        for (auto v: a) {
            if (len < v) return false;
            if (cur_len < v) {
                cur_len = len;
                line++;
                if (line > m) return false;
            }
            cur_len -= (v+1);
        }
        return true;
    };
    int left = 0, right = 0;
    for (auto v: a) right += v + 1;
    right -= 1;
    while (left < right) {
        int mid = (left + right) /2;
        if (isGood(mid)) {
            dbg(mid);
            right = mid;
        } else left = mid + 1;
    }
    cout << left;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
*/
