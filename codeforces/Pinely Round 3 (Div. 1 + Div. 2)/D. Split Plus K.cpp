// https://codeforces.com/problemset/problem/1909/D
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

bool isTarget = false;
int cnt = 0;
int N;

void solve(int tc) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    // Nếu có 1 số trong a bằng k thì nếu toàn bộ ko bằng nhau thì ko đc
    // vì nếu a[i] = k thì với mọi target t cuối cùng khác k thì đều ko tạo ra được
    // Ví dụ ai = 3 và k = 3. t buộc phải là 3. Nếu t = 2 < k
    // 3 + 3 = 6 = 2 + 4. 4 + 3 = 7 = 2 + 5. Số tạo ra ngày càng tăng
    // t = 4 > k
    // 3 + 3 = 6 = 4 + 2. 2 + 3 = 5 = 4 + 1. Số tạo ra ngày càng giảm
    // Do đó chỉ cần 1 số = k và 1 số != k là ko bao giờ thỏa mãn
    bool containK = false;
    for (auto v: a) if (v == k) containK = true;
    if (containK) for (auto v: a) {
        if (v != k) {
            cout << -1 << '\n';
            return;
        }
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    /*
    Observe:
    * Với 1 thao tác thì tổng dãy số tăng lên k, và số lượng phần tử tăng 1
    * Các số sẽ được xử lý riêng rẽ và không liên quan tới nhau.
    Gọi t là số mục tiêu. Ta có:
    (ai + kx)/(x+1) = t
    => (ai-k + kx+k)/(x+1) = t
    => (ai-k)/(x+1) = t-k
    => (ai-k)/(t-k) = x+1
    Vế trái có ai biết, k biết, vế phải có x+1 nguyên
    => t-k là ước của ai-k.
    => t-k là ước chung của toàn bộ ai-k với i=1->n
    t chung với index i = 1->n
    k biết trước
    ai là tập a
    x thay đổi
    Để x nhỏ nhất thì t-k phải lớn nhất và chính là UCLN(ai-k)
    */
    int g = a[0] - k;
    for (auto v: a) {
        g = std::gcd(g, v - k);
    }
    if (g == 0) {
        // mọi số trong a đều bằng nhau
        cout << 0 << '\n';
        return;
    }
    // t-k là ước của g
    // Thử toàn bộ ước của g rồi thử xem cái nào cho x nhỏ nhất
    // Kiểm tra cùng tính âm dương
    set<int> sign;
    for (int i=0;i<n;i++) {
        if (a[i] - k == 0) continue;
        if (a[i] - k > 0) sign.insert(1);
        else sign.insert(-1);
    }
    dbg(sign);
    assert((int) sign.size() != 0);
    if ((int) sign.size() == 2) {
        cout << -1 <<'\n';
        return;
    }
    int dau = *sign.begin();
    int ans = INF;
    // t-k mà âm thì toàn bộ ai-k phải âm
    // ngược lại t-k dương thì ai-k phải dương
    g *= dau;
    dbg(g, dau);
    for (auto v: a) dbg((v-k));
    int res = 0;
    for (auto v: a) {
        res += (v - k) / g - 1;
    }
    ans = min(ans, res);
    if (ans < -1) ans = -1;
    // (ai-k)/(t-k) = x+1  - với ai = k thì x lại ra -1??
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cin >> N;
    for (int i=0;i<N;i++)
        solve(i);

    show_exec_time();
}
// F*ck array problem
