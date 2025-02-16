// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

vector<int> calLIS(vector<int> const& a) {
    int n = a.size();
    vector<int> d(n + 1, INF);
    d[0] = -INF;
    vector<int> lis(n, 1);

    for (int i = 0; i < n; i++) {
        int k = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[k - 1] < a[i] && a[i] < d[k]) {
            d[k] = a[i];
            lis[i] = k;
        }
        if (k > 0 and d[k-1] == a[i]) {
            lis[i] = k - 1;
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++)
        if (d[i] != INF)
            ans = i;

    return lis;
}

struct Query {
    int q_index, max_index, max_val;
    friend bool operator<(Query& a, Query& b) {
        return a.max_index < b.max_index;
    }
};

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Tại 1 điểm lấy ra số lớn nhất gần với nó và in ra index đó
    */
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    auto lis = calLIS(a);
    vector<Query> queries;
    for (int i=0;i<q;i++) {
        int max_index, max_val;
        cin >> max_index >> max_val;
        // Tìm ra vị trí mà a[i] <= max_val và có lis[i] lớn nhất có thể
        //  1 5 3 4 6
        // sắp xếp lại toàn bộ để xử lý offline
        // map<int, set<int>> m;
        // m[length] => set of value
        // với mỗi length này sẽ biết được nó kết thúc tại các value nào
        // thực ra chỉ cần mỗi giá trị cuối
        // m[length] = min_value
        // vector<int> m;
        queries.push_back(Query{i, --max_index, max_val});
    }
    sort(queries.begin(), queries.end());
    vector<int> m(n + 1, INF);
    vector<int> ans(q);
    int old_index = -1;
    for (auto&q: queries) {
        for (int i=old_index+1;i<=q.max_index;i++) {
            m[lis[i]] = min(m[lis[i]], a[i]);
        }
        old_index = q.max_index;
        // binary search trên cái độ dài
        int l = 1, r = q.max_index + 1;
        while (l < r) {
            int mid = (l + r) /2;
            if (mid * 2 < l + r) mid++;
            if (m[mid] <= q.max_val) l = mid;
            else r = mid - 1;
        }
        ans[q.q_index] = l;
    }
    for (auto&v: ans) cout << v << '\n';
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
