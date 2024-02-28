// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int __int128 // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

string to_string(__int128 num) {
    string s;
    while (num != 0) {
        s += num % 10 + '0';
        num /= 10;
    }
    reverse(s.begin(), s.end());
    if ((int)s.size() == 0) s = "0";
    return s;
}
// _int128 in/out
istream& operator>>(istream&in, __int128& num) {
    string s; cin >> s;
    num = 0;
    for (auto v: s) num = num * 10 + (v - '0');
    return in;
}

#ifndef DEBUG
ostream& operator<<(ostream &os, __int128 x) {
    if (x < 0) {
        os << '-';
        x = -x;
    }
    string ans = "";
    while (x != 0) {
        ans += (x%10) + '0';
        x /= 10;
    }
    reverse(ans.begin(), ans.end());
    if ((int) ans.size() == 0) ans = "0";
    os << ans;
    return os;
}
#endif


int k;

enum CONSTR { none, low, up, both };

// i have d, index // ***
#define transition(cur, prev) \
cnt[index][cur] += cnt[index-1][prev]; \
for (auto [mul, _cnt]: dp[index-1][prev]) { \
    dp[index][cur][mul * d] += _cnt; \
} \

// digitDP[index][constraint]
int digitDPSameDigit(string low, string up) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    vector<vector<int>> cnt(n, vector<int>(4, 0));
    vector dp(n, vector(4, map<int, int>())); // dp[index][constraint][mul] => cnt
    if (up[0] == low[0]) {
        int d = up[0] - '0';
        cnt[0][CONSTR::both] += 1;
        dp[0][CONSTR::both][d] += 1;
    } else {
        int d = low[0] - '0';
        cnt[0][CONSTR::low] += 1;
        dp[0][CONSTR::low][d] += 1;
        for (int d=low[0]-'0'+1;d<=up[0]-'0'-1;d++) {
            cnt[0][CONSTR::none] += 1;
            dp[0][CONSTR::none][d] += 1;
        }
        d = up[0] - '0';
        cnt[0][CONSTR::up] += 1;
        dp[0][CONSTR::up][d] += 1;
    }
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        // none -> none. Chữ số trước ko constraint thì toàn bộ chữ số sau cũng ko constraint
        for (int d=0;d<10;d++) {
            transition(CONSTR::none, CONSTR::none);
        }
        // up -> none
        for (int d=0;d<up[index]-'0';d++) {
            transition(CONSTR::none, CONSTR::up);
        }
        // up -> up
        int d = up[index] - '0';
        transition(CONSTR::up, CONSTR::up);
        // low -> none
        for (int d=low[index]-'0'+1;d<=9;d++) {
            transition(CONSTR::none, CONSTR::low);
        }
        // low -> low
        d = low[index] - '0';
        transition(CONSTR::low, CONSTR::low);
        // both -> both
        if (up[index] == low[index]) {
            d = low[index] - '0';
            transition(CONSTR::both, CONSTR::both);
        }
        else {
            // both -> low
            d = low[index] - '0';
            transition(CONSTR::low, CONSTR::both);
            // both -> up
            d = up[index] - '0';
            transition(CONSTR::up, CONSTR::both);
            // both -> none
            for (int d=low[index]-'0'+1;d<up[index]-'0';d++) {
                transition(CONSTR::none, CONSTR::both);
            }
        }
    }
    // Get answer // dp[n-1][0/1/2/3]
    int ans = 0;
    for (int c=0;c<4;c++) {
        for (auto [mul, _cnt]: dp[n-1][c]) {
            if (mul <= k) 
                ans += _cnt;
        }
    }
    return ans;
}

int digitDP(string l, string r) {
    std::function<string(int)> full9 = [&](int num_digit){ return string(num_digit, '9');};
    std::function<string(int)> full0 = [&](int num_digit){ return '1' + string(num_digit-1, '0'); };
    
    int ans = 0;
    for (int i=(int)l.size();i<=(int)r.size();i++) {
        string ll = (i > (int) l.size()) ? full0(i) : l;
        string rr = (i < (int) r.size()) ? full9(i) : r;
        ans += digitDPSameDigit(ll, rr);
    }

    return ans;
}

int digitDP(int l, int r) { return digitDP(to_string(l), to_string(r)); }

int bruteForce(int l, int r, int k) {
    std::function<int(int)> mul = [&](int u) {
        int m = 1;
        while (u != 0) {
            m *= u % 10;
            u /= 10;
        }
        return m;
    };
    int ans = 0;
    for (int i=l;i<=r;i++) {
        if (mul(i) <= k) {
            ans++;
            dbg(i);
        }
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n >> k;
    // 0->n đếm số lượng số có tích <= k
    cout << digitDP(1, n);
    show_exec_time();
}
/*
Lưu ý duy nhất ở bài này là số có dạng xxx0xx có ít nhất 1 số 0 bên trong.
Nếu duyệt trái qua phải xxx mà x*x*x > k loại đi thì là ko đúng vì xxx có lớn bao nhiêu thì số 0 nhân vào đều thành 0 nên đều được đếm
Bài này có thể làm nhanh hơn bằng cách duyệt digitDP chỉ trên số không chứa số 0 rồi đếm số lượng số bao gồm ít nhất 1 số 0 sau => có lẽ nếu làm theo cách này thì xứng đáng với rate 2k cho bài này.
Tại đây chỉ đơn giản thêm 1 trường [map<int/mul, int/cnt>] là xong chứ ko khó như mk nghĩ ban đầu rằng mul sẽ có rất nhiều giá trị và ko thể hội tụ
*/
