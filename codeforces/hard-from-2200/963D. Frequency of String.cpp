#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
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

    int better_index(int a, int b) const {
        return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
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

struct SuffixArray{
    string s; int n;
    vector<int> suffix_array, lcp;
    RMQ<int> rmq_min_suf, rmq_max_suf;
    RMQ<int> rmq_lcp; // just for common_prefix_of_substrs()
    unordered_map<ll, ll> m; // start tại s -> index sau khi sắp xếp // lowb2
    SuffixArray(string s){
        this->s = s; n = s.size();
        suffix_array = cal_suffix_array(s + char(*min_element(s.begin(), s.end())-1)); // gốc là $ - bản chất là kí tự nhỏ nhất khi so sánh cyclic substring
        lcp = cal_lcp();
        rmq_min_suf.build(suffix_array);
        rmq_max_suf.maximum_mode = true;
        rmq_max_suf.build(suffix_array);
        rmq_lcp.build(lcp); // just for common_prefix_of_substrs()
        // preprare for lower_bound(start, size) // lowb2
        for (int i=0;i<suffix_array.size();i++) {
            m[suffix_array[i]] = i;
        }
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
    ll lower_bound(string any_sub){
        ll left = 0, right = n-1;
        while (left < right) {
            ll mid = (left + right) /2;
            string _s = s.substr(suffix_array[mid], any_sub.size());
            if (any_sub <= _s) right = mid;
            else left = mid +1;
        }
        if (left < n && s.substr(suffix_array[left], any_sub.size()) < any_sub) left ++;
        if (s.substr(suffix_array[left], any_sub.size()) != any_sub) return -1;
        return left;
    }
   
    ll upper_bound(string sub) {
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
    string s;
    cin >> s;
    SuffixArray suf(s);
    ll q; cin >> q;
    while (q--) {
        ll k; string sub;
        cin >> k >> sub;
        ll lower_bound = suf.lower_bound(sub);
        ll upper_bound = suf.upper_bound(sub);
        if (lower_bound == -1 || upper_bound - lower_bound < k) {
            cout << -1 <<'\n';
            continue;
        }
        vector<ll> a;
        for (int i=lower_bound;i<upper_bound;i++) {
            a.push_back(suf.suffix_array[i]);
        }
        sort(a.begin(), a.end());
        dbg(a);
        if (k == 1) {
            cout << sub.size() <<'\n'; continue;
        }
        ll ans = LLONG_MAX;
        for (int i=0;i<=(int) a.size() -k;i++) {
            ans = min(ans, a[i+k-1] + (ll) sub.size() - a[i]);
        }
        cout << ans <<'\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Bài này khá là vô liêm sỉ vì chả cần cách làm nào phức tạp,
đơn giản là dùng suffix array lấy ra toàn bộ vị trí xuất hiện trong a (NlogN)
sau đó sort cái đống đó rồi duyệt qua đống đã sort với độ phức tạp O(N)
Thế mà ko hiểu sao nó vẫn chạy rất nhanh. Có vẻ như phần testcase hơi yếu
ko có trường hợp 10^5 chữ a.
*/