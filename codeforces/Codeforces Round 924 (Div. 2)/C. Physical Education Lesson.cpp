// https://codeforces.com/contest/1928/problem/C
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

int divCeil(int a, int b) {
    return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

const int maxN = 1e6; // maxN < 1e8 - thỉnh thoảng allocate ko được. 1e9 super slow
class Prime {
private:
    void build(){
        cerr << "Nhớ điều chỉnh maxN = √N ở đề bài\n";
        is_prime.set(); // set to full 1
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i < maxN; i++)
            if (is_prime[i])
                for (int j = i * i; j < maxN; j += i) is_prime[j] = false;
        for (int i=0;i<maxN;i++) if (is_prime[i]) primes.push_back(i);
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
    Prime() {
        build();
    }
    bool isPrime(int k) {
        assert(k < maxN && "Out of range maxN");
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
    // Lấy ra danh sách các divisor của k
    vector<int> divisors(int k, bool _sort = false) {
        vector<int> res;
        int i=1;
        while (i * i < k) {
            if (k % i == 0) {
                res.push_back(i); res.push_back(k/i);
            }
            i++;
        }
        if (i * i == k) res.push_back(i);
        if (_sort) sort(res.begin(), res.end());
        return res;
    }
};
Prime P;

void solve() {
    int n, x;
    cin >> n >> x;
    /*
    Ta có 2 trường hợp:
    * Trường hợp 1:
        Sau khi đi ck lần chu kỳ thì tới số của người đó là x
        mỗi chu kỳ là 2k-2 phần tử, đi quá thêm x là ra số người đó.
        Toàn bộ độ dài là n
        => Công thức: n = (2k-2)ck + x với k >= x (k = x thì người đó ở đỉnh. vd 1 2 3 2 1 thì 3 là đỉnh)
    * Trường hợp 2:
        Sau khi đi ck lần chu kỳ và đi qua nửa trên ta sẽ quay qua nửa dưới và gặp người đó
        Lưu ý rằng tại nửa bên kia của chu kỳ thì x != k và x != 1 do k là đỉnh được xét tại trường hợp trên
            còn x = 1 là điểm bắt đầu của chu kỳ trong trường hợp 1
        => Công thức: n = (2k-2)ck + k + (k- x) . (2k-2)ck là các chu kỳ chẵn. k là qua 1 nửa bên trái của chu kỳ. (k-x) là số bước để từ đỉnh k -> x. vd 1234321. k là 4 -> muốn tới 2 tại nửa kia của chu kỳ ta cần 4-2 bước
                    =>n = (2k-2)ck + 2k -2 + 2-x
                      n = (2k-2)ck' + (2-x) với k > x và x > 1 (k = x là đỉnh xét tại bên trên)
    số lượng số k thỏa mãn 2 phương trình
    */
    int ans = 0;
    // 10 = (2k-2)ck + x
    int kck = n - x;
    // Tách kck thành 1 số chẵn * 1 số bất kỳ
    // giữ 1 số 2 lại và tính số ước của số còn lại
    if (kck % 2 == 0) {
        auto divisor = P.divisors(kck);
        // số lượng divisor >= 2x-2 và chẵn
        for (auto d: divisor) {
            if (d >= 2*x-2 && d % 2 == 0) ans++;
        }
    }
    dbg(ans);
    kck = n - (2-x);
    if (kck > 0 && kck % 2 == 0 && x > 1) {
        auto divisor = P.divisors(kck);
        for (auto d: divisor) {
            if (d > 2*x-2 && d % 2 == 0) ans++;
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    while (n--) solve();

    show_exec_time();
}
