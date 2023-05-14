// https://codeforces.com/problemset/problem/825/F
// https://codeforces.com/contest/825/submission/205800755
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct CompressString {
private:
    vector<vector<int>> p;
    vector<int> prefix_function(string s) {
        int n = (int) s.size();
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i-1];
            while (j > 0 && s[i] != s[j]) j = pi[j-1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    };
public:
    string s;
    int n;
    CompressString(string s) {
        this->n = (int) s.size();
        p.resize(n);
        for (int i=0;i<n;i++) p[i] = prefix_function(s.substr(i));
    }
    // {độ dài subtr, số lần substr đó xuất hiện}. "abcabc" => {3, 2}. 3 = "abc"
    pair<int,int> minLen(int start, int sz) {
        int k = sz - p[start].at(sz - 1);
        if (sz % k == 0) return make_pair(k, sz/k);
        return make_pair(sz, 1);
    }
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s;
    cin >> s;
    int n = (int) s.size();
    vector<int> minLen(n, n+1);
    CompressString cp(s);
    minLen[0] = 2;
    // dung pull dp de tinh toan gia tri hien tai
    for (int i=1;i<n;i++) {
        for (int j=0;j<=i;j++) {
            auto pii = cp.minLen(j, i-j+1);
            int p = pii.first + to_string(pii.second).size();
            if (j == 0) {
                minLen[i] = min(minLen[i], p);
            } else {
                minLen[i] = min(minLen[i], minLen[j-1] + p);
            }
        }
    }
    cout << minLen[n-1];
    show_exec_time();
}
