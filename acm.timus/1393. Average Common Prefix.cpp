// https://timus.online/problem.aspx?space=1&num=1393
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

<suffix_array>
<hash_string>
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(3);
    int n;
    cin >> n;
    string s;
    cin >> s;
    SuffixArray suf(s);
    ll ans = 0;
    dbg(suf.suffix_array);
    Hash<string> hash;
    hash.build(s.size());
    hash.load(s);
    for (int i=0;i<n-1;i++) {
        ans += hash.common_prefix(suf.suffix_array[i], suf.suffix_array[i+1]);
    }
    cout << double(ans) / (n-1);
    // dbg(suf.common_prefix_of_substrs(0, 2));
}
/*
lcp tại hàm ban đầu với index = n-2 thì tối đa nó cũng chỉ tới biên n tức là
lcp tại string đó với string bên cạnh tối đa chỉ là 2.
Việc sửa hàm đó rất khó khăn -> dùng SuffixArray với đầu vào là s+s. Khi này mọi điểm trên string s ban đầu đều có đoạn nối dài thêm ở s thứ 2
Sử dụng hàm common_prefix_of_substrs để lấy ra độ dài chung tại 2 điểm start của s, nếu nó dài hơn n thì sẽ là n.
=> Kết quả ko sai nhưng bị MLE - do string dài 500.000 (250.000 * 2) -> reduce memory của SuffixArray ban đầu??
OR
chuyển qua cách dùng hash để so sánh 2 string cạnh nhau
hash.load(string s);
Với 2 string bên cạnh tìm common_prefix - mất O(logN) cho 1 cặp
*/
