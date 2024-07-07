// https://atcoder.jp/contests/abc361/tasks/abc361_f
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

// maxN < 1e8 (0.45s for build). if maxN >= 1e8 used primeFactorize() instead
const int maxN = 100; 
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
};

int power(int a, int b) {
    __int128 res = 1;
    __int128 x = a;
    while (b > 0) {
        if (res > INF || x > INF) return INF;
        if (b & 1) res = res * x;
        x = x * x;
        b >>= 1;
    }
    if (res > INF) res = INF;
    return res;
}

int sqrt64(int k) {
    auto s = (int) std::sqrt((long double) k) + 2; // 1 là được, để chắc chắn để là 2
    while (s * s > k) s--;
    return s;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    Prime P;
    /*
    x = a^b thì chỉ xét tới a không có dạng a^b
    để check a không có dạng a^b thì lấy căn của nó
    vì b chỉ có từ 2->60 là cùng
    
    b = 2->59
    với mọi b chẵn thì có thể chuyển thành X^2 nên bỏ qua b chẵn
    -> b là số nguyên tố là được
    khi này a^b với b nguyên tố < 60
    b = 2 đếm được số lượng
    a phải ko có dạng a^b vì nếu có dạng đó thì nó suy thành a^(b1*b2) lặp lại
    => a^b với a ko có dạng (a^b) và b là số nguyên tố

    Ý tưởng khác: - implement dưới đây là theo cách này
    Có tối đa 10^6 phần tử nếu ko xét tới b = 2
    Nếu lưu tất cả vào 1 set.
    Xét riêng b = 2 thì có luôn số lượng là căn của N
    hợp 2 phần này lại thì bỏ qua những phần tử trong set là pow(a, 2) là xong
    */
    set<int> S;
    vector<int> ps = {};
    for (int i=3;i<60;i++)
        if (P.isPrime(i))
            ps.push_back(i);

    std::function<bool(int)> isPowOf2 = [&](int x) {
        auto s = (int) std::sqrt((long double) x) + 2; // 1 là được, để chắc chắn để là 2
        while (s * s > x) s--;
        return s * s == x;
    };
    int curIndex = (int) ps.size() -1;
    for (int num=2;num<1e6;num++) {
        if (isPowOf2(num)) continue;
        while (curIndex >= 0 && power(num, ps[curIndex]) > n) {
            curIndex--;
        }
        if (curIndex < 0) break;
        for (int i=0;i<=curIndex;i++) {
            S.insert(power(num, ps[i]));
        }
    }
    cout << (int) S.size() + sqrt64(n);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
