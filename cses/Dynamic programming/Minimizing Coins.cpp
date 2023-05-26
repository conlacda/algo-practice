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
    cout << std::fixed << setprecision(15);
    int n, sum;
    cin >> n >> sum;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    // Dùng pull DP, đồng sau bằng đồng trước cộng 1 đồng trong đống
    vector<int> cnt(sum+1, INF);
    for (auto coin: a) if (coin <= sum) cnt[coin] = 1; // khởi tạo initial base
    for (int i=1;i<=sum;i++) { // tính cho giá trị i
        for (auto coin: a) { // giá trị i = min([i], [i-coin] + 1)
            if (i-coin >=0 && cnt[i-coin] != INF) 
                cnt[i] = min(cnt[i], cnt[i-coin] + 1); // hàm quan trọng nhất
        }
    }
    cout << ((cnt[sum] != INF) ? cnt[sum] : -1); // không tạo ra được i từ các coin thì in -1
    
    show_exec_time();
}
