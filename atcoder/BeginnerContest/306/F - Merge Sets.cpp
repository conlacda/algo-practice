// https://atcoder.jp/contests/abc306/tasks/abc306_f
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
// const int INF = std::numeric_limits<int>::max();

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
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Thực hiện việc compress để lấy ra luôn vị trí của nó
    i, j
    Khi lắp ai, aj vào với nhau
    1 số aij sẽ có giá trị chính bằng số lượng số nhỏ hơn hoặc bằng nó
    Với số lượng số nhỏ hơn hoặc trong chính Ai. thì sẽ là 1, 2, ...M
    -> (1+M)*M/2. Có tổng cộng là N(N-1)/2 cặp i,j cần xét -> có (1+M)*M/2*N*(N-1)/2
    Số lượng số nhỏ hơn ai trong Aj sẽ được tính cùng toàn bộ Aj
    -> khi này cần tính số lượng số nhỏ hơn ai trong toàn bộ các số
    -> Xét hàng i, với mỗi số hàng i ta cần tính số lượng số đang nhỏ hơn a[i][j] trong toàn bộ dãy
    -> Dùng fenwick tree 0/1, với số nào tồn tại thì là 1, số nào bị xóa là 0.
    -> Với dãy đã sắp xếp ta tính ngay được số lượng số nhỏ hơn nó chính là index của nó (lower_bound)
    nhưng do có 1 số phần tử đã bị xóa nên cần dùng fenwicktree
    */
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, std::vector<int>(m));
    vector<int> f;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cin >> a[i][j];
            f.push_back(a[i][j]);
        }
    }
    int ans = 0;
    ans += m*(m+1)/2*n*(n-1)/2;
    sort(f.begin(), f.end());
    dbg(f);
    // Tính số phần tử nhỏ hơn x trong dãy từ m*i tới m*n
    FenwickTree<int> fw(vector<int>(n*m, 1));
    for (int i=0;i<m;i++) {
        int val = a[0][i];
        int index = std::lower_bound(f.begin(), f.end(), val) - f.begin();
        fw.set(index, 0);
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            // Xóa các số ở hàng hiện tại đi - vì hàng hiện tại đã được tính ở công thức N*(N-1)/2*M*(M+1)/2
            // Do i < j nên từ i cứ xóa cuốn chiếu, khi query thì chỉ còn các phần tử a[i+1...n][0..m] (hàng bên dưới)
            int val = a[i][j];
            int index = std::lower_bound(f.begin(), f.end(), val) - f.begin();
            fw.set(index, 0);
        }
        for (int j=0;j<m;j++) {
            // Query các số ở hàng hiện tại
            int val = a[i][j];
            int index = std::lower_bound(f.begin(), f.end(), val) - f.begin();
            ans += fw.sum(0, index);
        }
    }    
    cout << ans;
    show_exec_time();
}
