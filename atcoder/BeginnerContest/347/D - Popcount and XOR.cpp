// https://atcoder.jp/contests/abc347/tasks/abc347_d
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#include "random.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

vector<int> toBaseN(int n, int base, int fixed_len = 1) {
    if (n == 0) return vector<int>(fixed_len, 0);
    vector<int> ans;
    while (n > 0) {
        ans.push_back(n % base);
        n= n/base;  
    }
    while ((int) ans.size() < fixed_len) ans.push_back(0);
    reverse(ans.begin(), ans.end());
    return ans;
}

int toDecimal(vector<int> s, int base) {
    __int128 ans = 0, power = 1;
    for (int i=(int)s.size()-1;i>=0;i--) {
        if (ans > INF || power > INF) {
            assert(false);
            return INF; // tràn ll gây ra lỗi
        }
        ans += s[i] * power;
        power *= base;
    }
    assert(ans <= INF && "Overflow?? number is bigger than INF");
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    1^1=0^0=0
    1^0=1
    Số C = A^B với bit 1 -> sinh ra 1 lần 1
    -> bit 0 sinh ra 0 hoặc 2 bit 1
    -> Dựa vào tính chẵn lẻ của bit để yes, no
    -> dựa vào bit 0 để điều chỉnh số lượng bit
    C có c0 bit 0 và c1 bit 1
    A có a bit 1, a0 bit 0
    B    b        b0
    a, b cho sẵn
    -> a + b cùng tính chẵn lẻ với c1
    -> a + b >= c1
    */
    int a, b, C;
    // a = RAND.Int(0, 59);
    // b = RAND.Int(0, 59);
    // C = RAND.Int(1, 1e9);
    // dbg(a, b, C);
    cin >> a >> b >> C;
    int c = __builtin_popcountll(C);
    if ((a + b - c) % 2 != 0 || a + b < c) {
        cout << -1;
        return 0;
    }
    dbg(a, b, c);
    int r = (a+b-c)/2;
    int ra = a - r;
    int rb = b - r;
    if (ra < 0 || rb < 0) {
        cout << -1;
        return 0;
    }
    dbg(r, ra, rb);
    dbg(c);
    vector<int> ans1(60, 0), ans2(60, 0);
    vector<int> base2C = toBaseN(C, 2, 60);
    for (int i=0;i<60;i++) {
        if (base2C[i] == 1) {
            if (ra > 0) {
                ans1[i] = 1;
                ra--;
            } else if (rb > 0) {
                ans2[i] = 1;
                rb--;
            } else
                assert(false);
        } else {
            if (r > 0) {
                ans1[i] = 1;
                ans2[i] = 1;
                r--;
            }
        }
    }
    if (ra != 0 || rb != 0 || r != 0) {
        cout << -1;
        return 0;
    }
    int A = toDecimal(ans1, 2);
    int B = toDecimal(ans2, 2);
    assert((A^B) == C);
    assert(__builtin_popcountll(A) == a);
    assert(__builtin_popcountll(B) == b);
    cout << toDecimal(ans1, 2) << ' ' << toDecimal(ans2, 2);
    show_exec_time();
}