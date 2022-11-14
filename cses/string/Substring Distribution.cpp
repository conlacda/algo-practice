// https://cses.fi/problemset/task/2110/ 
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

// Copy from: https://cp-algorithms.com/string/suffix-array.html
struct SuffixArray{
    string s; int n;
    vector<int> suffix_array, lcp;
    SuffixArray(string s){
        this->s = s; n = s.size();
        suffix_array = cal_suffix_array(s + '$');
        lcp = cal_lcp();
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
        p.erase(p.begin());
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
template <typename T>
struct FenwickTree { // One-based indexing
    vector <T> bit;
    int N;
    FenwickTree(int n) {
        this->N = n+1;
        bit.assign(n + 1, 0);
    }
    FenwickTree(vector <T> a) : FenwickTree(a.size()) {
        for (int i = 1; i <= a.size(); ++i) {
            add(i, i, a[i-1]);
        }
    }

    void internal_update(int idx, T val) {
        for (int i = idx; i < N; i += (i & (-i))) {
            bit[i] += val;
        }
    }
    // s[l<=i<=r] += val;
    void add(int l, int r, T val) {
        internal_update(l, val);
        internal_update(r + 1, -val);
    }
    T at(int idx) {
        T ans = 0;
        for (int i = idx; i; i -= (i & (-i))) ans += bit[i];
        return ans;
    }
    vector<T> original(){
        vector<T> org;
        for (int i=1;i<N;i++) org.push_back(this->at(i));
        return org;
    }
};
/*
vector<ll> a{1,2,3,4,5,6,7};
FenwickTree<ll> fw(a), fw(n);
fw.add(l, r, val); // thêm vào [l:r] s[i] += val;
fw.original(); // lấy ra toàn bộ mảng
cout << fw.at(i); // giá trị tại index i
*/
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s;
    cin >> s;
    // Dùng suffix array + fenwicktree khi cộng
    SuffixArray suf(s);
    vector<ll> ans(s.size(), 0);
    dbg(ans);
    FenwickTree<ll> fw(ans);
    // xét phần tử đầu tiên
    fw.add(1, (ll) s.size() - suf.suffix_array[0], 1);
    for (int i=0;i<(ll) s.size()-1;i++){
        fw.add(suf.lcp[i]+1, (ll) s.size() - suf.suffix_array[i+1], 1);
    }
    for (auto v: fw.original()){
        cout << v << ' ';
    }
    // dbg(fw.original());
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
// https://cses.fi/problemset/result/4975558/
/*
Ý tưởng thuật toán:
Như ta thấy nếu dùng hash thì sẽ mất O(N^2). Mỗi giá trị độ dài i (i=1->N) thì cần duyệt từ đầu tới cuối để đếm xem có bao nhiêu string khác nhau (N)
Với việc dùng suffix array. Ta thấy với 2 string cạnh nhau trong bảng suffix 
    6*       "" (empty)
0*  5   0    a               -> substr = s.substr(suffix_array[idx]) - idx (left, right) dùng trong binary search
1   0   1    ababba          -> suffix_array + cyclic_substr.size() = s.size() (cột 2 + cột4)
2   2   2    abba
0   4   3    ba
2   1   4    babba
1   3   5    bba
lcp suf idx  cyclic substr
Ví dụ: 
    0   1    ababba
2   2   2    abba
Đoạn này trùng nhau 2 kí tự đầu tiên
-> kí tự từ 3->string size() sẽ là 1 string khác nhau.
Cụ thể tại đây đang xét string abba và nó có phần ab trùng nên string mới tại đây là abb và abba
Khi này ta cần cộng ans[abb.size()]+=1 (a[3]+=1) và ans[abba.size()] +=1 (a[4]+=1)
-> Nếu cộng thường thì độ phức tạp cho phép cộng for vẫn là N và duyệt hết mảng suffix là N -> N^2
Dùng fenwick tree cho việc cộng các phần tử liên tiếp
fw.add(l=3, r=4, val=1); mất logN
-> tổng cả N*logN thao tác
*/