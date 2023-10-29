// http://www.usaco.org/index.php?page=viewproblem2&cpid=945
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
// #define int long long
const int INF = 2147483647 / 2; // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

template<typename T = int>
struct Compress {
    vector<T> rcv; // recover - giá trị mảng ban đầu đã sort và xóa unique
    vector<T> cpr; // compressed - giá trị đã nén của mảng a
    Compress() {}
    Compress(vector<T> a) { build(a);}
    void build(vector<T> a) {
        rcv = a;
        sort(rcv.begin(), rcv.end());
        rcv.resize(unique(rcv.begin(), rcv.end()) - rcv.begin());

        cpr.resize(a.size());
        for (int i = 0; i < (int) cpr.size(); ++i) 
            cpr[i] = lower_bound(rcv.begin(), rcv.end(), a[i]) - rcv.begin(); // O(logN) thay cho map
    }
    T compressed_val(T originalVal) { // giá trị ban đầu sang giá trị đã compress
        T i = lower_bound(rcv.begin(), rcv.end(), originalVal) - rcv.begin();
        if (rcv[i] != originalVal) return -1;
        return i;
    }
    T operator[] (int index) {
        return cpr[index];
    }
    T original_val(T compressedVal) {
        return rcv[compressedVal];
    }   
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        freopen("snakes.in", "r", stdin);
        freopen("snakes.out", "w", stdout);
    #endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    vector<int> netType = a;
    sort(netType.begin(), netType.end());
    Compress compress(netType);
    int maxSize = compress.rcv.size();
    // Dùng push DP
    // dp[index][change_remain][net_size]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k+1, vector<int>(maxSize+1, INF)));
    // Khởi tạo
    for (int net=0;net<maxSize;net++) {
        int net_size = compress.original_val(net);
        if (net_size >= a[0]) {
            dp[0][k][net] = net_size - a[0];
        }
    }
    // transition
    dbg(maxSize, n, k);
    for (int i=0;i<n-1;i++) {
        for (int change=0;change<=k;change++) {
            for (int net=0;net<maxSize;net++) {
                // Không thay đổi lưới
                int onet = compress.original_val(net);
                if (onet >= a[i+1]) {
                    dp[i+1][change][net] = min(dp[i+1][change][net], dp[i][change][net] + onet - a[i+1]);
                }
            }
            // Thay đổi lưới - net nào cũng có thể được - dựa vào min(dp[i][k][any_net])
            int bestAns = INF;
            for (int net=0;net<maxSize;net++) {
                bestAns = min(bestAns, dp[i][change][net]);
            }
            for (int net=0;net<maxSize;net++) {
                int onet = compress.original_val(net);
                if (change-1>=0 && onet>=a[i+1]) {
                    dp[i+1][change-1][net] = min(dp[i+1][change-1][net], bestAns + onet - a[i+1]);
                }
            }
        }
    }
    int ans = INF;
    for (int change=0;change<=k;change++) {
        for (int net=0;net<=maxSize;net++) {
            ans = min(ans, dp[n-1][change][net]);
        }
    }
    cout << ans;
    show_exec_time();
}