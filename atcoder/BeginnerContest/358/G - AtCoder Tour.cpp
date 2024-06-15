// [Atcoder|Codeforces].abcxxx.F
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

template <class T = int>
bool smax(T& x, T y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, k;
    int s1, s2;
    cin >> n >> m >> k;
    cin >> s1 >> s2; s1--;s2--;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }
    /*
    Dùng dp??
    dp[i][j][K = times] => sum
    K = 1e9 -> K lớn hơn H * W thì khi này sẽ đi được mọi điểm

    // Init -> mọi điểm đều là 0
    // move thì bắt đầu K bị giảm đi 1 và tính giá trị nếu điểm đó là điểm cuối cùng
    move đi rồi thì sẽ không bao giờ quay lại nữa
    // in ra kết quả
    vector dp(3, vector(4, vector<int>(5, 0)));
    */
    std::function<vector<pair<int,int>>(pair<int,int>)> getAdj= [&](pair<int,int> p) {
        vector<pair<int,int>> ans;
        if (p.first > 0) ans.push_back({p.first - 1, p.second});
        if (p.first < n-1) ans.push_back({p.first + 1, p.second});
        if (p.second > 0) ans.push_back({p.first, p.second - 1});
        if (p.second < m-1) ans.push_back({p.first, p.second + 1});
        return ans;
    };
    /*
    Khi từ p1->p2 thì mọi k của p2 sẽ được tính lại toàn bộ
    mỗi khi được tính lại toàn bộ thì lại được đẩy vào queue 1 lần nữa
    */
    int extra = 0;
    extra = max(extra, k - m * n);
    k -= extra;
    vector dp(n, vector(m, vector<int>(k+1, 0)));
    dp[s1][s2][k] = 1;
    /*
    Bắt đầu từ điểm {s1, s2}
    Mỗi lần di chuyển sang 1 node nếu mà số điểm khi di chuyển có thể được tăng lên
    điểm u với k lần còn lại -> v với k-1 lần
    point[u][k] + a[v] -> point[v][k]
    có 1 điều lưu ý tại đây là việc điểm u với k lần (gọi tắt là (u,k)) sang (v, k-1)
    thì tức là ko thể đi từ (v,k-1) sang (u,k-2) được vì đứng yên tại (u, k) 2 nhịp
    sẽ lớn hơn (v, k-2)
    Tại đây mỗi lần đứng ở điểm p thì ta sẽ tính toán lại toàn bộ giá trị k
    ví dụ đứng ở (1, 1) với a[1][1] = 2 và point hiện tại khi còn k = 3 lần di chuyển là 0
    -> 0, 0, 0 sẽ thành 0, 2, 4
    ví dụ đi tới (1, 0) được thì đưa nó vào queue rồi lại tính lại toàn bộ (1, 0) sau đó rồi mới đi tiếp.
    => Mấu chốt: tính lại giá trị của điểm với mọi k trước khi di chuyển.
                di chuyển tới v thì đưa v vào queue và lại lặp tính -> move
    */

    queue<pair<int,int>> Q;
    Q.push({s1, s2});
    map<pair<int,int>, bool> in_queue;
    while (!Q.empty()) {
        pair<int,int> p = Q.front();
        Q.pop();
        // tính toán lại toàn bộ giá trị cho điểm này
        for (int i=k;i>=1;i--) {
            if (dp[p.first][p.second][i] > 0) {
                smax(dp[p.first][p.second][i-1], dp[p.first][p.second][i] + a[p.first][p.second]);
            }
        }
        // di chuyển sang các ô khác
        for (auto adj: getAdj(p)) {
            for (int i=k;i>=1;i--) {
                if (dp[p.first][p.second][i] > 0) { 
                    if (smax(dp[adj.first][adj.second][i-1], dp[p.first][p.second][i] + a[adj.first][adj.second])) {
                        if (!in_queue[adj]) {
                            in_queue[adj] = true;
                            Q.push(adj);
                        }
                    }
                }
            }
        }
        in_queue[p] = false;
    }
    int ans = 0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            ans = max(ans, dp[i][j][0] + extra * a[i][j]);
        }
    }
    cout << ans - 1;
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
