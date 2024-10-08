// https://codeforces.com/contest/1808/problem/C
// C. Unlucky Numbers
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

template<class... Args>
auto _vector(size_t n, Args&&... args) {
    if constexpr(sizeof...(args) == 1)
        return vector(n, args...);
    else
        return vector(n, _vector(args...));
}

#define init(cur) \
if (mind <= digit && digit <= maxd) { \
    cnt[0][cur] = 1; \
    num[0][cur][0] = char(digit + '0'); \
} \

#define transition(cur, prev) \
if (mind <= digit && digit <= maxd && cnt[index-1][prev] != 0) { \
    cnt[index][cur] += cnt[index-1][prev];\
    num[index][cur] = num[index-1][prev];\
    num[index][cur][index] = char(digit + '0');\
}\


enum CONSTR { none, low, up, both };

// pair<count, match number>
string digitDPSameDigit(string low, string up, int mind, int maxd) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    auto cnt = _vector(n, 4, (int) 0); // cnt[index][constraint]
    vector<vector<string>> num(n, vector<string>(4, string(n, ' ')));
    if (up[0] == low[0]) {
        int digit = up[0] - '0';
        init(CONSTR::both);
    } else {
        int digit = low[0] - '0';
        init(CONSTR::low);

        for (int digit=low[0]-'0'+1;digit<=up[0]-'0'-1;digit++) {
            init(CONSTR::none);
        }
        digit = up[0] - '0';
        init(CONSTR::up);
    }
    
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        // none -> none. Chữ số trước ko constraint thì toàn bộ chữ số sau cũng ko constraint
        for (int digit=0;digit<10;digit++) {
            transition(CONSTR::none, CONSTR::none);
        }
        // up -> none
        for (int digit=0;digit<up[index]-'0';digit++) {
            transition(CONSTR::none, CONSTR::up);
        }
        // up -> up
        int digit = up[index] - '0';
        if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::up] != 0) {
            transition(CONSTR::up, CONSTR::up);
        }
        // low -> none
        for (int digit=low[index]-'0'+1;digit<=9;digit++) {
            transition(CONSTR::none, CONSTR::low);
        }
        // low -> low
        digit = low[index] - '0';
        transition(CONSTR::low, CONSTR::low);
        // both -> both
        if (up[index] == low[index]) {
            digit = low[index] - '0';
            transition(CONSTR::both, CONSTR::both);
        }
        else {
            // both -> low
            digit = low[index] - '0';
            transition(CONSTR::low, CONSTR::both);
            // both -> up
            digit = up[index] - '0';
            transition(CONSTR::up, CONSTR::both);
            // both -> none
            for (int digit=low[index]-'0'+1;digit<up[index]-'0';digit++) {
                transition(CONSTR::none, CONSTR::both);
            }
        }
    }

    int ans = 0;
    for (int i=0;i<4;i++) {
        if (cnt[n-1][i] != 0)
            return num[n-1][i];
    }
    return "";
}

string digitDP(string l, string r, int mind, int maxd) {
    std::function<string(int)> full9 = [&](int num_digit){ return string(num_digit, '9');};
    std::function<string(int)> full0 = [&](int num_digit){ return '1' + string(num_digit-1, '0'); };
    
    for (int i=(int)l.size();i<=(int)r.size();i++) {
        string ll = (i > (int) l.size()) ? full0(i) : l;
        string rr = (i < (int) r.size()) ? full9(i) : r;
        string pis = digitDPSameDigit(ll, rr, mind, maxd);
        if (pis != "") return pis;
    }
    // ko có thì trả về rỗng
    return "";
}

void solve() {
    int l, r;
    cin >> l >> r;
    int mindiff = 10;
    string ans = "";
    for (int mind=0;mind<=9;mind++) {
        for (int maxd=mind;maxd<=9;maxd++) {
            if (maxd - mind > mindiff) continue;
            auto num = digitDP(to_string(l), to_string(r), mind, maxd);
            if (num != "") {
                ans = num;
                mindiff = maxd - mind;
            }
        }
    }
    cout << ans << '\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Tính sao cho hiệu 2 chữ số trong số đó là min
    -> Xét từng cặp chữ số max, min có trong các số dùng digitDP
    -> Với mỗi cặp max, min sẽ tìm được số lượng số. Mấu chốt ở đây là phải lấy ra được 1 số trong số đó.
    */
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
    show_exec_time();
}
