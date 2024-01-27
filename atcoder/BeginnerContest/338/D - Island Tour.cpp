// https://atcoder.jp/contests/abc338/tasks/abc338_d
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

// Range update - point query
template <typename T>
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
    /*
    Dùng segment tree.
    1 đoạn a->b sẽ có 2 cách đi là xuôi/ngược kim đồng hồ
    Chọn cách ngắn hơn và cập nhật toàn bộ điểm bên trong đó thêm diff
    tức là nếu cầu tại đó gãy thì sẽ làm tăng cost lên diff đơn vị
    khi này xét từng cây cầu bị gãy và sẽ biết cost tại đâu tăng lên nhiều hơn

    Dễ hiểu hơn thông qua ví dụ:
         1 
       8   2
     7       3
       6   4
         5
    Xét n = 8.
    Ta đi từ 2->5 thì sẽ có 2 cách đi là trái từ 2->5 và phải 2->1->5
    Nếu từ 2->8 từ trái là 2->1->8 và phải là 2->8
    Sao cho trái <= phải.
    Trong trường hợp ko gãy cầu thì luôn đi theo đường ngắn hơn là đường trái.
    Khi này ta sẽ tính cost trong trường hợp 1 trong các cầu tại trái bị gãy.
    Cost sẽ tăng lên right - left.
    Dùng fenwicktree với range update để tăng toàn bộ các cây cầu nằm trong khoảng trái lên diff = cost_right - cost_left
    Sau khi hết tour sẽ có fw.at(i) là cost nếu cây cầu thứ i bị gãy.
    Với từng cây cầu bị gãy ta có chi phí bị đội lên so với chi phí ban đầu.
    Lặp qua 1 vòng là biết cây cầu nào gãy sẽ có chi phí đi lại ít nhất.

    Cây cầu thứ i sẽ được định nghĩa là cạnh nối đỉnh i và i+1.
    Ví dụ đi từ 2->5 có left = 5-2=3 và right = 8 + 2 - 5 = 5. Nếu cây cầu 2->3, 3->4, 4->5 gãy thì cost tăng lên 2
    vì phải đi vòng
    fw.add(2, 4, diff); // node 2->5 thì sẽ gồm cây cầu 2, 3, 4 (cạnh được chuyển về node thấp hơn - kĩ thuật tương tự ở trong HLD hay các bài về tree khác)
    */
    int n, len;
    cin >> n >> len;
    vector<int> tour(len);
    for (auto& v: tour) {
        cin >> v;
        v--;
    }
    dbg(tour);
    int cost = 0;
    FenwickTree<ll> fw(vector<int>(n, 0));
    for (int i=0;i<len-1;i++) {
        int start = tour[i];
        int end = tour[i+1];
        if (start > end) swap(start, end);
        int left = end - start; // đi trực tiếp từ start->end
        int right = n + start - end; // đi end -> 1 -> start
        int diff = abs(left - right);
        // Cầu từ u->u+1 sẽ được fenwicktree giữ tại điểm(index) u
        if (left < right) {
            cost += left;
            // chọn đi left - nếu hỏng cầu trong khoảng [start->end) thì cost tăng lên diff
            fw.add(start, end - 1, diff);
        } else {
            cost += right;
            // chọn đi right - nếu hỏng cầu trong khoảng [0->start) và [end->n] thì cost tăng lên diff
            if (start > 1)
                fw.add(0, start-1, diff);
            if (end < n-1)
                fw.add(end, n-1, diff);
        }
    }
    int finalCost = INF;
    for (int i=0;i<n;i++) {
        finalCost = min(cost + fw.at(i), finalCost);
    }
    cout << finalCost;
    show_exec_time();
}

