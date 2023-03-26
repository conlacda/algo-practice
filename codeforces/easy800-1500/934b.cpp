#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n;
    cin >> n;
    int eight, four;
    eight = n /2;
    four = n % 2;
    string result = "";
    if (n>36){
        cout << -1;
    } else {
        for(int i=0;i<eight;i++){
        result += "8";
        }
        for (int i=0;i<four;i++){
            result +="4";
        }
        cout << result;
    }
    return 0;
}
// #include <bits/stdc++.h>
 
// int main()
// {
// 	int k;
// 	scanf("%d",&k);
// 	if(k <= 36) {
// 		while(k >= 2) {putchar('8');k -= 2;}
// 		if(k >= 1) {putchar('4');k--;}
// 		printf("\n");
// 	} else {
// 		printf("-1\n");
// 	}
// }