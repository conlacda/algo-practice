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
    Lấy 1 số x >= 2 rồi xóa nó đi -> viết ra 2 số 1 nửa lên bảng
    Cứ lặp đi lặp lại cho tới khi mọi số về 1
    Hỏi có bao nhiêu yên được trả ra
    */
    map<int, int> cache;
    std::function<int(int)> cal = [&](int u) {
        if (u < 2) return (int) 0;
        if (cache.find(u) != cache.end())
            return cache[u];
        if (u % 2 == 0) {
            int ans = u + 2 * cal(u / 2);
            cache[u] = ans;
            return ans;
        } 
        int ans = u + cal(u /2) + cal(u/2 +1);
        cache[u] = ans;
        return ans;
    };
    int n; cin >> n;
    cout << cal(n);
    show_exec_time();
}

