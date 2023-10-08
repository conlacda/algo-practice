// https://codeforces.com/contest/1349/problem/A
// A. Orac and LCM - 1600
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

int divCeil(int a, int b) {
    return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

const int maxN = 200001; // maxN < 1e8 - lưu ý local chạy max 1e7, OJ max 1e8. 1e9 super slow
class Prime {
private:
    // hàm sàng nguyên tố, có thể tách ra độc lập nếu phần này rườm ra quá
    void build(int n){
        dbg("Nhớ điều chỉnh maxN = căn(N ở đề bài)");
        is_prime.set(); // set to full 1
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; i++)
            if (is_prime[i])
                for (int j = i * i; j <= n; j += i) is_prime[j] = false;
        for (int i=0;i<n;i++) if (is_prime[i]) primes.push_back(i);
    }
    // Calculate a^b
    int power(int a, int b) {
        int res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
public:
    int n;
    bitset<maxN> is_prime;
    vector<int> primes;
    Prime(int n = maxN) {
        this->n = n;
        build(n);
    }
    bool isPrime(int k) {
        assert(k < n && "Out of range maxN");
        return is_prime[k];
    }
    map<int, int> split(int u) {
        map<int, int> pf; // prime & factor. 12 = 2*2* 3 -> pf[2] = 2, pf[3] = 1
        for (auto p: primes) {
            if (p * p > u) break;
            if (u < maxN && is_prime[u]) break;
            while (u % p == 0) {
                pf[p]++;
                u /= p;
            }
        }
        if (u != 1) pf[u]++;
        return pf;
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
    Tách các số này thành các số nguyên tố.
    Bản chất hàm LCM() là lấy ra exp lớn nhất.
    Bản chất GCD() lấy ra số exp nhỏ nhất
    => Lấy ra 2 số mũ nhỏ nhất và lấy max của nó là ra
    */
    Prime p;
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) {
        cin >> v;
    }
    dbg(a);
    /*
    Tách các số thành số nguyên tố rồi đếm số lần xuất hiện + số mũ của số đó
    Ví dụ: số 2 xuất hiện 3 lần, N = 5 => có 2 số số 2 ko xuất hiện -> số 2 ko xuất hiện trong kết quả
    số 2 ko xuất hiện 1 lần => số mũ nhỏ nhất vì số có số mũ nhỏ nhất kết hợp với số ko có số mũ -> số có số mũ nhỏ nhất => lấy GCD thì số mũ này được giữ lại
    số 2 luôn xuất hiện => max(2 số mũ nhỏ nhất) => vì 2 số này kết hợp với nhau sẽ cho ra số có số mũ nhỏ nhất, lấy GCD cùng các số có số mũ cao thì số mũ nhỏ nhất này lấy thành kết quả
    */
    map<int, int> remain;
    for (auto prime: p.primes) remain[prime] = n;
    map<int, pair<int,int>> _min;
    for (auto prime: p.primes) _min[prime] = {INF, INF};
    for (auto v: a) {
        auto df = p.split(v);
        for (auto [factor, exp]: df) {
            remain[factor]--;
            _min[factor].first = min(_min[factor].first, exp);
            if (_min[factor].first < _min[factor].second) {
                swap(_min[factor].first, _min[factor].second);
            }
        }
    }
    int ans = 1;
    for (auto p: p.primes) {
        if (remain[p] >= 2) continue;
        if (remain[p] == 1) {
            ans *= pow(p, _min[p].second);
        } else if (remain[p] == 0) {
            int exp = max(_min[p].first, _min[p].second);
            ans *= pow(p, exp);
        }
    }
    cout << ans;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/
