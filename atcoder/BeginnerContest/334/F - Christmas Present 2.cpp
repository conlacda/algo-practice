// https://atcoder.jp/contests/abc334/tasks/abc334_f
// F - Christmas Present 2
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const double INF = DBL_MAX; // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Node {
    double val = 0; // giá trị mặc định nên để là 0 // ***
    bool is_null = false;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return Node{min(a.val, b.val)}; // ***
    }

    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

template<typename Node = Node>
class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(vector<Node>& v){ build(v);}
    void build(vector<Node>& v) {
        n = 1; while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
    void set(int index, Node x) {
        index += n - 1;
        dat[index] = x;
        while (index > 0) {
            index = (index - 1) / 2;
            dat[index] = dat[index * 2 + 1] + dat[index * 2 + 2];
        }
    }
    Node query(int l, int r){
        assert(l <= r);
        Node left = Node{.is_null = true}, right = Node{.is_null = true};
        l += n - 1; r += n;
        while (l < r) {
            if ((l & 1) == 0) left = left + dat[l];
            if ((r & 1) == 0) right = dat[r - 1] + right;
            l = l / 2; r = (r - 1) / 2;
        }
        return left + right;
    }
    // Retrieve current state of vector
    vector<Node> original() {
        vector<Node> res;
        for (int i=0;i<n;i++){
            res.push_back(query(i, i));
        }
        return res;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cout << std::fixed << setprecision(15);
    /*
    Observation:
    * Mọi khoảng cách đều có thể tính toán được từ trước
        * Khoảng cách từ santa -> nhà mọi đứa trẻ
        * nhà của đứa trẻ i->j bất kỳ sử dụng prefix sum

    Idea:
    * Push dp từ i push lên k lần. Mỗi lần push thì mất O(K) mà maxK = N => too slow
    * Bản chất là việc chia array thành nhiều phần với mỗi phần có độ dài <=k sao cho sum nhỏ nhất
    Cách suy nghĩ thông thường: dp[index][k] - index và số lượng quà còn lại
    Cách nghĩ khác: chỉ dùng 1 chiều dp[index]
    Nếu ô noel có đủ quà cho 1 lần đi -> ko về nhà giữa chừng là tối ưu nhất - gọi đây là base cost
    K < N -> ô noel buộc phải chọn các index ai để về nhà và giữa 2 index ai liên tục cách nhau tối đa k-1
    Với mỗi lần về thì cost sẽ tăng lên là dist[child_i, noel] + dist[child_i+1, noel] - dist[i,i+1]
    Bài toán quay về: cho arr cost. Chọn các số có index cách nhau tối đa k-1 sao cho tổng là nhỏ nhất
    pull dp, tại i sẽ tính cost dựa vào cost các index trước đó
    */
    int n, k;
    cin >> n >> k;
    pair<int,int> noel;
    cin >> noel.first >> noel.second;
    vector<pair<int,int>> child(n);
    for (int i=0;i<n;i++) {
        cin >> child[i].first >> child[i].second;
    }
    std::function<double(pair<int,int>, pair<int,int>)> dist = [&](pair<int,int> a, pair<int,int> b) {
        int d = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
        return sqrt(d);
    };
    // Tính base cost
    double base_cost = 0;
    base_cost += dist(child[0], noel);
    for (int i=0;i<n-1;i++) base_cost += dist(child[i], child[i+1]);
    base_cost += dist(child[n-1], noel);
    // Tính addition cost cho i =[0..n-2] ko có n-1
    vector<double> add_cost(n, 0);
    for (int i=0;i<n-1;i++) {
        add_cost[i] = dist(child[i], noel) + dist(child[i+1], noel) - dist(child[i], child[i+1]);
    }
    // Dp trên add_cost để lấy ra được cost nhỏ nhất bị thêm vào do phải về nhà refill
    // Cứ làm cách đơn giản dp thông thường => chuyển qua dùng segment tree để giảm thời gian pull dp từ các số trước đó
    vector<double> dp(n, INF);
    vector<Node> sega(n); for (auto&v: sega) v.val = INF;
    SegmentTree seg(sega);
    // initial
    dp[0] = add_cost[0];
    seg.set(0, Node{add_cost[0]});
    // transition
    for (int i=1;i<n;i++) {
        // lấy ra cost nhỏ nhất ở k-1 đoạn trước đó rồi cộng với cost ở chính điểm này
        if (i < k) {// nếu mà trước đó chưa có lần nào về thì cost sẽ chỉ là add_cost[i]
            dp[i] = add_cost[i];
            seg.set(i, Node{add_cost[i]});
            continue;
        }
        auto prev_min_cost = seg.query(i-k, i-1).val;
        dp[i] = prev_min_cost + add_cost[i];
        seg.set(i, {dp[i]});
        // for (int j=1;j<=k;j++) {
        //     if (i >= j) {
        //         dp[i] = min(dp[i], dp[i-j] + add_cost[i]); // optimised here
        //     }
        // }
    }
    // answer
    dbg(add_cost);
    cout << base_cost + dp[n-1];
    show_exec_time();
}
/*
Bài này là 1 bài dp. Nhưng khác nhau về góc nhìn về vấn đề
Bình thường mình dùng dp[index][k] với k là số quà còn lại.
Việc transition cũng rất dễ dàng với index -> index +1 và k -> k-1
Nhưng k ~ n ~ 1e5 thì ko thể chạy được

=> Giảm số chiều của dp đi. Thay vì là k thì giờ mk sẽ cố định k lại. Ví dụ k cố định là
điểm bắt đầu hành trình phát quà mới (sau khi vừa về và tới đó)
Khi này thì số chiều giảm đi 1 do ko cần k nữa.

Góc nhìn của vấn đề này là về việc:
* Đi toàn bộ hành trình rồi quay về theo cách ngắn nhất sẽ là đi phát 1 lượt rồi quay về
* Do phải về nhà nạp quà, mỗi lần nạp quà thì cost sẽ tăng lên 1 lượng là dist[i, noel] (về) + dist[noel, i+1] (đi) - dist[i, i+1] (cost khi đi thẳng đã tính vào base cost)
=> bài toán trở thành cho 1 arr có n phần tử. Mỗi index sẽ có add_cost.
Chọn các index sao cho 2 index liền nhau cách nhau tối đa k và tổng add_cost là min
=> bài toàn hoàn toàn về bài toán dp[index]
Dùng pull dp ta sẽ tính được dp[i] từ min(dp[i-k]...dp[i-1])
min(dp[i-k]...dp[i-1]) tính bình thường với for thì TLE. Do đó dùng SegmentTree với merge() = min(x, y)
*/
