// https://codeforces.com/contest/1499/problem/D
#include<bits/stdc++.h>

typedef long long ll; // ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

const int maxN = (int) 2e7 + 5;// maxN < 1e8 - lưu ý local chạy max 1e7, OJ max 1e8. 1e9 super slow
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
public:
    int n;
    bitset<maxN> is_prime;
    vector<int> primes;
    Prime(int _n = maxN) {
        this->n = _n-1;
        build(n);
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
    vector<int> divisors(int k) {
        vector<int> res;
        int i=1;
        while (i * i < k) {
            if (k % i == 0) {
                res.push_back(i); res.push_back(k/i);
            }
            i++;
        }
        if (i * i == k) res.push_back(i);
        return res;
    }

};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    Prime p;
    int n;
    cin >> n;
    while (n--) {
        int c, d, x;
        cin >> c >> d >> x;
        /*
        Duyệt mọi số nhỏ hơn x. Chia hết bởi x có thể làm gcd.
        c.lcm - d.gcd = x;
        Ta thấy vế trái chia hết cho gcd => x % gcd = 0
        Duyệt qua từng gcd rồi tính ra được lcm
        => với mỗi (lcm, gcd) thì có bao nhiêu cặp số thỏa mãn
        x.y = lcm * gcd
        -> x.y = gcd * k1 * k2 * gcd
        k1 * gcd = x
        k2 * gcd = y
        Lấy lcd/gcd^2 là ra k1*k2 -> số lượng ước của (k1*k2) là số lượng
        */
        // lấy ra toàn bộ divisor để làm gcd
        int ans = 0;
        for (auto gcd: p.divisors(x)) {
            ll right = x * 1LL + 1LL * d * gcd;
            if (right % c != 0) continue;
            ll lcm = right /c;
            if (lcm % gcd != 0) continue;
            // Từ lcm, gcd lấy ra được bao nhiêu cặp số thỏa mãn
            // a * b = lcm * gcd => a*b/(gcd^2) = lcm/gcd
            // a' * b' = lcm/gcd;
            int a_times_b = lcm / gcd;
            // có bao nhiêu cặp a'*b' coprime thỏa mãn -> số divisor của (lcm/gcd)
            // https://www.geeksforgeeks.org/given-gcd-g-lcm-l-find-number-possible-pairs-b/
            // ans += 1 << (int) p.split(a_times_b).size(); // đoạn này cần tối ưu
            ans += 1 << p.prime_divisor_num(a_times_b);
            // 17598
            // tính toán trước toàn bộ số lượng
        }
        cout << ans << '\n';     
    }

    show_exec_time();
}
