// https://atcoder.jp/contests/abc370/tasks/abc370_e
// DP optimization
// https://atcoder.jp/contests/abc370/tasks/abc370_e
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

const int maxN = 1000003;
vector<ll> factorial, factorial_inv; // giai thừa
unsigned int normalize(int x) { x %= mod; if (x < 0) x += mod; return x; } // there is a weird bug if put this func into mint

template<unsigned int mod = mod>
struct Mint {
    friend std::ostream& operator<<(std::ostream& os, const Mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, Mint &s) { int k; cin >> k; os >> k; s.x = normalize(k); return os; }
    unsigned int x;
    Mint() : x(0) {}
    Mint(ll _x) { // auto convert ll to Mint.
        x = normalize(_x);
    }
   
    unsigned int val() { return x; }

    Mint& operator += (const Mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator -= (const Mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator *= (const Mint &a) {
        x = (unsigned long long)x * a.x % mod;
        return *this;
    }
    Mint& operator /= (const Mint &a) {
        return *this *= a.inv();
    }

    Mint operator + (const Mint &a) const {
        return Mint(*this) += a;
    }
    Mint operator - (const Mint &a) const {
        return Mint(*this) -= a;
    }
    Mint operator * (const Mint &a) const {
        return Mint(*this) *= a;
    }
    Mint operator / (const Mint &a) const {
        return Mint(*this) /= a;
    }
 
    bool operator == (const Mint &a) const {
        return x == a.x;
    }
    bool operator != (const Mint &a) const {
        return x != a.x;
    }
    bool operator < (const Mint &a) const {
        return x < a.x;
    }
};
using mint = Mint<mod>;

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Dùng dp
    dp[index] chứa số lượng cách và tổng của giá trị cuối cùng
    dp[index][sum] = way
    */
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto&v: a) cin >> v;

    // Cách naive này không hoạt động do độ phức tạp O(N^2)
    // // Initial
    // vector<map<int, mint>> dp(n);
    // dp[0][a[0]] = 1;
    // // transition
    // for (int i=1;i<n;i++) {
    //     // giữ lại số mới
    //     for (auto&v: dp[i-1])
    //         if (v.first != k)
    //             dp[i][a[i]] += v.second;
    //     // giữ lại số cũ
    //     for (auto&v: dp[i-1])
    //         dp[i][a[i] + v.first] += v.second;
    // }
    // // answer
    // mint ans = 0;
    // for (auto&v: dp[n-1]) {
    //     if (v.first!= k) ans+=v.second;
    // }
    // cout << ans;

    mint sum = 1; // tổng số cách chọn hiện tại
    unordered_map<int, mint> m; // số cách chọn ở index hiện tại
    // chọn số đầu tiên
    m[a[0]] = 1;
    int delta = 0; // số lệch giá trị qua từng index
    for (int i=1;i<n;i++) {
        // x là số lượng số mà ngoặc kết thúc không bằng k
        // khi này ta có thể đặt a[i] vào 1 ngoặc mới
        // ví dụ [1, 2, 5] với k = 3 thì [1, 2] + 5 ta sẽ ko đặt (5) thành ngoặc mới với (1, 2) đằng trước được mà chỉ đặt được (5) với (2) ở đằng trước
        // sum = 2, m[3] = 1 -> x = 1
        mint x = sum - m[k - delta]; // số lượng số ko có đoạn cuối là k
        
        // dp[i][a[i] + v.first] += v.second;
        // để ý tại đây ta thấy ta có 1 vòng lặp để tăng toàn bộ element
        // trong map lên a[i]. Thay vì thế ta sẽ giữ 1 delta
        // Xét ví dụ:
        // a[0] = 2 -> map chứa {2}
        // a[1] = 3 -> map chứa {5, 3}
        // a[2] = 4 -> map chứa {9, 7, 4}
        // giờ ta dùng 1 index
        // a[0] = 2 -> map chứa {2}
        // a[1] = 3 -> map chứa {2, 0} với delta = 3
        // a[2] = 4 -> map chứa {2, 0, -3} với delta = 7
        // khi này thay vì lặp qua toàn bộ map thì ta sẽ chỉ append thêm 1 phần tử
        // rồi tăng delta lên a[i] là xong
        delta += a[i];

        // tách số hiện tại ra thành 1 () riêng
        m[a[i] - delta] += x;
        // sum = sum + x.
        // sum vế phải sẽ là việc nối a[i] vào các ngoặc trước đó. Có bao nhiêu ngoặc trước đó thì thêm a[i] vào là xong -> 1:1 -> sum cách
        // x là số lượng cách để đặt a[i] làm 1 ngoặc mới riêng
        sum += x;
    }
    cout << (sum - m[k-delta]).val();

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
