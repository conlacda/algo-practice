/* https://codeforces.com/problemset/problem/1765/N
N. Number Reduction
You are given a positive integer x.

You can apply the following operation to the number: remove one occurrence of any digit in such a way that the resulting number does not contain any leading zeroes and is still a positive integer. For example, 10142 can be converted to 1142, 1042, 1012 or 1014 (note that 0142 is not a valid outcome); 10 can be converted to 1 (but not to 0 since it is not positive).

Your task is to find the minimum positive integer that you can obtain from x if you can apply the aforementioned operation exactly k times.

Input
The first line contains a single integer t (1≤t≤105) — the number of test cases.

The first line of each test case contains a single integer x (1≤x<10500000).

The second line contains a single integer k (0≤k<|x|), where |x| is the length of the number x.

The sum of |x| over all test cases does not exceed 5⋅105.

Output
For each test case, print one integer — the minimum positive number that you can obtain from x if you can apply the operation exactly k times.

Example:
5
10000
4
1337
0
987654321
6
66837494128
5
7808652
3
OUT:
1
1337
321
344128
7052
*/
#include <bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

template <typename T> struct RMQ {
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
        return (maximum_mode ? values[b] <= values[a] : values[a] <= values[b])
                   ? a
                   : b;
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
                range_low[k][i] = better_index(
                    range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
    }

    // Note: breaks ties by choosing the largest index.
    int query_index(int a, int b) const {
        b++;
        assert(0 <= a && a < b && b <= n);
        int level = largest_bit(b - a);
        return better_index(range_low[level][a],
                            range_low[level][b - (1 << level)]);
    }

    T query_value(int a, int b) const { return values[query_index(a, b)]; }
};
/*
cout << rmq.query_value(index1, index2); // return min/max_value of range
cout << rmq.query_index(index1, index2); // return min/max_index of range
*/
void solve() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    /*
    Tìm ra vị trí số nhỏ nhất trong dãy cho số đầu tiên
    Các số tiếp theo sẽ lấy số nhỏ nhất trong dãy
    */
    char min_char = s[0];
    int index = 0;
    for (int i = 0; i <= k; i++) {
        if (min_char > s[i] && s[i] != '0') {
            min_char = s[i];
            index = i;
        }
    }
    k -= index;
    int cur = index + 1;
    string ans = "";
    ans += s[index];
    RMQ<char> rmq;
    rmq.build(vector<char>(s.begin(), s.end()));
    /*
    Tìm từng số hạng 1. nếu cur + k >= s.size() -> dừng
    Còn k số cần xóa và mảng còn lại là từ cur -> s.size()
    */
    dbg(cur, k);
    while (k > 0) {
        if (cur + k >= (int)s.size()) {
            cur = (int)s.size();
            k = 0;
            break;
        }
        // Tìm index có giá trị nhỏ nhất và dịch cur về đó
        int next_index = rmq.query_index(cur, cur + k);
        k -= next_index - cur;
        cur = next_index + 1;
        ans += s[next_index];
    }

    for (int i = cur; i < s.size(); i++) {
        ans += s[i];
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    while (n--)
        solve();

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
