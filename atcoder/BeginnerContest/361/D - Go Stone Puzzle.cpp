// https://atcoder.jp/contests/abc361/tasks/abc361_d
// [Atcoder|Codeforces].abcxxx.F
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    s1 += "..";
    s2 += "..";
    if (s1 == s2) {
        cout << 0;
        return 0;
    }
    // N tại đây rất nhỏ chỉ 14
    // Dùng search vô hạn có thể giải ra
    // dùng 1 graph để kết nối các đỉnh lại với nhau
    // tìm đường đi ngắn nhất từ cái của mk tới cái điểm kia
    unordered_map<string, int> m;
    queue<string> Q;
    Q.push(s1);
    std::function<vector<string>(string)> getNeighbors = [&](string s) {
        // Lấy ra điểm có 2 dấu .
        // Bắt đầu move 2 dấu đó tới những điểm khác để tạo ra string mới
        int index = 0;
        int n = s.size();
        while (s[index] != '.') index++;
        assert(s[index] == '.');
        vector<string> ans;
        for (int i=0;i<n-1;i++) {
            if (s[i] != '.' && s[i+1] != '.') {
                string ss = s;
                swap(ss[i], ss[index]);
                swap(ss[i+1], ss[index+1]);
                ans.push_back(ss);
            }
        }
        return ans;
    };
    while (!Q.empty()) {
        auto s = Q.front();
        Q.pop();
        // Lấy ra tất cả hàng xóm của nó
        // Nếu mà string hiện tại + 1 có cost < hàng xóm thì thêm vào Q
        // Ngược lại thì thôi
        // Hoặc nếu hàng xóm chưa có dữ liệu thì cũng thêm vào Q
        for (auto ss: getNeighbors(s)) {
            if (m.find(ss) == m.end()) {
                Q.push(ss);
                m[ss] = m[s] + 1;
            } else {
                if (m[s] + 1 < m[ss]) {
                    m[ss] = m[s] + 1;
                    Q.push(ss);
                }
            }
        }
    }
    // In ra map[s2]
    if (m[s2] == 0) cout << -1;
    else cout << m[s2];

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
