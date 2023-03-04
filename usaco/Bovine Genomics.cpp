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

// Full doc: https://github.com/conlacda/algo-learning/blob/master/string/cp-algorithm/hash-full.md
template<class Iterable> // chỉ chạy với 64bit.
class Hash{
private:
    vector<ll> pc; // pre-compute 
    ll factor = 137; // **
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0); // **
    // a*x ≡ 1 mod m -> find x - xem thêm tại math-compilation snippet
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    void build(ll length = 200005){ ll p = 1; for (ll i=0;i<length;i++){ pc.push_back(p); p = (p* factor) % mod;} for (auto v: pc) inv.push_back(mod_inv(v));}
    // lấy ra luôn 1 lúc hash ngược và hash xuôi
    pair<ll, ll> hash(Iterable s){
        assert((int) pc.size() >= (int) s.size() && "quên chưa hash.build()??");
        std::function<ll(Iterable)> hash_oneway_toward = [&](Iterable s){
            ll hash_value = 0;
            for (int i=0;i< (int) s.size();i++) {
                int v = s[i] - min_char + 1; assert(v > 0 && "min_char phải nhỏ hơn s[i]");
                hash_value = (hash_value + 1LL*v*pc[i]) % mod;
            }
            if (hash_value < 0) hash_value += mod;
            return hash_value; 
        };
        ll hsh_toward = hash_oneway_toward(s);
        reverse(s.begin(), s.end());
        ll hsh_backward = hash_oneway_toward(s);
        return {hsh_toward, hsh_backward};
    }

    // Precompute O(N) dạng prefix sum để sau tính hash từ l->r với O(1). 
    void load_toward(Iterable s, bool reverse = false){
        vector<ll> *ph;
        Iterable *str;
        if (!reverse) {
            str = &(this->s);
            ph = &prefix_hash;
        } else {
            str = &(this->rs);
            ph = &rprefix_hash;
        }
        *str = s;
        ph->resize(0);
        ph->push_back(0);
        ll hash_value = 0;
        ll start = (!reverse) ? 0 : (ll) s.size() -1;
        ll end = (!reverse) ? (ll) s.size() : -1;
        ll increment = (!reverse) ? 1 : -1;
        for (int i=start;i!=end;i+=increment) {
            int v = str->at(i) - min_char + 1; assert(v > 0 && "min_char phải nhỏ hơn s[i]");
            if (!reverse) hash_value = (hash_value + 1LL*v*pc[i]) %mod;
            else hash_value = (hash_value + 1LL*v*pc[(int) s.size()-1-i]) %mod;
            ph->push_back(hash_value);
        }
    }
    void load_backward(Iterable s){ return load_toward(s, true);} // alias for load_toward(reverse=true);
    void load(Iterable s) {
        assert((int) pc.size() >= (int) s.size() && "quên chưa hash.build()??");
        load_toward(s); load_backward(s);
    }
    // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng lại lấy từ đầu đi tiếp
    ll substr_toward(ll start, ll length){
        assert(length <= (ll) s.size()); // assert(start+length <= (ll) s.size()); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll ans = 0;
        if (start + length <= (ll) s.size()) {
            ans = (prefix_hash[start + length] - prefix_hash[start] + mod) % mod;
            return (ans * inv[start]) % mod;
        }
        ll start2ssize = (prefix_hash[s.size()] - prefix_hash[start] + mod) % mod;
        start2ssize = (start2ssize * inv[start]) % mod;
        ll zero2end = prefix_hash[length + start - (ll) s.size()];
        ans = (start2ssize + zero2end * pc[(ll) s.size() - start]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    ll substr_backward(ll start, ll length){
        assert(length <= (ll) rs.size()); // assert(start+length <= (ll) rs.size()); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll ans = 0;
        start = (ll) rs.size() - 1 - start;
        if (start + length <= (ll) rs.size()) {
            ans = (rprefix_hash[start + length] - rprefix_hash[start] + mod) % mod;
            return (ans * inv[start]) % mod;
        }
        ll start2ssize = (rprefix_hash[(ll) rs.size()] - rprefix_hash[start] + mod) % mod;
        start2ssize = (start2ssize * inv[start]) % mod;
        ll zero2end = rprefix_hash[length + start - (ll) rs.size()];
        ans = (start2ssize + zero2end * pc[(ll) rs.size() - start]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    // Lấy ra hash của s.substr(start, length)
    pair<ll, ll> substr(ll start, ll length) {
        ll end = (start + length >= (ll) s.size()) ? (start + length - (ll) s.size() -1) : (start+length-1);
        return make_pair(substr_toward(start, length), substr_backward(end, length));
    }
    // so sánh 2 substring. 1,0,-1 tương ứng lớn, bằng, nhỏ hơn (chưa kiểm duyệt)
    ll compare_2substrs(ll st1, ll len1, ll st2, ll len2){ // s.substr(st1, len1) <=> s.substr(st1, len2)
        ll size = min(len1, len2);
        ll left = 0, right = size;
        while (left < right - 1){
            ll mid = (left + right) /2;
            if (substr_toward(st1, st1 + mid) != substr_toward(st2, st2 + mid)){
                right = mid-1;
            } else left = mid;
        }
        while (left < size && s[st1 + left] == s[st2 + left]) left++;
        if (left == size) {
            if (len1 > len2) return 1;
            else if (len1 < len2) return -1;
            else return 0;
        }
        if (s[st1 + left] > s[st2 + left]) return 1;
        else if (s[st1 + left] < s[st2 + left]) return -1;
        return 0;
    }
};
struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));
    size_t operator()(pair<ll, ll> p) const noexcept {
        return size_t(p.first) << 32 | p.second; // <<32 chỉ chạy với 64 bit.
    }
};

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
        unordered_map<pair<ll, ll>, bool, IntPairHash> um;        
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