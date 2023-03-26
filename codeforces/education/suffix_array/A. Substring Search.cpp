// https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/problem/A
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
        suffix_array = cal_suffix_array(s + char(*min_element(s.begin(), s.end())-1)); // gốc là $ - bản chất là kí tự nhỏ nhất khi so sánh cyclic substring
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

    ll lower_bound(string sub){
        // Tìm lower_bound của sub trong mảng suffix các string. suffix_array[lower_bound(sub)] -> index của sub trong string
        // -1 nếu không tìm thấy. O(NlogN). logN - binary search. N cho so sánh 2 string
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
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s;
    cin >> s;
    int n;
    cin >> n;
    SuffixArray suf(s);
    for (int i=0;i<n;i++){
        string sub; cin >> sub;
        if (suf.lower_bound(sub) != -1){
            cout << "Yes\n";
        } else cout << "No\n";
    }
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
