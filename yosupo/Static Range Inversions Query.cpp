// https://judge.yosupo.jp/problem/static_range_inversions_query
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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

template<typename T = int>
struct Compress {
    vector<T> rcv; // recover - giá trị mảng ban đầu đã sort và xóa unique
    vector<T> cpr; // compressed - giá trị đã nén của mảng a
    Compress() {}
    Compress(vector<T>& a) { build(a);}
    void build(vector<T>& a) {
        rcv = a;
        sort(rcv.begin(), rcv.end());
        rcv.resize(unique(rcv.begin(), rcv.end()) - rcv.begin());

        cpr.resize(a.size());
        for (int i = 0; i < (int) cpr.size(); ++i) 
            cpr[i] = lower_bound(rcv.begin(), rcv.end(), a[i]) - rcv.begin(); // O(logN) thay cho map
    }
    T compressed_val(T originalVal) { // giá trị ban đầu sang giá trị đã compress
        T i = lower_bound(rcv.begin(), rcv.end(), originalVal) - rcv.begin();
        if (rcv[i] != originalVal) return -1;
        return i;
    }
    T operator[] (int index) {
        return cpr[index];
    }
    T original_val(T compressedVal) {
        return rcv[compressedVal];
    }   
};

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
        if (!(0 <= l && l <= r && r < n)) return 0;
        // assert(0 <= l && l <= r && r < n);
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
    
    // Tìm ra index x nhỏ nhất để sum(start_index, x) >= K
    // nếu không có x nào thỏa mãn -> return n-1
    int firstIndexWithSumFromK(int start_index, int K) {
        int l = start_index, r = n-1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (sum(start_index, mid) >= K) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};

inline int64_t hilbertOrder(int x, int y, int pow = 21, int rotate = 0) { // 2**pow là số lượng query sẽ xử lý
    if (pow == 0) return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2*pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct Query {
    int l, r, index;
    ll ord = -1;
    friend bool operator<(Query& a, Query& b) {
        return a.ord < b.ord;
    }
};

struct Mo {
private:
    vector<int> a; // mảng đầu vào
public:
    FenwickTree<int> fw;
    vector<int> ans;
    int cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    Mo(vector<int>& a) {
        this->a = a;
        fw = FenwickTree(vector<int>(a.size(), 0));
    }
    void addLeft(int index) {
        cur_result += fw.sum(0, a[index] - 1);
        fw.add(a[index], 1);
    }
    void addRight(int index) {
        cur_result += fw.sum_from(a[index] + 1);
        fw.add(a[index], 1);
    }
    void removeLeft(int index) {
        cur_result -= fw.sum(0, a[index] - 1);
        fw.add(a[index], -1);
    }
    void removeRight(int index) {
        cur_result -= fw.sum_from(a[index] + 1);
        fw.add(a[index], -1);
    }
    ll getResult() {
        return this->cur_result;
    }
    vector<int> solve(vector<Query>& queries) {
        for (auto& q: queries) q.ord = hilbertOrder(q.l, q.r);
        sort(queries.begin(), queries.end());
        ans.resize(queries.size());
        ll left = 0, right = -1;
        for (auto query: queries) {
            while (left > query.l) left--, addLeft(left);
            while (right < query.r) right++, addRight(right);
            while (left < query.l) removeLeft(left), left++;
            while (right > query.r) removeRight(right), right--;
            ans[query.index] = getResult();
        }
        return ans;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    Compress com(a);
    a = com.cpr;
    Mo mo(a);
    vector<Query> queries;
    for (int i=0;i<q;i++) {
        int u, v;
        cin >> u >> v;
        v--;
        queries.push_back({u, v, i});
    }
    mo.solve(queries);
    for (auto v: mo.ans) cout << v << '\n';
    // dbg(mo.ans);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này dùng Mo
Khi này data (cửa số dữ liệu) sẽ duy trì 1 set.
Bài toán khi này trở thành thêm 1 phần tử vào trái thì có bao nhiêu phần tử phải nhỏ hơn nó
và thêm vào phải thì trái bao nhiêu phần tử lớn hơn nó
Thoạt nhìn thì có thể sử dụng set để thêm 1 phần tử rồi theo order 
rồi dùng binary search tìm ra được có bao nhiêu số lớn/nhỏ hơn nó
=> thực ra thì ko có cách nào cả với set kể cả policy based set

Tại đây sử dụng fenwicktree.
* Compress mảng thành dạng index
* Dựng fenwicktree với mảng full 0
* thêm phần tử thì tăng index đó lên 1
* đếm số lượng phần tử nhỏ hơn hay lớn hơn thì đơn giản là lấy sum vì khi này a[index] chính là index trên fw
=> cửa sổ dữ liệu được maintain bằng cách sử dụng fw
*/
