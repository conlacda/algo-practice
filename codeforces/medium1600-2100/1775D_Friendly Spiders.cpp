// https://codeforces.com/contest/1775/problem/D
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

int maxN = 300005; // maxN < 1e8
class Prime {
    vector<bool> sieve_prime(int n = maxN){
        vector<bool> is_prime(n+1, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; i++)
            if (is_prime[i])
                for (int j = i * i; j <= n; j += i) is_prime[j] = false;
        return is_prime;
    }
public:
    int n;
    vector<bool> is_prime;
    vector<int> primes;
    Prime(int n = maxN) {
        this->n = n;
        is_prime = sieve_prime(n);
        for (int i=0;i<n;i++) if (is_prime[i]) primes.push_back(i);
    }
    bool isPrime(int k) {
        assert(k < n && "Out of range maxN");
        return is_prime[k];
    }
    vector<int> split(int u) {
        vector<int> s;
        // unordered_map<int, int> pf; // prime & factor. 12 = 2*2* 3 -> pf[2] = 2, pf[3] = 1
        for (auto p: primes) {
            if (is_prime[u]) break;
            if (p * p > u) break;
            if (u % p == 0) {
                s.push_back(p);
                while (u % p == 0) {
                    // pf[p]++;
                    u /= p;
                }
            }
        }
        if (u != 1) {
            s.push_back(u);
            // pf[u]++;
        }
        return s;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i=0;i<n;i++) cin >> a[i];
    int start, end;
    cin >> start >> end; start--; end--;
    // Duyệt BFS là xong
    vector<vector<int>> _map(300005, vector<int>{});
    Prime P;
    for (int i=0;i<(int)a.size();i++) {
        auto s = P.split(a[i]);
        for (auto prime: s) _map[prime].push_back(i);
    }
    vector<int> layer(n, INF);
    vector<int> parent(n);
    unordered_map<int, bool> solvedPrime;
    // BFS
    queue<int> Q;
    Q.push(start);
    layer[start] = 1; parent[start] = -1;
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        auto ps = P.split(a[p]);
        for (auto prime: ps) {
            if (solvedPrime[prime]) continue;
            for (auto index: _map[prime]) {
                if (layer[index] != INF) continue; // xử lý rồi thì bỏ qua
                layer[index] = layer[p] + 1;
                parent[index] = p;
                Q.push(index);
            }
            solvedPrime[prime] = true;
        }
    }
    if (layer[end] == INF) {
        cout << -1<< '\n';
        return 0;
    }
    cout << layer[end] <<'\n';
    vector<int> trace;
    while (end != -1) {
        trace.push_back(end);
        end = parent[end];
    }
    reverse(trace.begin(), trace.end());
    for (auto v: trace) cout << v+1 << ' ';
    show_exec_time();
}
/*
Từ số start, tách ra thành các số nguyên tố.
Từ số nguyên tố đó dựa vào map đã dựng sẵn (map[prime] = {ai, aj, ak,...}) với ai chia hết cho prime
Từ các số này lại tiếp tục lan ra các số khác
Optimise:
Các số prime đã tính rồi thì đánh dấu nó lại để ko tính lại nó lần nữa
Hàm tách số nguyên tố ngắt luôn khi số đang xét là số nguyên tố, ví dụ số 299993 là số nguyên tố, nếu 1 dãy toàn là số này mà đưa vào tách số nguyên tố thì nó sẽ rất chậm. Thay vì thế check luôn ngay tại vòng lặp qua mỗi số nguyên tố nhỏ.
Các số lan ra cũng được đánh dấu đã xử lý để nó bỏ qua ko xử lý lần 2
*/
