// https://open.kattis.com/problems/stringmultimatching
// Cho 1 string mẫu, n substring. in ra vị trí của substring trong string mẫu
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
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    vector<string> subs;
    string s;
    int n;
    while (cin >> n){
        getline(cin, s);
        subs.resize(n);
        for (int i=0;i<n;i++){
            getline(cin, subs[i]);
        }
        getline(cin, s);
        SuffixArray suf(s);
        for (auto sub: subs){
            ll lower_bound = suf.lower_bound(sub);
            if (lower_bound == -1){
                cout << " \n";
                continue;
            }
            ll upper_bound = suf.upper_bound(sub);
            vector<ll> ans;
            for (int i=lower_bound;i<upper_bound;i++){
                ans.push_back(suf.suffix_array[i]);
            }
            sort(ans.begin(), ans.end());
            for (auto v: ans){
                cout << v << ' ';
            }
            cout << '\n';
        }
    }

    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
