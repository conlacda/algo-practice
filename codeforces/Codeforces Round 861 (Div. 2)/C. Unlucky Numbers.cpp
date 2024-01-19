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

enum CONSTR { none, low, up, both };

// pair<count, match number>
string digitDPSameDigit(string low, string up, int mind, int maxd) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    vector<vector<int>> cnt(n, vector<int>(4, 0)); // cnt[index][constraint]
    // res[index][constraint] = ""
    vector<vector<string>> num(n, vector<string>(4, string(n, ' ')));
    if (up[0] == low[0]) {
        int digit = up[0] - '0';
        if (mind <= digit && digit <= maxd) {
            cnt[0][CONSTR::both] = 1; // ***
            num[0][CONSTR::both][0] = char(digit + '0');
        }
    } else {
        int digit = low[0] - '0';
        if (mind <= digit && digit <= maxd) {
            cnt[0][CONSTR::low] = 1; // 1234 & 3456 => 1xxx // ***
            num[0][CONSTR::low][0] = char(digit + '0');
        }
        for (int digit=low[0]-'0'+1;digit<=up[0]-'0'-1;digit++) {
            if (mind <= digit && digit <= maxd) {
                cnt[0][CONSTR::none] += 1; // ***
                num[0][CONSTR::none][0] = char(digit + '0');
            }
        }
        digit = up[0] - '0';
        if (mind <= digit && digit <= maxd) {
            cnt[0][CONSTR::up] = 1; // ***
            num[0][CONSTR::up][0] = char(digit + '0');
        }
    }
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        // none -> none. Chữ số trước ko constraint thì toàn bộ chữ số sau cũng ko constraint
        for (int digit=0;digit<10;digit++) {
            if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::none] != 0) {
                cnt[index][CONSTR::none] += cnt[index-1][CONSTR::none]; // ***
                num[index][CONSTR::none] = num[index-1][CONSTR::none]; // ***
                num[index][CONSTR::none][index] = char(digit + '0');
            }
        }
        // up -> none
        for (int digit=0;digit<up[index]-'0';digit++) {
            if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::up] != 0) {
                cnt[index][CONSTR::none] += cnt[index-1][CONSTR::up]; // ***
                num[index][CONSTR::none] = num[index-1][CONSTR::up]; // ***
                num[index][CONSTR::none][index] = char(digit + '0');
            }
        }
        // up -> up
        int digit = up[index] - '0';
        if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::up] != 0) {
            cnt[index][CONSTR::up] += cnt[index-1][CONSTR::up]; // ***
            num[index][CONSTR::up] = num[index-1][CONSTR::up]; // ***
            num[index][CONSTR::up][index] = char(digit + '0');
        }
        // low -> none
        for (int digit=low[index]-'0'+1;digit<=9;digit++) {
            if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::low] != 0) {
                cnt[index][CONSTR::none] += cnt[index-1][CONSTR::low]; // ***
                num[index][CONSTR::none] = num[index-1][CONSTR::low]; // ***
                num[index][CONSTR::none][index] = char(digit + '0');
            }
        }
        // low -> low
        digit = low[index] - '0';
        if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::low] != 0) {
            cnt[index][CONSTR::low] += cnt[index-1][CONSTR::low]; // ***
            num[index][CONSTR::low] = num[index-1][CONSTR::low]; // ***
            num[index][CONSTR::low][index] = char(digit + '0');
        }
        // both -> both
        if (up[index] == low[index]) {
            digit = low[index] - '0';
            if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::both] != 0) {
                cnt[index][CONSTR::both] += cnt[index-1][CONSTR::both]; // ***
                num[index][CONSTR::both] = num[index-1][CONSTR::both]; // ***
                num[index][CONSTR::both][index] = char(digit + '0');
            }
        }
        else {
            // both -> low
            digit = low[index] - '0';
            if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::both] != 0) {
                cnt[index][CONSTR::low] += cnt[index-1][CONSTR::both]; // ***
                num[index][CONSTR::low] = num[index-1][CONSTR::both]; // ***
                num[index][CONSTR::low][index] = char(digit + '0');
            }
            // both -> up
            digit = up[index] - '0';
            if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::both] != 0) {
                cnt[index][CONSTR::up] += cnt[index-1][CONSTR::both]; // ***
                num[index][CONSTR::up] = num[index-1][CONSTR::both]; // ***
                num[index][CONSTR::up][index] = char(digit + '0');
            }
            // both -> none
            for (int digit=low[index]-'0'+1;digit<up[index]-'0';digit++) {
                if (mind <= digit && digit <= maxd && cnt[index-1][CONSTR::both] != 0) {
                    cnt[index][CONSTR::none] += cnt[index-1][CONSTR::both]; // ***
                    num[index][CONSTR::none] = num[index-1][CONSTR::both]; // ***
                    num[index][CONSTR::none][index] = char(digit + '0');
                }
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
