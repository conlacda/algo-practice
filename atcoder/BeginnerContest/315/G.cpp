#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int __int128
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// _int128 in/out
istream& operator>>(istream&in, __int128& num) {
    string s; cin >> s;
    num = 0;
    for (auto v: s) num = num * 10 + (v - '0');
    return in;
}

#ifndef DEBUG
ostream& operator<<(ostream &os, __int128 x) {
    if (x < 0) {
        os << '-';
        x = -x;
    }
    string ans = "";
    while (x != 0) {
        ans += (x%10) + '0';
        x /= 10;
    }
    reverse(ans.begin(), ans.end());
    if ((int) ans.size() == 0) ans = "0";
    os << ans;
    return os;
}
#endif

// Nhanh hơn __gcd(x, y) có sẵn 1 chút
int gcd(int a, int b) {
    if (!a || !b) return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

// floor(a / b)
int divFloor(int a, int b) {
  return a / b - (((a ^ b) < 0 && a % b != 0) ? 1 : 0);
}

// ceil(a / b)
int divCeil(int a, int b) {
  return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

pair<int, int> findSolution(int a, int b, int c = 1) {
    int g = gcd(a, b);
    a /= g; b /= g; c /= g;

    int x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    // a1 chính là gcd(a, b)
    x = x * c; y = y * c; // ax+by=1 -> a*x*c+b*y*c=c
    assert(a * x + b * y == c);
    return make_pair(x, y);  
}

bool hasSolution(int a, int b, int c) {
    if (a == b && a == 0) return c == 0; // 0x+0y = 0 != c != 0
    int g = gcd(a, b);
    if (c % g != 0) return false;
    return true;
}


int N, A, B, C, X;
int cnt(int a, int b, int c) {
    if (!hasSolution(a, b, c)) return 0;
    int x0, y0;
    tie(x0, y0) = findSolution(a, b, c);

    int g = gcd(a, b);
    // Công thức nghiệm: x = x0 + b/g * t; y = y0 - a/g * t với t là 1 số nguyên
    int tmin, tmax;
    int low = 1, high = N;
    tmin = max(divCeil(low-x0, b/g), divCeil(y0-high, a/g));
    tmax = min(divFloor(high - x0, b/g), divFloor(y0-1, a/g));
    if (tmax < tmin) return 0;
    return tmax - tmin + 1;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    // ax + by = c. Đếm xem là bao nhiêu nghiệm là xong
    // Dùng extendgcd để tìm ra 1 nghiệm
    // Hạn chế giới hạn của t
    // Tính ra số nghiệm
    cin >> N >> A >> B >> C >> X;
    int ans = 0;
    for (int i=1;i<=N;i++) {
        ans += cnt(A, B, X - C*i);
    }
    cout << ans;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
What is the pattern from simple input to output.
https://atcoder.jp/contests/abc315/tasks/abc315_g
*/