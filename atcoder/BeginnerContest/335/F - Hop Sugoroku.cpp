// https://atcoder.jp/contests/abc335/tasks/abc335_f
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
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

const int maxN = 1000003;
template<unsigned int mod = mod>
struct Mint {
    friend std::ostream& operator<<(std::ostream& os, const Mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, Mint &s) { return os >> s.x;}
    unsigned int x;
 
    Mint() : x(0) {}
    Mint(ll _x) { // auto convert ll to Mint.
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }
 
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

    Mint power(ll pw) const {
        Mint res = 1;
        Mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    // Chứng minh xem tại CPH - Modular inverse
    Mint inv() const {
        assert(x != 0);
        unsigned int t = x;
        unsigned int res = 1;
        while(t != 1) {
            unsigned int z = mod / t;
            res = (unsigned long long)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
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
using mint = Mint<>;

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    /*
    Naive approach:
    dùng push dp. dp[i+Ai*x] += dp[i]
    Thay vì tới mỗi index cập nhật luôn giá trị vào dp thì dùng 1 mảng lưu lại giá trị cần cập nhật
    dp[i] push lên dp[i+1] nhưng ko push lên dp[i+2] mà giữ trạng thái tại dp[i+1]
    */
    // Naive
    // vector<int> dp(n, 0);
    // dp[0] = 1;
    // for (int i=0;i<n;i++) {
    //     int x = 1;
    //     while (i + a[i] * x < n) {
    //         dp[i + a[i] * x] += dp[i];
    //         dp[i + a[i] * x] %= mod;
    //         x++;
    //     }
    // }
    // int ans = 0;
    // for (int i=0;i<n;i++) {
    //     ans += dp[i];
    //     ans %= mod;
    // }
    // Better
    int block = sqrt(n);
    // int block = (int) sqrt(n);
    vector<mint> dp(n, 0);
    dp[0] = 1;
    vector store(n, vector<mint>(block, (mint)0));
    for (int index=0;index<n;index++) {
        if (a[index] < block) {
            if (a[index] + index < n) {
                // Tính 1 nhịp rồi để sau tính tiếp
                dp[a[index] + index] += dp[index];
                // Tại index i + a[i] có thể push lên index + a[i] tiếp theo dp[i] đơn vị
                // map[index][step] = dp[i];
                store[index + a[index]][a[index]] += dp[index];
            }
        } else {
            // Tính luôn
            int x = 1;
            while (index + a[index] * x < n) {
                dp[index + a[index] * x] += dp[index];
                x++;
            }
        }
        // Xử lý store được lưu tại index i và push nó thêm 1 step nữa
        // tại index có thể push lên index + a[i] lên giá trị dp
        for (int step=0;step<block;step++) {
            mint value = store[index][step];
            if (index + step < n) {
                dp[index + step] += value;
                store[index + step][step] += value;
            }
        }
    }
    mint ans = 0;
    for (int i=0;i<n;i++) {
        ans += dp[i];
    }
    cout << ans;
    show_exec_time();
}
/*
Bài này nếu sử dụng dp thông thường thì sẽ TLE nếu có toàn bộ số 1
Độ phức tạp là N^2.
Tối ưu:
Với những số lớn hơn sqrt(N) thì ta dùng dp như bình thường.
    Số lần nhảy sẽ tối đa là sqrt(N). N = 25, nhảy mỗi lần >= 5 bước -> số lần nhảy <= 5
Ngược lại với những trường hợp a[i] < sqrt thì nếu nhảy sẽ tốn O(N)
Do đó thay vì nhảy luôn thì ta sẽ chỉ nhảy đúng 1 lần.
Rồi lưu lại tại vị trí đó step + giá trị dp.
Ban đầu dp[i] push dp[i+1], dp[i+2]
thì thành dp[i] push dp[i+1] rồi để ở dp[i+1] rằng có thể nhảy step = 1 và tăng lên giá trị dp[i]
Khi này tối đa tại mỗi index ta lưu sqrt cặp (step, value) thể hiện rằng tại index đó ta có thể nhảy step bước và push giá trị value vào index mới đó.
Duyệt tới index k thì duyệt qua toàn bộ step rồi push tại đây đi 1 lần và lại lưu (step, value) tại index mới
Độ phức tạp ở đây cũng là O(N căn N)

Tổng độ phức tạp là O(N căn N)
*/
