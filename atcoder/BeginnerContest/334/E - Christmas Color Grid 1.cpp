// Atcoder.abcxxx.
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
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

struct DSU {
    vector<int> p, sz;
    // stores info from the past
    vector<pair<int, int>> past_parent, past_size;
    DSU(int n) {
        p.resize(n);
        sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) { return (p[x] == x) ? x : find(p[x]); }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (sz[a] < sz[b]) { swap(a, b); }
        // add to history
        past_parent.push_back({b, p[b]});
        past_size.push_back({a, p[a]});

        if (a != b) {
            p[b] = a;
            sz[a] += sz[b];
        }
    }

    bool isSame(int a, int b) { return find(a) == find(b); }

    // Reverts to previous DSU state.
    void rollback() {
        p[past_parent.back().first] = past_parent.back().second;
        sz[past_size.back().first] = past_size.back().second;
        past_parent.pop_back();
        past_size.pop_back();
    }
};


ll inv(ll a, ll m = mod) {
    a %= mod;
    ll x, y;
    auto extended_gcd = [&] (ll a, ll b) -> ll {
        x = 1; y =0;
        ll x1 = 0, y1 = 1, a1 = a, b1 = b;
        while (b1) {
            ll q = a1 / b1;
            tie(x, x1) = make_tuple(x1, x - q * x1);
            tie(y, y1) = make_tuple(y1, y - q * y1);
            tie(a1, b1) = make_tuple(b1, a1 - q * b1);
        }
        return a1; // a1 chính là std::gcd(a, b);
    };
    ll g = extended_gcd(a, m);
    if (g != 1) return -1;
    else x = (x%m +m) %m;
    return x;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &v : a) cin >> v;
    DSU dsu(n*m);
    std::function<bool(int, int)> isIn = [&](int r, int c){
        return (r >= 0) && (c>=0) && (r<n) && (c<m);
    };
    std::function<vector<pair<int,int>>(pair<int,int>)> neighbors = [&](pair<int,int> p){
        vector<int> dx = {0, -1, 1}, dy = {0, -1, 1};
        vector<pair<int,int>> res;
        for (auto x: dx) {
            for (auto y: dy) {
                if (isIn(p.first + x, p.second + y) && x * y == 0) {
                    if (x == 0 && y == 0) continue;
                    res.push_back({p.first + x, p.second + y});
                }
            }
        }
        return res;
    };
    for (int r=0;r<n;r++) {
        for (int c=0;c<m;c++) {
            if (a[r][c] == '.') continue;
            for (auto nb: neighbors({r, c})) {
                if (a[nb.first][nb.second] == '#') {
                    dsu.merge(r*m+c, nb.first*m+nb.second);
                }
            }
        }
    }
    set<int> cc;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (a[i][j] == '#') {
                cc.insert(dsu.find(i*m+j));
            }
        }
    }
    int sum = 0;
    int point = 0;
    for (int r=0;r<n;r++) {
        for (int c=0;c<m;c++) {
            int time = 0;
            if (a[r][c] == '#') continue;
            point++;
            int ccnum = cc.size() + 1;
            auto nbs = neighbors({r, c});
            for (auto nb: nbs) {
                if (a[nb.first][nb.second] == '.') continue;
                if (!dsu.isSame(nb.first * m + nb.second, r*m+c)) {
                    ccnum--;
                    dsu.merge(nb.first * m + nb.second, r*m+c);
                    time++;
                }
            }
            sum += ccnum;
            while (time--) dsu.rollback();
        }
    }
    // Luu y - buoc phai co dong nay
    sum %= mod;
    int res = inv(point) * sum % mod;
    assert(res * point % mod == sum % mod);
    cout << res;

    show_exec_time();
}