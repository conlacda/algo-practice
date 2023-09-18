// https://atcoder.jp/contests/arc165/tasks/arc165_c
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = 2147483647; // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    /*
    Binary search cho X
    left = min toàn bộ cạnh
    right = INF
    đánh dấu cho cạnh 0 là khác màu, 1 là trùng màu
    duyệt DFS đánh dấu màu cho nó, đánh dấu màu fail/ok
    */
    int n, m;
    cin >> n >> m;// n dinh, m canh
    vector<vector<pair<int,int>>> g(n);
    for (int i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    /*
    Dùng binary search để tìm X với X = [1->INF]
    Dựng 1 graph mà trong đó các cạnh nhỏ hơn X -> lớn hơn X thì đặt màu vào cạnh đó sao cũng được
    Duyệt DFS() để đánh dấu màu trên đồ thị này -> màu ko bị conflict là ok -> dạng 0/1
    Từ 1 đỉnh -> lấy ra 2 cạnh nhỏ nhất -> tổng 2 cạnh đó < X là fail -> ngược lại là được
    Submission tham khảo: https://atcoder.jp/contests/arc165/submissions/45671880
    Đoạn mình tắc: đoạn 1 từ đỉnh, lấy ra 2 đỉnh nhỏ nhất
        Ban đầu mình duyệt nguyên trên đồ thị ban đầu nên phải lấy ra 1 cấu trúc dữ liệu lưu trữ cạnh nào cần xét, cạnh nào không cần xét => chính đoạn này làm vấn đề trở nên rất lằng nhằng
        Nhưng tại đây graph mới được construct và những cạnh trong này đều cần xét tới -> dễ dàng lấy ra được 2 cạnh nhỏ nhất.
    */
    // dbg(g);
    std::function<bool(int)> isGood = [&](int x){
        // Dựng 1 đồ thị mới
        vector<vector<pair<int,int>>> gr(n);
        for (int i=0;i<n;i++){
            for (auto [v, w]: g[i]) {
                if (w < x) {
                    gr[i].push_back({v, w});
                }
            }
        }
        // Duyệt màu cho đồ thị
        vector<int> color(n, -1);
        vector<bool> vis(n, false);
        bool ableToPaint = true;
        std::function<void(int, int)> paintColor = [&](int u, int c){
            if (vis[u]) return;
            vis[u] = true;
            color[u] = c;
            for (auto [v, _]: gr[u]) {
                if (vis[v]) {
                    if (color[v] != 1-c) {
                        ableToPaint = false;
                        return;
                    }
                } else {
                    paintColor(v, 1-c);
                }
            }
        };
        for (int i=0;i<n;i++) {
            if (!vis[i]) paintColor(i, 0);
            if (!ableToPaint) return false;
        }
        // Check đồ dài 2 đỉnh cùng màu
        for (int i=0;i<n;i++) {
            if (gr[i].size() < 2) continue;
            int min1 = INF, min2 = INF;
            for (auto [v, w]: gr[i]) {
                min2 = min(min2, w);
                if (min1 > min2) swap(min1, min2);
            }
            assert(min1 != INF && min2 != INF);
            if (min1 + min2 < x) return false;
        }
        return true;
    };
    int left = 1, right = INF;
    while (left < right -1) {
        int mid = (left + right) /2;
        if (isGood(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    if (isGood(right)) {
        cout << right;
    } else {
        assert(isGood(left));
        cout << left;
    }
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??

Phần mà tại đây mk đã ko nghĩ ra là tạo graph mới từ graph cũ.
Vì việc lo lắng rằng tạo graph sẽ tốn quá nhiều thời gian
Nhưng thực ra với binarysearch thì số lần tạo graph mới chỉ là log1e9 ~ 30 lần
Tạo graph mới xong thì graph đó là graph 0/1 thuần, ko phải xử lý bất kỳ thao tác nào thêm
*/
