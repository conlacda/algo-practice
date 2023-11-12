// https://codeforces.com/contest/1808/problem/C
// C. Unlucky Numbers
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
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

// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
// Trong khoảng này số có độ chệnh lệch max, min là số nào
// độ chênh lệch là k (0->9) có số nào không -> có 1 số là in ra luôn
/*
Nếu vấn đề là tìm số có chênh lệch max/min lớn nhất thì đơn giản là cứ
lấy max lớn nhất có thể, min nhỏ nhất có thể -> tracking max, min rồi in ra max-min là xong
Nhưng ở bài này nếu max cứ lấy giảm đi tối đa có thể, min lấy lớn nhất có thể
thì max lại thành min, min -> max và kết quả cuối cùng ko được tối ưu
-> Xét riêng từng max, min với max = 0->9, min = 0->9
Nếu tồn tại 1 số thỏa mãn max/min này thì cập nhật kết quả
Với max-min lần lượt là 0->9 cho tới khi tìm ra được kết quả thì thôi
-> độ phức tạp max=10*min=10 -> mỗi testcase phải xử lý 100 trường hợp của max,min

Đếm số lượng số có mind và maxd
*/

// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
pair<string, int> digitDPSameDigit(string low, string up, int mind, int maxd) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    std::function<bool(int)> ok = [&](int u){
        return mind <= u && u <= maxd;
    };
    // Initial state
    // dp[index][digit][constraint_0/1/2/3
    // cnt[index][digit][constraint][mind][maxd]
    vector<vector<vector<bool>>> touch(n, vector<vector<bool>>(10, vector<bool>(4, false)));
    vector<vector<vector<int>>> cnt(n, vector<vector<int>>(10, vector<int>(4, 0)));
    vector<vector<vector<string>>> res(n, vector<vector<string>>(10, vector<string>(4, string(n, ' '))));
    if (up[0] == low[0]) {
        if (ok(up[0] - '0')) {
            touch[0][up[0] - '0'][3] = true; // 1234 & 1567 => 1xxx
            cnt[0][up[0] - '0'][3] = 1;
            res[0][up[0] - '0'][3][0] = up[0];
        }
    } else {
        if (ok(low[0] - '0')) {
            touch[0][low[0] - '0'][1] = true; // 1234 & 3456 => 1xxx
            cnt[0][low[0] - '0'][1] = 1; // 1234 & 3456 => 1xxx
            res[0][low[0] - '0'][1][0] = low[0];
        }
        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            if (ok(first_digit)) {
                touch[0][first_digit][0] = true; // 2xxx
                cnt[0][first_digit][0] = 1; // 2xxx
                res[0][first_digit][0][0] = first_digit + '0';
            }
        }
        
        if (ok(up[0] - '0')) {
            touch[0][up[0] - '0'][2] = true; // 3xxx
            cnt[0][up[0] - '0'][2] = 1; // 3xxx
            res[0][up[0] - '0'][2][0] = up[0];
        }
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
        for (int digit=mind;digit<=maxd;digit++) {
            // Không constraint => không constraint
            for (int prevdigit=mind;prevdigit<=maxd;prevdigit++) {
                if (!touch[index-1][prevdigit][0]) continue;
                cnt[index][digit][0] += cnt[index-1][prevdigit][0];
                res[index][digit][0] = res[index-1][prevdigit][0];
                res[index][digit][0][index] = digit + '0';

                touch[index][digit][0] = true;
            }

            int prevdigit = up[index-1] - '0';
            // Constraint trên => ko constraint
            if (digit < up[index] - '0') {
                if (touch[index-1][prevdigit][2]) {
                    cnt[index][digit][0] += cnt[index-1][prevdigit][2];
                    res[index][digit][0] = res[index-1][prevdigit][2];
                    res[index][digit][0][index] = digit + '0';
                    touch[index][digit][0] = true;
                }
            }
            // Constraint trên => tiếp tục constraint
            if (digit == up[index] - '0') {
                if (touch[index-1][prevdigit][2]) {
                    cnt[index][digit][2] += cnt[index-1][prevdigit][2];
                    res[index][digit][2] = res[index-1][prevdigit][2];
                    res[index][digit][2][index] = digit + '0';

                    touch[index][digit][2] = true;
                }
            }

            prevdigit = low[index-1] - '0';
            // Constraint dưới => ko constraint
            if (digit > low[index] - '0') {
                if (touch[index-1][prevdigit][1]) {
                    cnt[index][digit][0] += cnt[index-1][prevdigit][1];
                    res[index][digit][0] = res[index-1][prevdigit][1];
                    res[index][digit][0][index] = digit + '0';

                    touch[index][digit][0] = true;
                }
            }
            // Constraint dưới => constraint dưới tiếp
            if (digit == low[index] - '0') {
                if (touch[index-1][prevdigit][1]) {
                    cnt[index][digit][1] += cnt[index-1][prevdigit][1];
                    res[index][digit][1] = res[index-1][prevdigit][1];
                    res[index][digit][1][index] = digit + '0';

                    touch[index][digit][1] = true;
                }
            }
            
            // Constraint 2 chiều => ko constraint
            if (up[index-1] != low[index-1]) continue; // trước đó ko có constraint 2 chiều nữa
            prevdigit = up[index-1] - '0';
            // Constraint 2 chiều hay constraint 1 chiều
            if (up[index] == low[index]) {
                // Constraint 2 chiều tiếp
                if (digit == up[index] - '0') {
                    if (touch[index-1][prevdigit][3]) {
                        cnt[index][digit][3] += cnt[index-1][prevdigit][3];
                        res[index][digit][3] = res[index-1][prevdigit][3];
                        res[index][digit][3][index] = digit + '0';

                        touch[index][digit][3] = true;
                    }
                }
            } else {
                // constraint dưới
                if (digit == low[index] - '0') {
                    if (touch[index-1][prevdigit][3]) {
                        cnt[index][digit][1] += cnt[index-1][prevdigit][3];
                        res[index][digit][1] = res[index-1][prevdigit][3];
                        res[index][digit][1][index] = digit + '0';

                        touch[index][digit][1] = true;
                    }
                } 
                // không constraint nữa
                if (low[index] - '0' < digit && digit < up[index] - '0') {
                    if (touch[index-1][prevdigit][3]) {
                        cnt[index][digit][0] += cnt[index-1][prevdigit][3];
                        res[index][digit][0] = res[index-1][prevdigit][3];
                        res[index][digit][0][index] = digit + '0';

                        touch[index][digit][0] = true;
                    }
                }
                // constraint trên
                if (digit == up[index] - '0') {
                    if (touch[index-1][prevdigit][3]) {
                        cnt[index][digit][2] += cnt[index-1][prevdigit][3];
                        res[index][digit][2] = res[index-1][prevdigit][3];
                        res[index][digit][2][index] = digit + '0';

                        touch[index][digit][2] = true;
                    }
                }
            }
        }
    }

    // cout << ans; // dp[n-1][0:9][0/1/2/3];
    int ans = 0; string s;
    for (int digit=0;digit<=9;digit++) {
        ans += cnt[n-1][digit][0];
        if (cnt[n-1][digit][0] > 0) s = res[n-1][digit][0];
        ans += cnt[n-1][digit][1];
        if (cnt[n-1][digit][1] > 0) s = res[n-1][digit][1];
        ans += cnt[n-1][digit][2];
        if (cnt[n-1][digit][2] > 0) s = res[n-1][digit][2];
        ans += cnt[n-1][digit][3];
        if (cnt[n-1][digit][3] > 0) s = res[n-1][digit][3];
    }
    // dbg(s, ans, mind, maxd);
    return {s, ans};
}

void digitDP(string l, string r) {
    std::function<string(int)> full9 = [&](int num_digit){
        string res = "";
        for (int i=0;i<num_digit;i++) res += '9';
        return res;
    };
    std::function<string(int)> full0 = [&](int num_digit){
        string res = "1";
        for (int i=0;i<num_digit-1;i++) res += '0';
        return res;
    };
    int mi = 9, ma = 0;
    int id = 0;
    while (l[id] == r[id] && id < (int) l.size() && (int) l.size() == (int) r.size()) {
        mi = min(mi, (int) l[id] -'0');
        ma = max(ma, (int) l[id] -'0');
        id++;
    }
    for (int diff=0;diff<10;diff++) {
        for (int mind=0;mind+diff<10;mind++) {
            if (mind > mi || mind + diff < ma) continue; // key - reduce bruteforce
            // int ans = 0;
            string s = "";
            if ((int) l.size() == (int) r.size()) {
                auto x = digitDPSameDigit(l, r, mind, mind + diff);
                if (x.second > 0) {
                    s = x.first;
                }
            }
            else {
                auto x = digitDPSameDigit(l, full9(l.size()), mind, mind + diff);
                if (x.second > 0) s = x.first; 
                for (int i=(int) l.size() +1;i<=(int) r.size() -1;i++) {
                    x = digitDPSameDigit(full0(i), full9(i), mind, mind + diff);
                    if (x.second > 0) s = x.first;
                }
                x = digitDPSameDigit(full0(r.size()), r, mind, mind + diff);
                if (x.second > 0) s = x.first;
            }
            if (s != "") {
                cout << s <<'\n';
                return;
            }
        }
    }
}

void digitDP(int l, int r) { digitDP(to_string(l), to_string(r)); }
/** Comment xem tại github */

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) {
        string l, r;
        cin >> l >> r;
        if ((int) l.size() == 1) cout << l << '\n';
        else
        digitDP(l, r);
    }
    
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
Note:
* touch array
* remove dp if unnecessary - xóa đi vì việc cấp phát và assign tốn thời gian trong bài chặt chẽ về thời gian
* reduce bruteforce
* Với bài xử lý mối quan hệ giữa các digit -> dùng bruteforce đầu vào/binary search
Tại đây: tìm số có max_digit - min_digit là nhỏ nhất.
Nếu duyệt 1 lần thì ko xử lý được max_digit - min_digit.
    Do phải optimise (max_d - min_d) chứ ko phải optimise từng giá trị max_d, min_d
    Nếu optimise max_d lấy max liên tục thì sẽ ra max(max_d - min_d)
    còn tại đây min(max_d - min_d) thì giá trị này min đạt được khi 2 số gần nhau
    chứ ko phải optimise từng biến.
Do đó sử dụng bruteforce đầu vào hoặc binary search.
Đặt giá trị max_d, min_d cho sẵn và rồi đếm xem có số nào thỏa mãn không
diff = 0 -> 9. Nếu tìm thấy tại điểm diff nào thì in ra và ngắt luôn.
Lưu ý đoạn cho đầu vào min_d, diff thì loại bỏ bớt 1 số trường hợp 
với phần đầu chung. Ví dụ: 123xxx -> 123yyy. thì min_d = 1, max_d = 3
thế thì không cần xét trường hợp min_d = 2 hay max_d = 2. => chính đoạn này giảm từ
8s -> 0.3s
*/