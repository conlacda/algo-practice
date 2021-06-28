#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main(){
    // freopen("inp.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int m,n,k;
    cin >> m>>n>>k;
    vector<int> size, desire;
    for (int i=0;i<m;i++){
        int x;
        cin >> x;
        size.push_back(x);
    }
    for (int i=0;i<n;i++){
        int x;
        cin >>x;
        desire.push_back(x);
    }
    sort(size.begin(), size.end());
    sort(desire.begin(), desire.end());
    int i=0,j=0, c=0;
    while (i < m && j<n){
        if (desire[j] -k<= size[i] && size[i]<=desire[j] + k){
            c++;
            i++;
            j++;
        } else if (desire[j] +k <size[i]){
            j++;
        } else if (desire[j] -k > size[i]){
            i++;
        }
    }
    cout << c;
}
