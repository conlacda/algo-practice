// https://codeforces.com/contest/1883/problem/D
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

struct Query {
    int t, l, r;
    friend std::ostream& operator<<(std::ostream& os, const Query s) { return os << destructure(s);}
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
    vector<Query> a(n);
    for (int i=0;i<n;i++) {
        char t; int l, r;
        cin >> t; cin >> l >> r;
        if (t == '+') a[i] = Query{1, l, r};
        else a[i] = Query{0, l, r};
    }
    dbg(a);

    multiset<int> left, right;
    int cnt = 0;
    for (auto q: a) {
        if (q.t == 1) {
            cnt++;
            left.insert(q.l);
            right.insert(q.r);
        } else {
            cnt--;
            left.erase(left.lower_bound(q.l));
            right.erase(right.lower_bound(q.r));
        }
        if (cnt <= 1) {
            cout << "No\n";
            continue;
        }
        if (*prev(left.end()) > *right.begin()) {
            cout << "Yes\n";
        } else cout << "No\n";
        dbg(left, right);
    }
    /*
    Segment tree update giá trị mỗi lần cộng vào
    query toàn bộ dãy, nếu giá trị nhỏ nhất dãy là 1 thì Yes,
    ngược lại là No
    nếu số segment = 1 ->No
    segment từ 2 trở lên mới xét query

    2 cặp ko intersect thì max_left > min_right
    */
    
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