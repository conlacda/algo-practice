// https://codeforces.com/problemset/problem/1082/E
// DP + Fenwick tree
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
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    /*
    Dùng fenwick tree 0-1 để đếm số lượng số = k trong khoảng [l:r]
    Duyệt 1 loạt qua dãy rồi lập map[x] = vector<>index of x
    Duyệt qua lần lượt từng số -> toàn bộ N phần tử rồi query logN
    -> O(NlogN)
    */
    vector<int> b;
    for (int i=0;i<n;i++) {
        if (a[i] == k) b.push_back(1);
        else b.push_back(0);   
    }
    FenwickTree<int> fw(b);
    map<int, vector<int>> m;
    for (int i=0;i<n;i++) {
        m[a[i]].push_back(i);
    }
    int ans = (int) m[k].size();
    for (auto v: m) {
        if ((int) v.second.size() < 1) continue;
        if (v.first == k) continue;
        // int x = v.first;
        auto indexes = v.second;
        // giải bài toán range liên tục có sum of sub array max -> dp
        vector<int> dp((int) indexes.size(), (int) m[k].size() +1);
        for (int i=1;i<(int) indexes.size();i++) {
            dp[i] = max(dp[i-1] - fw.sum(indexes[i-1], indexes[i]) + 1, dp[i]);
        }
        dbg(v.first, v.second, dp);
        int _max_dp = *max_element(dp.begin(), dp.end());
        ans = max(ans, _max_dp);
    }
    cout << ans;
    show_exec_time();
}
/*
Lời giải:
Bài này cho 1 dãy a(N) phần tử 1<=ai<=1e5 (ai lớn quá thì sẽ dùng coordinator compress)
Cho số k, chọn 1 range [l:r] và cộng toàn bộ với lượng. Dãy mới có tối đa bao nhiêu số 
bằng k.
Ví dụ: a = {6, 2, 6} và k = 2 -> chọn l:r = 0, 2 và trừ cả dãy đi 4 ta có 2 số 2 = k.
Ý tưởng đầu tiên:
* Lấy ra toàn bộ index của các phần tử rồi duyệt qua nó map[6] = {0, 2}
* Duyệt từ 0->2 thì thêm được 1 số và số 2 ở giữa (bằng giá trị k) sẽ bị loại bỏ
* Ban đầu sẽ có x số bằng k. chọn 1 range giữa các index kia sao cho thêm được nhiều số và bớt đi ít số
Ví dụ: ai, ai+1,...6, 2, 6, aj, aj+1  k = 2
Đoạn 6->6 ở giữa kia có thể tạo được 2 số k và chỉ mất 1 số 2 ở giữa.
Để tính số lượng số k ở trong 1 range ta dùng fenwick tree 0/1 là xong. (các phần tử bằng k thì là 1, khác k là 0 -> query sum range là đếm đc số lượng số = k)
Giả sử map[6] = {0, 2, 3, 7, 15}; Phải chọn 2 index l:r để apply operation vào.
Nếu duyệt 2 vòng loop thì N^2 ko được. => dùng dp.
Dp giống hệt bài max_sum of sub array. Tìm ra sub array nào có max_sum lớn nhất là được.
Với mỗi phần tử có giá trị là 1 và trừ các phần tử = k xen kẽ (fw.query) (-1)
Khởi đầu dp sẽ là operation apply vào chỉ index đó thì sẽ được số lượng số k ban đầu + 1 (là chính số đó)
Rồi bò dần tới các index
dp[i] = max(dp[i-1] + 1 - fw.sum(i-1, i), dp[i]);
dp[i-1] + 1 - fw.sum(i-1, i) nghĩa là từ index i-1 lấy thêm index i và trừ đi số lượng số k ở giữa i-1 và i
Nếu nhỏ hơn dp[i] thì lấy dp[i] cũng hệt như sum sub array lấy tới điểm đó bị âm nên bỏ đi lấy mỗi điểm i
-> Đại khái: giữa 2 số bằng nhau thì lấy toàn bộ các số bằng số đó - các số bằng số k ban đầu + các số = k ngoài khoảng -> lấy max là ra kết quả
*/
