// https://codeforces.com/contest/858/problem/D
// https://codeforces.com/contest/858/my
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

<hash-without-changing>
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    // Dùng hash để check brute-force
    int n;
    cin >> n;
    vector<string> a(n);
    string s = "";
    for (int i=0;i<n;i++) cin >> a[i];
    Hash<string> hash;
    // xử lý từng trường string 1 -> 1 string tạo ra 81 mã hash
    // Đếm tất cả mã hash đó vào 1 map -> xét lại từng substring xem nếu có số hash == 1 là được
    hash.build(10);
    vector<unordered_set<ll>> v(n);
    // v tại đây lấy ra 81hash của string ith đưa ra set, giống nhau sẽ bị xóa
    for (int i=0;i<n;i++) {
        hash.load(a[i]);
        for (int j=0;j<9;j++) {
            for (int k=j;k<9;k++) {
                v[i].insert(hash.substr(j, k-j+1));
            }
        }
    }
    // hợp tất cả v vào trong m và đếm xem hash xuất hiện mấy lần
    // Do v là vector<set> nên ở đây bất kỳ hash nào xuất hiện >=2 là do xuất hiện ở 2 string khác nhau
    // -> chỉ cần xuất hiện 1 lần thì đó chính là duy nhất và cập nhật lại ans nếu độ dài nó ngắn hơn so với độ dài hiện tại
    unordered_map<ll, ll> m;
    for (int i=0;i<n;i++){
        for (auto u: v[i]){
            m[u]++;
        }
    }
    vector<string> ans(n, "____________________"); // dài nhất là 9 phần tử là khi gõ toàn bộ số điện thoại -> ____ chỉ làm mẫu để nó có độ dài > 9
    for (int i=0;i<n;i++) {
        hash.load(a[i]);
        for (int j=0;j<9;j++){
            for (int k=j;k<9;k++){
                if (m[hash.substr(j, k-j+1)] == 1) {
                    if (ans[i].size() > k-j+1) {
                        ans[i] = a[i].substr(j, k-j+1);
                    }
                }
            }
        }
    }
    for (auto v: ans) {
        cout << v << '\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
