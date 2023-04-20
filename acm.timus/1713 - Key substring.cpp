// https://acm.timus.ru/problem.aspx?space=1&num=1713
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

<SuffixArray>

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n; cin >> n;
    vector<string> a(n);
    string s = "";
    vector<pair<int, int>> ranges;
    for (int i=0;i<n;i++) {
        cin >> a[i];
        ranges.push_back({(int) s.size(), (int) a[i].size()});
        s += a[i] + char(0x00);
    }
    dbg(a);
    dbg(ranges); // đánh dấu vị trí bắt đầu của substring trong string
    dbg(s);
    /*
    Xét 1 range [l, r] đại diện cho 1 string con ban đầu.
    Tính lower_bound và upper_bound của string đó - dựa vào suffix aray - O(logN)
    Từ vị trí lower_bound, upper_bound query xem max, min trong rang đó nằm trong [l, r]
    nghĩa là nó chỉ thuộc về string đó -> ok. O(logN^2)
    Với mỗi vị trí dùng binary search để tìm ra độ dài mà nó là unique. 
    O(NlogN) cho toàn bộ mà ko cần dùng hash
    */
    SuffixArray suf(s);
    for (auto v: ranges) {
        int start, sz;
        std::tie(start, sz) = suf.key_substring(v.first, v.second);
        cout << s.substr(start, sz) << '\n';
    }
}
