// https://atcoder.jp/contests/abc348/tasks/abc348_b
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<pair<int,int>> points(n);
    for (auto&p: points) {
        cin >> p.first >> p.second;
    }
    vector<vector<double>> dist(n, vector<double>(n));
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            dist[i][j] = sqrt( pow(points[i].first - points[j].first, 2) + pow(points[i].second - points[j].second, 2));
        }
    }
    for (int i=0;i<n;i++) {
        cout << max_element(dist[i].begin(), dist[i].end()) - dist[i].begin() +1 << '\n'; 
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
