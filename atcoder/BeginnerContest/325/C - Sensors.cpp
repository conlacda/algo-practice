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

class DSU {
 public:
    vector<int> parent, rank;
    int N;
    DSU(int N) {
        this->N = N;
        this->parent.resize(N);
        this->rank.resize(N, 0);
        for (int i = 0; i < N; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int v) {
        assert(0 <= v && v < N);
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
    bool isSame(int a, int b) {
        return find(a) == find(b);
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i=0;i<n;i++) {
        cin >> a[i];
    }
    DSU dsu(n*m);
    std::function<int(int, int)> id = [&](int i, int j){
        return i * m + j;
    };
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (a[i][j] == '.') continue;
            if (i-1>=0 && a[i-1][j] == '#') dsu.merge(id(i, j), id(i-1, j));
            if (i-1 >=0 && j-1>= 0 && a[i-1][j-1] == '#') dsu.merge(id(i, j), id(i-1, j-1));
            if (i-1>=0 && j+1<m && a[i-1][j+1] == '#') dsu.merge(id(i, j), id(i-1, j+1));
            if (j+1<m && a[i][j+1] == '#') dsu.merge(id(i, j), id(i, j+1));
            if (j-1>=0 && a[i][j-1] == '#') dsu.merge(id(i, j), id(i, j-1));
            if (i+1<n && j-1>= 0 && a[i+1][j-1] == '#') dsu.merge(id(i, j), id(i+1, j-1));
            if (i+1<n && a[i+1][j] == '#') dsu.merge(id(i, j), id(i+1, j));
            if (i+1<n && j+1<m && a[i+1][j+1] == '#') dsu.merge(id(i, j), id(i+1, j+1));
        }
    }
    unordered_set<int> s;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (a[i][j] == '#')
                s.insert(dsu.find(id(i, j)));
        }
    }
    cout << s.size();
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/