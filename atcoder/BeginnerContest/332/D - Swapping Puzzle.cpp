// Atcoder.abc332.D
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

int inversion(vector<int> a) {
    int res = 0;
    int n = a.size();
    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            if (a[i] > a[j]) res++;
        }
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(n, vector<int>(m));
    for (auto &v: a)
        for (auto &u: v) cin >> u;
    for (auto &v: b)
        for (auto &u: v) cin >> u;

    // chay qua toan bo permutation -> xem no co match khong
    // Neu match thi tinh gia tri
    vector<int> row, col;
    for (int i=0;i<n;i++) row.push_back(i);
    for (int i=0;i<m;i++) col.push_back(i);
    int ans = INF;
    do { 
        do {
            bool match = true;
            for (int i=0;i<n;i++) {
                for (int j=0;j<m;j++) {
                    if (b[row[i]][col[j]] != a[i][j]) match = false;
                }
            }
            if (match) {
                // calculate
                ans = min(ans, inversion(row) + inversion(col));
            }
        } while (std::next_permutation(row.begin(), row.end()));
    } while (std::next_permutation(col.begin(), col.end()));
    cout << ((ans == INF) ? -1 : ans);
    show_exec_time();
}
/*
Cách giải:
Số cột, hàng là 2 vector 1...N và 1...M
Xét tất cả các hoán vị của cột, hàng rồi so sánh xem sau khi di chuyển cột và hàng của b như thế có ra được matrix a ban đầu không (if (b[row[i]][col[j]] != a[i][j]) match = false;)
Nếu match thì thành ra cho mảng {1, 2, 3, 4, 5} và 1 hoán vị {3, 2, 4, 5, 1}.
Cần swap bao nhiêu lần thì mảng hoán vị sẽ thành ra mảng ban đầu
=> Inversion() của vector.
Kết quả sẽ là 2 inversion() cộng với nhau
Nếu không match được thì kết quả là -1
*/
