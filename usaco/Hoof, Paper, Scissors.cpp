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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        freopen("hps.in", "r", stdin);
        freopen("hps.out", "w", stdout);
    #endif
    int n, k;
    cin >> n >> k;
    /*
    Với tối đa K lần thay đổi thì thắng được tối đa bao nhiêu lượt
    Dùng dp[] để tính
    dp[index][k][cur_gesture] = point
    index: vị trí hiện tại
    k: số lần thay đổi còn lại
    cur_gesture: búa, lá, kéo  PHS  H > S > P > H
    H = 0, S = 1, P = 2
    */
    vector<int> a(n);
    for (auto &v: a) {
        char k; cin >> k;
        if (k == 'H') v = 0;
        else if (k == 'S') v = 1;
        else v = 2;
    }
    dbg(a);
    std::function<int (int)> win = [&](int u){
        return (u+2) % 3;
    };
    std::function<int (int)> lose = [&](int u){
        return (u+1) % 3; 
    };
    // Init state
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k+1, vector<int>(3, 0)));
    dp[0][k][win(a[0])] = 1;
    // transition
    // dp[index][k][gesture] = dp[index-1][k-1][new_gesture] + 1|0
    // dp[index][k][gesture] = dp[index-1][k][same_gesture] +1|0
    for (int i=1;i<n;i++) {
        for (int _k = 0;_k<=k;_k++) {
            for (int gesture = 0;gesture < 3;gesture++) {
                // Không đổi gesture
                dp[i][_k][gesture] = max(dp[i][_k][gesture], dp[i-1][_k][gesture] + (gesture == win(a[i])));
                // Có đổi gesture
                if (_k > 0) {
                    int new_gesture = win(gesture);
                    dp[i][_k-1][new_gesture] = max(dp[i][_k-1][new_gesture], dp[i-1][_k][gesture] + (new_gesture == win(a[i])));
                    new_gesture = lose(gesture);
                    dp[i][_k-1][new_gesture] = max(dp[i][_k-1][new_gesture], dp[i-1][_k][gesture] + (new_gesture == win(a[i])));
                }
            }
        }
    }
    // answer
    int answer = 0;
    for (int _k=0;_k<=k;_k++) {
        for (int gesture = 0;gesture < 3;gesture++) {
            answer = max(answer, dp[n-1][_k][gesture]);
        }
    }
    dbg(dp);
    cout << answer;
    show_exec_time();
}
