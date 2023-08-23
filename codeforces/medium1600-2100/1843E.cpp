// Technique: binary search with fenwick tree
// https://codeforces.com/contest/1843/problem/E
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

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
        return sum(r) - sum(l-1);
    }

    void add(T idx, T delta) {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
    }
    void set(T idx, T val) {
        T diff = val - sum(idx, idx);
        add(idx, diff);
    }
};
void solve() {
    /*
    Gọi k là kết quả
    k nằm trong khoảng từ 1->q
    binary search cho k với hàm isGood(k) để check xem tại đó (OlogN)
    thì có segment nào thỏa mãn không (for seg: segment) -> O(N)
    Lưu ý:
    Bài này hơi khác 1 chút, thay vì isGood(k) liên tục khởi tạo lại
    toàn bộ quá trình for (int i=0;i<k;i++) { add(index)};
    thì mình chỉ chuyển từ index này sang index khác
    Ví dụ có l = 0, r = 8. mid = 4 thì add(index 0, 1, 2, 3, 4)
    mid = 4 chuyển qua mid = 6 thì add(index 5, 6) - fw.set(index, 1) - OlogN
    mid = 4 chuyển qua mid = 2 thì remove(index 4, 3) - fw.set(index, 0)
    chuyển qua lại các index này giống như ở Mo's algorithm. Mỗi lần dịch thì khoảng cách giảm đi 1 nửa -> n+n/2+n/4+... = 2n != n^2
    */
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> segment;
    for (int i=0;i<k;i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        segment.push_back({l, r});
    }
    int q;
    cin >> q;
    vector<int> index(q);
    for (int i=0;i<q;i++) {
        cin >> index[i];
        index[i]--;
    }
    // FenwickTree<int> fw;
    // fw.build(vector<int>(n, 0));
    int l = 0, r = q-1;
    int ans = INF;
    std::function<int(int)> isGood = [&](int u){
        FenwickTree<int> fw;
        fw.build(vector<int> (n, 0));
        for (int i=0;i<=u;i++) {
            fw.set(index[i], 1);
        }
        bool ok = false;
        for (auto seg: segment) {
            int len = seg.second - seg.first + 1;
            int sum = fw.sum(seg.first, seg.second);
            if (sum > len/2) {
                ok = true;
                break;
            }
        }
        return ok;
    };
    while (l < r) {
        int mid = (l + r) /2;
        if (isGood(mid)) {
            ans = min(ans, mid);
            r = mid;
        } else {
            l = mid+1;
        }
    }
    if (isGood(r)) {
        ans = min(ans, r);
    }
    if (ans == INF) {
        cout << -1 << '\n';
    } else cout << ans+1 <<'\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();
    show_exec_time();
}