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

struct PrefixSum {
public:
    int n, m;
    vector<vector<int>> a;
    vector<vector<int>> pref;
    PrefixSum() {}
    PrefixSum(vector<vector<int>>& a) {
        build(a);
    }
    void build(vector<vector<int>>& a) {
        // Init
        this->a = a;
        this->n = (int) a.size();
        this->m = (int) a[0].size();
        pref = vector<vector<int>>(n, vector<int>(m, 0));
        // calculate prefix for row by row
        vector<vector<int>> row(n, vector<int>(m, 0));
        for (int i=0;i<n;i++) {
            int s = 0;
            for (int j=0;j<m;j++) {
                s += a[i][j];
                row[i][j] = s;
            }
        }
        // calculate prefix for 2D
        for (int c=0;c<n;c++) {
            int s = 0;
            for (int r=0;r<n;r++) {
                s += row[r][c];
                pref[r][c] = s;
            }
        }
    }
    int cal(int a, int b, int c, int d) {
        // assert(c >= a && d >= b);
        if (c <a  || d < b) return (int) 0;
        if (a == 0 && b == 0) return pref[c][d];
        if (a == 0) return pref[c][d] - pref[c][b-1];
        if (b == 0) return pref[c][d] - pref[a-1][d];
        return pref[c][d] + pref[a-1][b-1] - pref[c][b-1] - pref[a-1][d];
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<string> g(n);
    for (auto &v: g) cin >> v;
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (g[i][j] == 'B') a[i][j] = 1;
        }
    }
    // 1 query tinh mat N
    // Dung prefix_sum de tinh
    // vector<vector<int>> pref(n, vector<int>(n));
    // Tinh prefix sum cho phan 2D -> hinh nay se bi tach thanh 9 phan khac nhau
    PrefixSum p;
    p.build(a);
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int ans = 0;
        dbg(a, b, c, d);
        int upa = (a/n+1)*n;
        int upb = (b/n+1)*n;
        int downc = c/n*n;
        int downd = d/n*n;
        ans += p.cal(a%n, b%n, n-1, n-1);
        ans += p.cal(0, b%n, n-1, n-1) * ((downc - upa) / n);
        ans += p.cal(0, b%n, c%n, n-1);
        ans += p.cal(0, 0, c%n, n-1) * ((downd - upb) /n);
        ans += p.cal(a%n, 0, n-1, n-1) * ((downd - upb) / n);
        ans += p.cal(0, 0, n-1, n-1) * ((downd - upb) /n) * ((downc - upa) /n);
        ans += p.cal(a%n, 0, n-1, d%n);
        ans += p.cal(0, 0, n-1, d%n) * ((downc - upa) /n);
        ans += p.cal(0, 0, c%n, d%n);
        cout << ans << '\n';
    }
    show_exec_time();
}
/*
Bài này cho 4 điểm a, b, c, d thì sẽ chia ra được thành 9 phần
Phần trung tâm sẽ bao gồm các khối nguyên vẹn.
Còn xung quanh trái phải trên dưới có tổng là 8 miếng.
Lần lượt cộng các khối đó vào thì ta được tổng của khối ban đầu.
Mỗi khối nhỏ sẽ là 1 khối nằm trọn trong 1 khối ban đầu -> dễ dàng lấy prefix sum 2D
để tính được từng khối con đó.
1 số mảng sẽ là tập nhiều khối con giống nhau ghép lại -> tính 1 khối con rồi nhân theo
số lần là được.
Bài này vẽ ra 1 khối to đùng rồi vẽ vào trong 1 số khối nguyên vẹn rồi các khối rườm rà
cũng sẽ lấy được hết tạo độ. Diễn giải bằng lời thì có thể hơi khó hiểu.
*/
