#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1, 0);
    for (int i=0;i<n;i++) cin >> a[i];
    map<int, int> m; for (int i=0;i<n;i++) m[min(a[i], n)]++;
    FenwickTree<int> fw(vector<int>(n+1, 0));
    for (int i=0;i<n;i++) fw.set(min(a[i], n), 1);
    std::function<int()> getAns = [&](){
        int l = 0, r = n;
        while (l != r) {
            int mid = (l+r) /2;
            if (fw.sum(0, mid) < mid + 1) r = mid;
            else l = mid + 1;
        }
        return l;
    };
    while (q--) {
        int index, val;
        cin >> index >> val;
        index--;
        if (a[index] == val) {
            cout << getAns() << '\n';
        } else {
            val = min(val, n);
            dbg(index, val);
            m[a[index]]--;
            m[val]++;
            dbg(m);
            if (m[a[index]] == 0) {
                fw.set(a[index], 0);
            }
            fw.set(val, 1);
            a[index] = val;
            cout << getAns() << '\n';
        }
    }
    
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
//////////////////////////////////////////////////////////////////////////
// Cách 2: chỉ sử dụng set<int>
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    map<int, int> m;
    set<int> ne; // not exist
    for (int i=0;i<=n;i++) ne.insert(i);
    for (auto &v: a) {
        ne.erase(v);
        m[v]++;
    }
    dbg(ne);
    while (q--) {
        int index, val;
        cin >> index >> val;
        index--;
        m[a[index]]--; m[val]++;
        ne.erase(val);
        if (m[a[index]] == 0) 
            ne.insert(a[index]);
        a[index] = val;
        cout << *ne.begin() << '\n';
    }
    
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