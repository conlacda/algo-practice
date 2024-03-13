// https://atcoder.jp/contests/abc343/tasks/abc343_g
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
// #define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int overlapLen(string s, string t) {
    // abcd & cde có overlap = 2 (cd)
    string ts = t + s;
    vector<int> z = z_function(ts);
    int ans = 0;
    for (int i= (int) ts.size()-1;i>=(int) ts.size() - (int) s.size();i--) {
        if (z[i] + i == (int) ts.size())
            ans = max(ans, z[i]);
    }
    ans = min(ans, (int) t.size());
    return ans;
}

bool contains(const string &s, const string &t) {
    int n = s.size(), m = t.size();
    vector<int> za = z_function(t + s);
    for (int i = m; i <= n; i++) {
        if (za[i] >= m) return true;
    }
    return false;
}

// Traveling salesman problem
int tspp(const vector<vector<int>>& dist, vector<int> initialCost) {
    assert(dist.size() == initialCost.size() && "initialCost là cost ban đầu phải trả để vào node. Start node ko được quay lại từ end node");
    int n = dist.size();
    vector dp(1 << n, vector<int>(n, INF/2));
    for (int i = 0; i < n; i++) dp[1 << i][i] = initialCost[i];
    for (int bit = 1; bit < (1 << n) - 1; bit++) {
        for (int i = 0; i < n; i++) {
            if (~bit >> i & 1) continue;
            for (int j = 0; j < n; j++) {
                if (bit >> j & 1) continue;
                dp[bit | 1 << j][j] = min(dp[bit | 1 << j][j], dp[bit][i] + dist[i][j]);
            }
        }
    }
    return *min_element(dp.back().begin(), dp.back().end());
}
int tspp(const vector<vector<int>>& dist) {
    vector<int> initialCost(dist.size(), 0);
    return tspp(dist, initialCost);
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Tất cả những string bị bao trọn thì ko cần nữa, chỉ giữ lại string ko bị bao trọn bởi string khác
    Với 2 string bất kỳ ta lấy f(s, t) là độ bao phủ của s lên phần đầu của t
    Bài toán trở thành traveling salesman chỉ khác là dist(n-1, 0) = 0
    Với mỗi string ith đặt là điểm bắt đầu thì mọi dist(k=0..n-1 != i, i) = 0
    Lấy ra min ans là xong
    */
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto&v: s) cin >> v;
    // Loại bỏ string trùng lặp đi
    set<int> removed;
    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            if (s[i] == s[j]) removed.insert(i);
            else {                
                if (contains(s[i], s[j]))
                    removed.insert(j);
                if (contains(s[j], s[i]))
                    removed.insert(i);
            }
        }
    }
    dbg(removed);
    vector<string> _s;
    for (int i=0;i<n;i++) {
        if (removed.count(i) == 0) _s.push_back(s[i]);
    }
    s = _s;
    dbg(s);
    n = s.size();
    // Dựng lên mảng dist[][] 2 chiều bằng việc dùng overlap
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (i != j)
                dist[i][j] = (int) s[j].size() - overlapLen(s[i], s[j]);
        }
    }
    // for (int i=0;i<n;i++) dist[n][i] = s[i].size();
    dbg(dist);
    // Thay đổi dist để nhét nó vào tsp
        // i sẽ là start string
        // Tsp thì xoay vòng tròn còn ở đây thì n-1 về 0 đều là 0
        // hay nói cách khác là mọi string về ith đều là 0 (dist[k=0..n-1][i] = 0)
    vector<int> initialCost(n);
    for (int i=0;i<n;i++) initialCost[i] = s[i].size();
    cout << tspp(dist, initialCost);

    show_exec_time();
}
// TODO : tìm chu trình cụ thể cho TSP
// Xem submission của umnik phan contest nay
