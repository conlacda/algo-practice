// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

template <typename T = int>
struct FenwickTree {
private:
    void internal_update(int idx, T val) {
        assert(0 < idx && idx <= N);
        for (int i = idx; i < N; i += (i & (-i))) {
            bit[i] += val;
        }
    }
public:
    vector<T>bit;
    int N;
    FenwickTree(int n) {
        this->N = n + 1;
        bit.assign(n + 1, 0);
    }
    FenwickTree(vector <T> a) : FenwickTree(a.size()) {
        for (int i = 0; i < (int) a.size(); i++) {
            add(i, i, a[i]);
        }
    }

    // s[l<=i<=r] += val;
    void add(int l, int r, T val) {
        l++; r++;
        internal_update(l, val);
        internal_update(r + 1, -val);
    }
    T at(int idx) {
        assert(0 <= idx && idx < N-1);
        T ans = 0;
        for (int i = idx+1; i; i -= (i & (-i))) ans += bit[i];
        return ans;
    }
    vector<T> original(){
        vector<T> org;
        for (int i=0;i<N-1;i++) org.push_back(this->at(i));
        return org;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& v: a) cin >> v;
    for (auto&v: b) cin >> v;
    /*
    Lấy toàn bộ bóng từ lọ Bi chia đều cho các lọ xung quanh
    -> Range update, point query
    // fw.add(l, r, val);
    // Có tối đa 3 khoảng sẽ được update
    */
    FenwickTree<int> fw(a);
    for (int i=0;i<m;i++) {
        int box = b[i];
        int val = fw.at(box);
        // remove lọ này đi
        fw.add(box, box, -val);
        dbg(val);
        // cập nhật tất cả
        int all = val / n;
        fw.add(0, n-1, all);
        val -= all * n;
        // cập nhật tới cuối
        int end = min(box + val, n-1);
        fw.add(box + 1, end, 1);
        val -= end - box;
        // cập nhật lên đầu
        end = val - 1;
        fw.add(0, end, 1);
    }
    for (auto v: fw.original()) {
        cout << v << ' ';
    }
    
    show_exec_time();
}
