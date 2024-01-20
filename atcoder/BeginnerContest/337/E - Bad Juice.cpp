#include<bits/stdc++.h>

typedef long long ll; 
const ll mod = 1000000007; 
#define int long long 
const int INF = std::numeric_limits<int>::max(); 

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif
template<typename T = int>
struct Combination {
    vector<T> data;
    vector<int> a;
    int n, k;
    bool hasNext = true;
    Combination(vector<T>& data, int k) {
        n = data.size();
        a.resize(k);
        std::iota(a.begin(), a.end(), 0);
        this->data = data;
        this->k = k;
    }
    vector<T> nextCombination() {
        
        vector<T> res;
        for (auto v: a) {
            res.push_back(data[v]);
        }
        
        if (*a.begin() == n-k) hasNext = false;
        else {
            std::vector<int>::iterator mt = a.end();
            while (*(--mt) == n-(a.end()-mt));
            (*mt)++;
            while (++mt != a.end()) *mt = *(mt-1)+1;
        }
        return res;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    
    int n;
    cin >> n;
    int num = 1;
    while ((int) pow(2, num) < n) {
        num++;
    }
    cout << num << '\n' <<flush;
    map<int, set<int>> m; 
    map<int, set<int>> drinkPeople; 
    vector<int> a;
    for (int i=0;i<num;i++) {
        a.push_back(i+1);
    }
    dbg(a);
    int cur = 0;
    bool full = false;
    for (int i=1;i<=num;i++) {
        Combination c(a, i);
        while (c.hasNext) {
            auto comb = c.nextCombination();
            cur++;
            if (cur > n) {
                full = true;
                break;
            }
            for (auto friendId: comb) {
                m[friendId].insert(cur);
                drinkPeople[cur].insert(friendId);
            }
        }
        if (full) break;
    }
    for (int i=1;i<=num;i++) {
        cout << m[i].size() << ' ';
        for (auto v: m[i]) cout << v << ' ';
        cout << '\n' << flush;
    }
    string s;
    cin >> s;
    set<int> stom;
    for (int i=0;i<(int) s.size();i++) {
        if (s[i] == '1') stom.insert(i+1);
    }
    for (int i=1;i<=n;i++) {
        if (stom == drinkPeople[i]) {
            cout << i << flush;
        }
    }
    show_exec_time();
}
