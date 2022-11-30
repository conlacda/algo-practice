// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/suffix-arrays/practice-problems/algorithm/sonya-and-string-shifts-code-monk-triesuffix-structures/
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
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
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
        for (int i = 0; i < n; i++)
            rank[suffix_array[i]] = i;

        int k = 0;
        vector<int> lcp(n-1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = suffix_array[rank[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
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
    // check if string s contains sub? - đưa ra vị trí của sub trong s (index) - https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/submission/167503987
    ll find_substr(string sub){
        ll left = 0, right = n-1;
        // suffix_array được sắp xếp nên muốn tìm 1 sub thì chỉ cần binary search.
        while (left < right) {
            ll mid = (left + right) /2;
            string _s = s.substr(suffix_array[mid], sub.size());
            if (_s < sub) left = mid+1;
            else right = mid;
        }
        if (s.substr(suffix_array[right], sub.size()) == sub){
            dbg(right);
            return suffix_array[right]; 
        }
        return -1;
    }
    // đếm xem substring xuất hiện trong string bao nhiêu lần. Trong prefix đã sắp xếp tìm phần tử nhỏ nhất và lớn nhất bằng sub - https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/submission/167527106
    ll occurrence(string sub){
        ll lower_bound, upper_bound;
        ll left = 0, right = n-1;
        // Get lower_bound of substring on subfix_array strings - tìm lower_bound, upper_bound https://www.geeksforgeeks.org/implementing-upper_bound-and-lower_bound-in-c/
        while (left < right) {
            ll mid = left + (right - left) /2;
            string _s = s.substr(suffix_array[mid], sub.size());
            if (sub <= _s) right = mid;
            else left = mid + 1;
        }
        if (left < n && s.substr(suffix_array[left], sub.size()) < sub) left++;
        lower_bound = left;
        // Get upper_bound
        left = 0, right = n-1;
        while (left < right){
            ll mid = left + (right - left) /2;
            if (sub >= s.substr(suffix_array[mid], sub.size())){
                left = mid+1;
            } else right = mid;
        }
        if (left < n && s.substr(suffix_array[left], sub.size()) <= sub) left++;
        upper_bound = left;
        return upper_bound - lower_bound;
    }
    void longest_common_prefix_of_substrs(ll a, ll b){ // s1 = s.substr(a); s2 = s.substr(b);
        // TODO - dùng segment tree hoặc RMQ để query trên lcp.
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
*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    string s; cin >> s;
    int t;
    cin >> t;
    SuffixArray suf(s);
    dbg(suf.suffix_array);
    vector<int> m(s.size());
    for (int i=0;i<suf.suffix_array.size();i++){
        m[suf.suffix_array[i]] = i;
    }
    dbg(m);
    vector<int> ans(s.size());
    int _min = m[0], ind = 0;
    ans[0] = 0;
    for (int i=1;i<s.size();i++){
        if (m[i] < _min) {
            _min = m[i];
            ind = i;
        }
        ans[i] = ind;
    }
    dbg(ans);
    for (int i=0;i<t;i++) {
        int q; cin >> q;
        cout << ans[q] <<'\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
