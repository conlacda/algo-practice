// http://www.usaco.org/index.php?page=viewproblem2&cpid=741
#include<bits/stdc++.h>
typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

template<class Iterable> // chỉ chạy với 64bit.
class Hash {
private:
    const ll factor = 263; // số nguyên tố lớn hơn 255 - là full bảng Acsii
    const char min_char = 0x00; // kí tự 0
    vector<ll> inv, pc; // pre-compute
    ll n;
    // a*x ≡ 1 mod m -> find x - xem thêm tại math-compilation snippet
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    int toInt(char x) { // char(127) = 127 nhưng char(128) = -127, ... char(255) = -1 
        int valOfChar = x - min_char + 1;
        int res = (valOfChar <= 0) ? valOfChar + 256 : valOfChar;
        assert(res > 0 && "min_char phải nhỏ hơn s[i]");
        return res;
    }
    int toInt(int x) {
        return x - min_char + 1;
    }
public:
    Iterable s;
    vector<ll> prefix_hash, suffix_hash;
    void build(ll length = 250000){ ll p = 1; for (ll i=0;i<length;i++){ pc.push_back(p); p = (p* factor) % mod;} for (auto v: pc) inv.push_back(mod_inv(v));}
    // Precompute O(N) dạng prefix sum để sau tính hash từ l->r với O(1).     
    void load(Iterable s) {
        assert((int) pc.size() >= (int) s.size() && "quên chưa hash.build()??");
        this->s = s; this->n = (ll) s.size();
        prefix_hash = suffix_hash = {0};
        ll pre = 0, suf = 0;
        for (int i=0;i< (int) s.size();i++) {
            pre = (pre + toInt(s[i]) * pc[i]) % mod;
            suf = (suf + toInt(s[(int) s.size() - i - 1]) * pc[i]) % mod;
            prefix_hash.push_back(pre);
            suffix_hash.push_back(suf);
        }
    }
    // Lấy ra hash của s.substr(start, length)
    ll substr(ll start, ll length) {
        assert(length <= n); // assert(start+length <= n); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll end = (start + length >= n) ? (start + length - n -1) : (start+length-1);
        // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng lại lấy từ đầu đi tiếp
        std::function<int(ll, ll, vector<ll>&)> hashOfSubstr = [&](ll start, ll length, vector<ll>& ps_hash){
            ll ans = 0;
            if (start + length <= n) {
                ans = (ps_hash[start + length] - ps_hash[start] + mod) % mod;
                return (ans * inv[start]) % mod;
            }
            ll start2ssize = (ps_hash[n] - ps_hash[start] + mod) % mod;
            start2ssize = (start2ssize * inv[start]) % mod;
            ll zero2end = ps_hash[length + start - n];
            ans = (start2ssize + zero2end * pc[n - start]) % mod;
            if (ans < 0) ans += mod;
            return ans;
        };
        return (ll) hashOfSubstr(start, length, prefix_hash) << 32 | hashOfSubstr(n - 1 - end, length, suffix_hash);
    }
};
// http://localhost:3000/docs/competitive-programming/string/hash-string
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        ifstream cin("cownomics.in");
        ofstream cout("cownomics.out");
    #endif
/*
Yêu cầu bài toán. 
Tìm ra range [l-r] sao cho đoạn từ l-r của phần trên và phần dưới không trùng nhau
Check lần lượt từ trái qua phải
Tại mỗi index tính xem giá trị tối thiểu tại đó là bao nhiêu
*/
    int n, m;
    cin >> n >> m;
    vector<string> spot(n), nospot(n);
    string spot_string = "", nospot_string = "";
    for (int i=0;i<n;i++) {
        cin >> spot[i];
        spot_string += spot[i];
    }
    for (int i=0;i<n;i++) {
        cin >> nospot[i];
        nospot_string += nospot[i];
    }
    Hash<string> hash;
    hash.build(spot_string.size());
    Hash<string> hspot = hash;
    Hash<string> hnospot = hash;
    hspot.load(spot_string);
    hnospot.load(nospot_string);
    std::function<bool(int, int)> check = [&](int index, int len){
        // Kiểm tra xem index và len này có được không
        unordered_map<ll, bool> um;        
        // Kiểm tra xem đoạn này có được không
        /*Dùng binary search để xem 
        Nếu index to được thì giảm đi 1 nửa*/
        for (int i=0;i<n;i++){
            um[hspot.substr(index + i*m, len)] = true;
        }
        for (int i=0;i<n;i++){
            if (um.find(hnospot.substr(index + i*m, len)) != um.end()){
                return false;
            }
        }
        return true;
    };
    int ans = INT_MAX;
    for (int i=0;i<m;i++){
        // Tìm ra giá trị phù hợp
        int left = 1, right = m-i;
        while (left < right-1){
            int mid = (left + right) /2;
            if (!check(i, mid)){
                left = mid + 1;
            } else right = mid;
        }
        if (check(i, left)){
            ans = min(ans, left);
        } else if (check(i, right)){
            ans = min(ans, right);
        }
    }
    cout << ans;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Problem: http://www.usaco.org/index.php?page=viewproblem2&cpid=741
Bài này cần tìm ra range [l:r] sao cho các đoạn từ [l:r] của các string có spot và
các string không có spot không có string nào trùng nhau
Ví dụ:
3 8
AATCCCAT
ACTTGCAA
GGTCGCAA
ACTCCCAG
ACTCGCAT
ACTTCCAT

Xét bất kỳ 1 đoạn string độ dài 3 nào thì 3 string trên và 3 string dưới luôn trùng nhau
Ví dụ: l=0, r=2 -> trùng ACT
       l=1, r=3 -> trùng CTT
       l=2, r=4 -> trùng TCC
       l=3, r=5 -> trùng CGC
       ...
Với độ dài = 4 thì đoạn l=1, r = 4 là không trùng nhau -> kết quả là 4
( [ATCC,CTTG,GTCG] x [CTCC, CTCG, CTTC] = {}  x là giao nhau/intersect)
Ban đầu mình tính với mỗi index tìm ra độ dài tối thiểu cần để nó ko intersect là bao nhiêu
Tăng dần length lên, đạt thì dừng và cập nhật ans = min(ans, result)
Nhưng với cách này với mỗi index O(N) sẽ có length = 1->N là N^2 phép kiểm tra
-> Tối ưu:
Dễ nhận thấy nếu với (index, len) thỏa mãn điều kiện thì (index, s.size()) cũng thỏa mãn điều kiện
Nghĩa là nếu index =1 và độ dài trên kia là 4 thỏa mãn thì index =1 và độ dài >4 cũng thỏa mãn
-> Dùng binary search để tìm. left = 1, right = m-i. Khi này kiểm tra mid có thỏa mãn hay không để điều chỉnh lại left, right  

Nói ngắn gọn:
Với mỗi index (O(N))ta dùng binary search để tìm ra len thỏa mãn (O(logN))
-> độ phức tạp O(NlogN)
*/
