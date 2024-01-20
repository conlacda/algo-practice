// https://codeforces.com/gym/100886/problem/G
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

#define init(cur) \
{ \
    cnt[0][cur] += 1;\
    if (prod[0][cur] < digit) \
    { \
        prod[0][cur] = digit; \
        num[0][cur][0] = char(digit + '0'); \
    } \
} \


#define transition(cur, prev) \
if (cnt[index-1][prev] != 0) {\
    cnt[index][cur] += cnt[index-1][prev]; \
    if (prod[index][cur] < prod[index-1][prev] * digit) \
    { \
        prod[index][cur] = prod[index-1][prev] * digit; \
        num[index][cur] = num[index-1][prev]; \
        num[index][cur][index] = char(digit + '0'); \
    } \
}\

// digitDP[index][constraint]
pair<string, int> digitDPSameDigit(string low, string up) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    vector<vector<int>> cnt(n, vector<int>(4, 0)); // cnt[index][constraint]
    vector<vector<int>> prod(n, vector<int>(4, 0)); // cnt[index][constraint]
    vector<vector<string>> num(n, vector<string>(4, string(n, ' ')));
    if (up[0] == low[0]) {
        int digit = up[0] - '0';
        init(CONSTR::both);
    } else {
        int digit = low[0] - '0';
        init(CONSTR::low); // 1234 & 3456 => 1xxx
        for (int digit=low[0]-'0'+1;digit<=up[0]-'0'-1;digit++) {
            init(CONSTR::none);
        }
        digit = up[0] - '0';
        init(CONSTR::up);
    }
    /*
    Không constraint => không constraint
    Constraint trên => ko constraint
                    => tiếp tục constraint
    Constraint dưới => ko constraint
                    => tiếp tục constraint
    Constraint 2 chiều => ko constraint
                       => constraint trên
                       => constraint dưới
                       => constraint 2 chiều
    */
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
        transition(CONSTR::up, CONSTR::up);
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

    // cout << ans; // cnt[n-1][0/1/2/3]
    int max_prod = 0;
    string number = "";
    for (int i=0;i<3;i++) {
        if (cnt[n-1][i] != 0) {
            if (prod[n-1][i] > max_prod) {
                max_prod = prod[n-1][i];
                number = num[n-1][i];
            }
        }
    }
    return make_pair(number, max_prod);
}

string digitDP(string l, string r) {
    std::function<string(int)> full9 = [&](int num_digit){ return string(num_digit, '9');};
    std::function<string(int)> full0 = [&](int num_digit){ return '1' + string(num_digit-1, '0'); };
    
    int cur_max = 0;
    string cur_str = l;
    for (int i=(int)l.size();i<=(int)r.size();i++) {
        string ll = (i > (int) l.size()) ? full0(i) : l;
        string rr = (i < (int) r.size()) ? full9(i) : r;
        auto [number, max_prod] = digitDPSameDigit(ll, rr);
        if (max_prod >  cur_max) {
            cur_max = max_prod;
            cur_str = number;
        }
    }

    return cur_str;
}

string digitDP(int l, int r) { return digitDP(to_string(l), to_string(r)); }
/** Comment xem tại github */
/**
 * Phần này chia [l:r] thành các đoạn có cùng số digit.
 * Ví dụ: [12:4321] = [12:99] + [100:999] + [1000:4321]
 * Đếm đoạn to bằng việc đếm các đoạn nhỏ hơn có cùng độ dài digit
 * Khi này ko cần leading_zero
 * dp[index][digit][constraint]
 * index là index tại số đang xét (giống các bài khác) l = 123 => l[0] = 1, l[1] = 2, l[2] = 3
 * digit: digit điền vào cho index đang xét
 * constraint: có 4 loại
 *     * 0: không constraint. [123:256] => 2xx
 *     * 1: constraint cho phần bên dưới. [123:256] => 1xx
 *     * 2: constraint cho phần trên. [123:256] => 2xx
 *     * 3: constraint cho cả low/up. [523:576] => 5xx. low[index] = up[index] = 5 -> số 5 vừa constraint dưới, vừa constraint trên
*/

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string l, r;
    cin >> l >> r;
    /*
    dp[index][constraint][product]
    */
    cout << digitDP(l, r);

    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
