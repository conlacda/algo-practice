// https://timus.online/problem.aspx?space=1&num=1393
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

<hash-string-without-changes>

struct SuffixArray{
private:
    const char min_char = 0x00; // kí tự 0 - gốc là $
    const int alphabet = 256;
    vector<int> cal_suffix_array(string s){
        int n = s.size(); vector<int> p(n), c(n), cnt(max(alphabet, n), 0); for (int i = 0; i < n; i++) cnt[s[i]]++; for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1]; for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i; c[p[0]] = 0; int classes = 1; for (int i = 1; i < n; i++) { if (s[p[i]] != s[p[i-1]]) classes++; c[p[i]] = classes - 1;} vector<int> pn(n), cn(n); for (int h = 0; (1 << h) < n; ++h) { for (int i = 0; i < n; i++) { pn[i] = p[i] - (1 << h); if (pn[i] < 0) pn[i] += n;} fill(cnt.begin(), cnt.begin() + classes, 0); for (int i = 0; i < n; i++) cnt[c[pn[i]]]++; for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1]; for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i]; cn[p[0]] = 0; classes = 1; for (int i = 1; i < n; i++) { pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]}; pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]}; if (cur != prev) classes++; cn[p[i]] = classes - 1; } c.swap(cn);}
        // p.erase(max_element(p.begin(), p.end())); // dấu $ - cũng là phần tử có index lớn nhất trong suffix_array (6* trong ví dụ dưới)
        return p;
    }
public:
    string s; int n;
    vector<int> suffix_array;
    SuffixArray(string s){
        this->s = s; n = s.size();
        suffix_array = cal_suffix_array(s);
    }
};
// Doc: http://localhost:3000/docs/competitive-programming/string/suffix-array
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(3);
    int n;
    cin >> n;
    string s;
    cin >> s;
    SuffixArray suf(s);
    ll ans = 0;
    dbg(suf.suffix_array);
    Hash<string> hash;
    hash.build(s.size());
    hash.load(s);
    for (int i=0;i<n-1;i++) {
        ans += hash.common_prefix(suf.suffix_array[i], suf.suffix_array[i+1]);
    }
    cout << double(ans) / (n-1);
}
