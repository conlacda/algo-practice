// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/C - đăng nhập mới xem được
// Cho 1 string
// n các giá trị a, b thể hiện s[a:b]
// sắp xếp các cặp đó theo thứ tự tăng dần của giá trị substr
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
 
template<typename T>
struct RMQ {
    int n = 0;
    vector<T> values;
    vector<vector<int>> range_low;
    bool maximum_mode = false;
    RMQ(const vector<T> &_values = {}) {
        if (!_values.empty())
            build(_values);
    }

    static int largest_bit(int x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    // Note: when `values[a] == values[b]`, returns b.
    int better_index(int a, int b) const {
        return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
        // return (maximum_mode ? values[b] <= values[a] : values[a] <= values[b]) ? a : b; // when values[a] == values[b] returns a
    }

    void build(const vector<T> &_values) {
        values = _values;
        n = int(values.size());
        int levels = largest_bit(n) + 1;
        range_low.resize(levels);

        for (int k = 0; k < levels; k++)
            range_low[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_low[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
    }

    // Note: breaks ties by choosing the largest index.
    int query_index(int a, int b) const {
        b++;
        assert(0 <= a && a < b && b <= n);
        int level = largest_bit(b - a);
        return better_index(range_low[level][a], range_low[level][b - (1 << level)]);
    }

    T query_value(int a, int b) const {
        return values[query_index(a, b)];
    }
};
/*
Source: nealwu - RQM - https://codeforces.com/contest/1454/submission/128555767
vector<int> a{3, 2, 10};
RMQ<int> rmq_min, rmq_max;
rmq_min.build(a); // tạo ra rmq_min 
*/
// Copy from: https://cp-algorithms.com/string/suffix-array.html
struct SuffixArray{
    string s; int n;
    vector<int> suffix_array, lcp;
    RMQ<int> rmq_lcp; // just for common_prefix_of_substrs()
    unordered_map<int, int> m;    
    SuffixArray(string s){
        this->s = s; n = s.size();
        suffix_array = cal_suffix_array(s + char(*min_element(s.begin(), s.end())-1));
        lcp = cal_lcp();
        rmq_lcp.build(lcp);
        build_lower_bound();
    }
    vector<int> cal_suffix_array(string s){
        int n = s.size();
        const int alphabet = 256;

        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1];
        for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]]) classes++;
            c[p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
                if (cur != prev) classes++;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        p.erase(max_element(p.begin(), p.end())); // dấu $ - cũng là phần tử có index lớn nhất trong suffix_array (6* trong ví dụ dưới)
        return p;
    }
    vector<int> cal_lcp(){
        vector<int> rank(n, 0);
        for (int i = 0; i < n; i++) rank.at(suffix_array[i]) = i;

        int k = 0;
        vector<int> lcp(n-1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = suffix_array[rank[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
        return lcp; 
    }
    // Tính tổng số substr có trong s - https://cses.fi/problemset/result/4386205/ - https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/submission/167497445
    ll number_of_substr(){
        ll ans = n - suffix_array[0];
        for (int i=1;i<n;i++){
            ans += (n - suffix_array[i]) - lcp[i-1];
        }
        return ans;
    }

    ll lower_bound(string sub){
        // Tìm lower_bound của sub trong mảng suffix các string. suffix_array[lower_bound(sub)] -> index của sub trong string
        // -1 nếu không tìm thấy
        ll left = 0, right = n-1;
        while (left < right) {
            ll mid = (left + right) /2;
            string _s = s.substr(suffix_array[mid], sub.size());
            if (sub <= _s) right = mid;
            else left = mid +1;
        }
        if (left < n && s.substr(suffix_array[left], sub.size()) < sub) left ++;
        if (s.substr(suffix_array[left], sub.size()) != sub) return -1;
        return left;
    }
    void build_lower_bound(){
        for (int i=0;i<suffix_array.size();i++){
            m[suffix_array[i]] = i;
        }
    }
    // Tìm lower_bound cho sub = s.substr(start, size)
    ll lower_bound(ll start, ll size){
        // Xét trên suffix_array thì m[start] là vị trí của nó. Cố gắng dịch nó về phía index thấp hơn sẽ ra lower_bound
        ll index = m[start];
        if (index == 0) return index;
        ll bound = index -1;
        // left --- mid --- right-|bound
        ll left = 0, right = bound;
        while (left < right){
            ll mid = (left + right) /2;
            if (rmq_lcp.query_value(mid, bound) >= size){
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        // Do lcp[i] là phần chung của i vs i+1.
        if (lcp[right] >= size)
            return right;
        return right+1;
    }
    ll upper_bound(string sub) {
        // Tương tự lower_bound. Lưu ý lower_bound = upper_bound = n khi không tìm thấy sub
        ll left = 0, right = n-1;
        while (left < right){
            ll mid = (left + right) /2;
            if (s.substr(suffix_array[mid], sub.size()) <= sub){
                left = mid+1;
            } else right = mid;
        }
        if (left < n && s.substr(suffix_array[left], sub.size()) <= sub) left++;
        return left;
    }
    // đếm xem substring xuất hiện trong string bao nhiêu lần. Trong prefix đã sắp xếp tìm phần tử nhỏ nhất và lớn nhất bằng sub - https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/submission/168931121
    ll occurrence(string sub){
        ll low = lower_bound(sub);
        if (low == -1) return 0;
        ll up = upper_bound(sub);
        return up - low;
    }
    // trả về substring - muốn tìm index của substr thì dùng hàm find_substr()
    string longest_substr() {
        ll signal_index = -1;
        for (int i=0;i<s.size();i++) {
            if (s[i] == '|') {
                signal_index = i;
                break; 
            }
        }
        assert(signal_index != -1);
        ll max = 0; string ans = "";
        for (int i=0;i<lcp.size();i++){
            if (lcp[i] >= max && (suffix_array[i] - signal_index) * (suffix_array[i+1] - signal_index) < 0) {
                if (max == lcp[i]) {
                    if (ans > s.substr(suffix_array[i], lcp[i])) {
                       ans = s.substr(suffix_array[i], lcp[i]); 
                    }
                } else {
                    max = lcp[i];
                    ans = s.substr(suffix_array[i], lcp[i]);
                }
            }
        }
        return ans;
    }
};
/*
SuffixArray suf(s);
cout << suf.suffix_array;
cout << suf.lcp;
cout << suf.number_of_substr();
cout << suf.find_substr("abc"); // index of substring in s
cout << suf.occurrence("abc"); // how many times "abc" appears in s
    6*       "" (empty)
0*  5   0    a               -> substr = s.substr(suffix_array[idx]) - idx (left, right) dùng trong binary search
1   0   1    ababba          -> suffix_array + cyclic_substr.size() = s.size() (cột 2 + cột4)
2   2   2    abba
0   4   3    ba
2   1   4    babba
1   3   5    bba
lcp suf idx  cyclic substr
Dấu * nghĩa là nó mang tính biểu tượng (hình dung), sẽ không xuất hiện trong mảng thực tế
Tìm longest substr của s1, s2
string s = s1 + '|' + s2
SuffixArray suf(s);
cout << suf.longest_substr(); // trả về substring chung dài nhất của s1, s2
cout << suf.common_prefix_of_substrs(index1, index2); // "ababc" -> id1,id2 = 0,2 -> "ababc" & "abc" -> phần chung = 2 = "ab"
*/
struct D {
    ll u, v, stt;
    bool operator<(D b){
        // đoạn này bận trước gây ra RE ***
        // return this->stt < b.stt || this->v - this->u < b.v - b.u || this->u < b.u || this->v  < b.v;
        return th
        if (this->stt != b.stt){
            return this->stt < b.stt;
        }
        if (this->v - this->u != b.v - b.u){
            return this->v - this->u < b.v - b.u;
        }
        if (this->u != b.u){
            return this->u < b.u;
        }
        if (this->v != b.v){
            return this->v  < b.v;
        }
        return false; // lưu ý đoạn này true là có đổi chỗ. Nếu a=b mà đổi chỗ thì nó sẽ đổi chỗ vô hạn gây ra lỗi
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s;
    cin >> s;
    SuffixArray suf(s);
    int n; cin >> n;
    vector<D> data;
    
    for (int i=0;i<n;i++){
        ll u, v; cin >> u>> v; u--; v--;
        data.push_back({u, v, suf.lower_bound(u, v-u+1)});
    }
    sort(data.begin(), data.end());
    for (D v: data){
        cout << v.u +1 <<' ' << v.v+1<<'\n';
    }
    cerr << "OK Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}