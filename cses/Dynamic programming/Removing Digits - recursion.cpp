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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<int> ans(n+1, INF);
    ans[0] = 0;
    int call_times = 0;
    std::function<int(int)> cal = [&](int k){
        // Dùng recursion với memoization
        if (ans[k] != INF) return ans[k];
        string num = to_string(k);
        for (auto digit: num) {
            int prev = k - (digit - '0');
            if (prev < 0) continue;
            ans[k] = min(ans[k], cal(prev) + 1);
        }
        return ans[k];
    };
    cout << cal(n);
    show_exec_time();
}
/*
https://cses.fi/problemset/task/1637/
Removing Digits
Với mỗi số k ví dụ bằng 125.
thì k có 3 cách (số chữ số của k) để biến đổi
-> ans[k] = min(ans[k], ans[k-digit] + 1)
125 có thể chyển thành 124 (125-1), 123 (125-2), 120 (125-5)

Lưu ý: 
Dùng recursion với memoization về cơ bản là giống và giải quyết được các bài dp
nhưng
* Khó debug
* RE trên máy local (vẫn chạy trên online judge)
*/
