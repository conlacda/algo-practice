#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

struct SuffixArray {
private:
    const char min_char = 0x00; // kí tự 0 - gốc là $
    const int alphabet = 256;

    template<typename T> struct RMQ { int n = 0; vector<T> values; vector<vector<int>> range_low; bool maximum_mode = false; RMQ(const vector<T> &_values = {}) { if (!_values.empty()) build(_values); }  static int largest_bit(int x) { return x == 0 ? -1 : 31 - __builtin_clz(x); }   int better_index(int a, int b) const { return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;  }  void build(const vector<T> &_values) { values = _values; n = (int)values.size(); int levels = largest_bit(n) + 1; range_low.resize(levels);  for (int k = 0; k < levels; k++) range_low[k].resize(n - (1 << k) + 1);  for (int i = 0; i < n; i++) range_low[0][i] = i;  for (int k = 1; k < levels; k++) for (int i = 0; i <= n - (1 << k); i++) range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]); }   int query_index(int a, int b) const { b++; assert(0 <= a && a < b && b <= n); int level = largest_bit(b - a); return better_index(range_low[level][a], range_low[level][b - (1 << level)]); }  T query_value(int a, int b) const { return values[query_index(a, b)]; } };
    vector<int> cal_suffix_array(string s){
        int n = s.size(); vector<int> p(n), c(n), cnt(max(alphabet, n), 0); for (int i = 0; i < n; i++) cnt[s[i]]++; for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1]; for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i; c[p[0]] = 0; int classes = 1; for (int i = 1; i < n; i++) { if (s[p[i]] != s[p[i-1]]) classes++; c[p[i]] = classes - 1;} vector<int> pn(n), cn(n); for (int h = 0; (1 << h) < n; ++h) { for (int i = 0; i < n; i++) { pn[i] = p[i] - (1 << h); if (pn[i] < 0) pn[i] += n;} fill(cnt.begin(), cnt.begin() + classes, 0); for (int i = 0; i < n; i++) cnt[c[pn[i]]]++; for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1]; for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i]; cn[p[0]] = 0; classes = 1; for (int i = 1; i < n; i++) { pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]}; pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]}; if (cur != prev) classes++; cn[p[i]] = classes - 1; } c.swap(cn);}
        p.erase(max_element(p.begin(), p.end())); // dấu $ - cũng là phần tử có index lớn nhất trong suffix_array (6* trong ví dụ dưới)
        return p;
    }
    vector<int> cal_lcp(){ vector<int> rank(n, 0), lcp(n-1, 0); for (int i = 0; i < n; i++) rank.at(suffix_array[i]) = i; int k = 0; for (int i = 0; i < n; i++) { if (rank[i] == n - 1) {k = 0; continue;} int j = suffix_array[rank[i] + 1]; while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++; lcp[rank[i]] = k; if (k) k--; } return lcp;  }
public:
    string s; int n;
    vector<int> suffix_array, lcp;
    RMQ<int> rmq_lcp; // just for common_prefix_of_substrs()
    vector<int> suf_to_indx; // index k có s.substr(k) ở vị trí bao nhiêu trong suffix_array.
    SuffixArray(){}
    void build(string s){
        this->s = s; n = s.size();
        suffix_array = cal_suffix_array(s + min_char);
        lcp = cal_lcp();
        rmq_lcp.build(lcp); // just for common_prefix_of_substrs()
        suf_to_indx.resize(n);
        for (int i=0;i<(int) suffix_array.size();i++) suf_to_indx[suffix_array[i]] = i;
    }

    int common_prefix_of_substrs(int a, int b) {
        if (a == b) return s.size() - a;
        int idxa = suf_to_indx[a];
        int idxb = suf_to_indx[b];
        if (idxa > idxb) swap(idxa, idxb);
        idxb--; // idxb-- là vì mảng lcp nhỏ hơn mảng suffix 1 phần tử và lcp[i] là lcp(suf_arr[i], suf_arr[i+1])
        return rmq_lcp.query_value(idxa, idxb);
    }
    int compare_2substrs(int a, int b, int sz = INF) {
        std::function<int(ll, ll)> getAns = [&](char x, char y){
            if (x > y) return 1;
            if (x < y) return -1;
            return 0;
        };
        int cp = common_prefix_of_substrs(a, b);
        if (cp >= sz) return 0;
        return getAns(this->s[a+cp], s[b+cp]);

    }
};
// Doc: http://localhost:3000/docs/competitive-programming/string/suffix-array
SuffixArray suf;

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    string S = s + s + t + t;
    suf.build(S);
    vector<int> a;
    for (int i=0;i<n;i++) {
        a.push_back(i);
        a.push_back(2*n+i);
    }
    sort(a.begin(), a.end(), [&](int id1, int id2) {
        int cmp = suf.compare_2substrs(id1, id2, n);
        if (cmp == 0) return id1 < id2;
        if (cmp < 0) return true;
        return false;
    });
    int ans = 0;
    int g = n;
    for (int i=0;i<(int) a.size();i++) {
        if (a[i] < n) ans += g;
        else g--;
    }
    cout << ans;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
What is the pattern from simple input to output?

Bài này nó hỏi là cho các string dạng vòng của s, t. Sắp xếp nó lại rồi xem với mỗi index i thì s.substr(i, n) nhỏ hơn bao nhiêu số t.substr(j, n)
Hỏi dạng vòng: -> S = s + s + t + t. Dạng vòng thì cứ build với s + s. 2 string thì s + s + t + t.
Suffixarray sẽ sắp xếp các string lại với nhau.
Mình chỉ xét tới các string nằm ở s thứ 1 và t thứ 1 tức là index nằm trong 2 khoảng 0->n-1 và 2n->3n-1
Lấy mảng a chứa 2 khoảng đó. Sắp xếp mảng a theo điều kiện S.substr(i, n) > S.substr(j, n) thì đảo chỗ i, j.
Mảng sau khi sắp xếp sẽ gồm các index mà i < j thì S.substr(i, n) < S.substr(j, n)
Duyệt mảng rồi với mỗi i nằm trong khoảng của s thứ 1 thì cộng với số index thuộc khoảng t thứ 1 đằng sau nó là xong

Thời gian chạy trên cái atcoder ko ổn định, nó yêu cầu 2s. Chương trình chạy từ 1.75->2.3s nên 1 source code submit nhiều lần lúc thì AC, lúc thì TLE
*/
