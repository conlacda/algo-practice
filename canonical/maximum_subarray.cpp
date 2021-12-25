#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    vector<int> array {-1 ,2, 4, -3, 5 ,2 ,-1000, 20};
    int best = 0, sum = 0;
    for (int k = 0; k < 8; k++) {
        sum = max(array[k],sum+array[k]);
        best = max(best,sum);
        cout << sum << " " << best << ' ' << array[k] << '\n';
    }
    cout << best << "\n";

}
