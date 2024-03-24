// https://atcoder.jp/contests/abc346/tasks/abc346_f
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

// Range query, point update
template <typename T = int>
struct FenwickTree {
private:
    vector<T> bit; // binary indexed tree
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

    int sum_from(int idx) {
        return sum(idx, n-1);
    }
    
    int firstIndexWithSumFromK(int idx, int val) {
        // Tìm ra index k nhỏ nhất để sum(idx, k) >= val
        // nếu không có k nào thỏa mãn thì return n-1
        int l = idx, r = n-1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (sum(idx, mid) >= val) r = mid;
            else l = mid + 1;
        }
        if (l != n-1)
            assert(sum(idx, l) >= val);
        return l;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    string s;
    string t;
    cin >> s >> t;
    dbg(s, t);
    /*
    Binary search??
    Độ dài string s*n biết sẵn
    l = 0, r = s.size()*n/t.size();
    */
    map<char, int> ms;
    for (auto v: s) ms[v]++;
    for (auto v: t) if (ms[v] == 0) {
        cout << "0";
        return 0;
    }
    vector<FenwickTree<int>> forest(27, FenwickTree(vector<int>((int) s.size() ,0)));
    for (int i=0;i<(int) s.size();i++) {
        forest[s[i]-'a'].set(i, 1);
    }
    // dùng 27 fenwicktree cho từng chữ cái
    int sz = (int) s.size();
    int msz = sz * n;
    std::function<bool(int)> isGood = [&](int kk) {
        int cur = 0;
        for (auto&v: t) {
            dbg(v, cur);
            int k = kk;
            // tìm ra vị trí đầu tiên chứa "v" * k
            // dùng binary search
            int block_num = cur / sz;
            int index = cur - block_num * sz;
            int remain = forest[v-'a'].sum_from(index);
            // Nếu block hiện tại ko có đủ k kí tự thì nhảy qua block sau
            if (remain < k) {
                k -= remain;
                block_num++;
                cur = block_num * sz;
                index = 0;
            }
            int all = forest[v-'a'].sum_from(0);
            if (k > all) {
                int next = k / all;
                if (k % all == 0) next--;
                block_num += next;
                cur += next * sz;
                k -= next * all;
                index = 0;
            }
            assert(k <= all);
            if ((block_num+1) * sz > msz) return false;
            // tìm ra index X có fw.sum(index, x) == k
            dbg(v, index, k, forest[v-'a'].firstIndexWithSumFromK(index, k));
            cur += forest[v-'a'].firstIndexWithSumFromK(index, k) - index + 1;
        }
        return true;
    };
    int l = 0, r = (int) s.size() * n / (int) t.size() + 1;
    while (l < r-1) {
        int mid = (l + r) / 2;
        if (isGood(mid)) l = mid;
        else r = mid -1;
    }
    dbg(l, r);
    if (isGood(r)) cout << r;
    else {
        // assert(isGood(l));
        cout << l;
    }
    show_exec_time();
}
/*
2
aab
aaaab

=> return 0 but actual is 1
*/
