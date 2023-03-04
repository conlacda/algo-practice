/*
Date: 2022-10-23
LANG: C++
TASK: beads
*/

#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        ofstream cout("beads.out");
        ifstream cin("beads.in");
    #endif
    int n; cin >> n;
    string s; cin >> s;
    /*
    Lấy ra 1 điểm làm điểm bắt đầu và tính kết quả tại đó
    */
    std::function<int(int)> point = [&](int start){
        // Tính điểm số bắt đầu từ điểm này.
        string _s = s.substr(start, s.size()) + s.substr(0, start);
        // Tìm ra điểm khác w ở vị trí đầu tiên
        int k = 0;
        while (_s[k] == 'w' && k < (int) s.size()){
            k++;
        }
        if (k == (int) s.size()) return (int)s.size();
        int i=k;
        while (_s[i] == _s[k] || _s[i] == 'w') {
            i++;
            if (i == (int)s.size()) return (int)s.size();
        }
        k = i;
        // Lại tìm điểm có vị trí xa nhất khác w
        while (_s[k] == 'w'){
            k++;
            if (k == (int) s.size()) return (int) s.size();
        }
        i = k;
        while (_s[i] == _s[k] || _s[i] == 'w'){
            i++;
            if (i == (int) s.size()) return (int) s.size();
        }
        return i;
    };
    int ans = 0;
    for (int i=0;i<n;i++){
        ans = max(ans, point(i));
    }
    dbg(ans);
    cout << ans << endl;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
    return 0;
}