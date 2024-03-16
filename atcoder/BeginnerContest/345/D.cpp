// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif
int n, h, w;
vector<pair<int,int>> tiles;

bool isOK(vector<int>& s, int bit) {
    if (s == vector<int>{1,3,4}) dbg(bit);
    vector<vector<bool>> grid(h, vector<bool>(w, false));
    std::function<bool(pair<int,int>, bool)> place = [&](pair<int,int> tile, bool flip) {
        for (int i=0;i<h;i++) {
            for (int j=0;j<w;j++) {
                if (!grid[i][j]) {
                    // đặt gạch vào vị trí này
                    int th = tile.second, tw = tile.first;
                    if (flip) swap(th, tw);
                    for (int p=0;p<th;p++) {
                        for (int q=0;q<tw;q++) {
                            if (i + p >= h || j + q >= w) {
                                return false;
                            }
                            if (grid[i + p][j + q]) {
                                return false;
                            }
                            grid[i +p][j+q] = true;
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    };
    // Kiểm tra xem toàn bộ diện tích có thỏa mãn ko
    int dt = 0;
    for (auto&v: s) dt += tiles[v].first * tiles[v].second;
    if (dt != h * w) return false;
    // for (auto&v: s) {
    for (int i=0;i<(int) s.size();i++) {
        auto v = s[i];        
        bool flip = false;
        if ((1<<i) & bit) flip = true;
        bool pl = place(tiles[v], flip);
        if (!pl) return false;
    }
    return true;
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin >> n >> h >> w;
    tiles.resize(n);
    for (int i=0;i<n;i++) cin >> tiles[i].first >> tiles[i].second;
    dbg(tiles);
    
    for (int i=1;i<(1<<n);i++) {
        vector<int> s;
        for (int j=0;j<n;j++) {
            if ((1<<j) &i) s.push_back(j);
        }
        // Kiểm tra xem từng set này có hoạt động không
        // Lấy toàn bộ permutation của set này ra
        do {
            // bit thể hiện việc viên nào sẽ bị flip
            for (int bit=0;bit< (1<<(int) s.size());bit++) {
                if (isOK(s, bit)) {
                    cout << "Yes";
                    return 0;
                }
            }
        } while (std::next_permutation(s.begin(),s.end()));
    }
    cout << "No";
    show_exec_time();
}
/*
Cứ đặt như css đặt ngang mãi
cho tới khi được rồi check xem nó có hoạt động không
chọn K khối trong N khối
Lấy permutation của K khối đó đưa vào xem có OK không
*/
