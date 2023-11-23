// https://codeforces.com/contest/1899/problem/G
#include<bits/stdc++.h>

typedef long long ll;
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// Range query, point update
template <typename T>
struct FenwickTree {
private:
    vector<T> bit;
    T n;
public:
    FenwickTree(){}
    void build(T n) { this->n = n; bit.assign(n, 0); }
    void build(vector<T> a) { build(a.size()); for (int i = 0; i < (int) a.size(); i++) add(i, a[i]); }
    FenwickTree(vector<T> a) { build(a); }
    T sum(T r) {
        if (r==-1) return 0;
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
        return ret;
    }

    T sum(T l, T r) {
        assert(0 <= l && l <= r && r < n);
        return sum(r) - sum(l-1);
    }

    void add(T idx, T delta) {
        assert(0 <= idx && idx < n);
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
    }
    void set(T idx, T val) {
        T diff = val - sum(idx, idx);
        add(idx, diff);
    }

    vector<T> original(){ // Return original value of input vector
        vector<T> a;
        for (T i=0;i<this->n;i++) a.push_back(sum(i,i));
        return a;
    }
};

// euler_tour_on_tree
vector<int> first, second;
void makeEulerTour(vector<vector<int>>& adj) {
    int n = adj.size();
    first.resize(n); second.resize(n); // first[v] - thời điểm duyệt v, second[v] - thời điểm ra khỏi v
    int clock = 0;
    std::function<void(int, int)> dfs = [&](int u, int p){
        first[u] = clock++;
        for (auto v: adj[u]) {
            if (v != p) dfs(v, u);
        }
        second[u] = clock++;
    };
    dfs(0, 0);
}

// Temporary version                
const int blockSize = 400; // 300, 700

struct Query {
    int l, r, x, index;
    friend bool operator<(Query& a, Query& b) {
        // những cái thuộc cùng 1 block sẽ đứng cạnh nhau, những cái cùng block thì r sẽ xếp từ bé tới lớn
        if (a.l/blockSize != b.l/blockSize) return a.l < b.l;
        return (a.l/blockSize & 1) ? (a.r < b.r) : (a.r > b.r);
    }
    friend std::ostream& operator<<(std::ostream& os, const Query &s) { return os << destructure(s);}
};
struct Ans {
    int index, val;
    friend bool operator<(Ans& a, Ans& b) {
        return a.index < b.index;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ans &s) { return os << destructure(s);}
};

struct Mo {
private:
    vector<int> a; // mảng đầu vào
    vector<Query> queries; // l, r, index
    FenwickTree<int> fw;
public:
    // set<int> data; // lưu trạng thái hiện tại - lưu tần số của từng số có trong range [left, right] hiện tại
    vector<Ans> ans; // index, val
    int cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    Mo(vector<int>& p) {
        for (auto v: p) a.push_back(first[v]);
        this->a = a;
        fw.build(vector<int>((int) p.size() * 2, 0));
    }
    void add(int index) {
        fw.add(a[index], 1);
    }
    void remove(int index) {
        fw.add(a[index], -1);
    }
    int getResult(int x) {
        int s = fw.sum(first[x], second[x]);
        if (s > 0) return 1;
        return 0;
    }
    void solve(vector<Query>& queries) {
        sort(queries.begin(), queries.end());
        int left = 0, right = -1;
        for (auto query: queries) {
            while (left > query.l) left--, add(left);
            while (right < query.r) right++, add(right);
            while (left < query.l) remove(left), left++;
            while (right > query.r) remove(right), right--;
            ans.push_back({query.index, getResult(query.x)});
        }
        sort(ans.begin(), ans.end());
        for (auto v: ans) {
            if (v.val) cout << "YES\n";
            else cout << "NO\n";
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> p(n);
    for (auto& v: p) {cin >> v; v--;}
    vector<Query> queries;
    for (int i=0;i<q;i++) {
        int u, v, x;
        cin >> u >> v >> x;
        u--; v--; x--; // x la node tren tree, u, v la index cua vector p
        queries.push_back({u, v, x, i});
    }
    makeEulerTour(adj);
    Mo mo(p);
    mo.solve(queries);
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
*/
