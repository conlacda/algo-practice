// [Atcoder|Codeforces].abcxxx.F
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
    vector<int> a;
    const int ROOT = 0, LAST = -1;
    a.push_back(ROOT);
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    a.push_back(LAST);
    n = a.size();
    dbg(a);
    map<int, int> prev, next; // m[value] = next_value;
    for (int i=0;i<n-1;i++)
        next[a[i]] = a[i+1];
    for (int i=n-1;i>=1;i--)
        prev[a[i]] = a[i-1];
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            // add
            int val, v;
            cin >> val >> v;
            int nextval = next[val];
            next[val] = v;
            next[v] = nextval;
            prev[nextval] = v;
            prev[v] = val;
        } else {
            // remove
            int val;
            cin >> val;
            int nextval = next[val];
            int prevval = prev[val];
            next[prevval] = nextval;
            prev[nextval] = prevval;
            next.erase(val);
            prev.erase(val);
        }
    }
    int r = ROOT;
    while (r != LAST) {
        r = next[r];
        if (r == LAST) break;
        cout << r << ' ';
    }

    show_exec_time();
}

