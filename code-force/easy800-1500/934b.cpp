#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ll n;
    cin >> n;
    int eight, four;
    eight = n /2;
    four = n % 2;
    string result = "";
    for(int i=0;i<eight;i++){
        result += "8";
    }
    for (int i=0;i<four;i++){
        result +="4";
    }
    if (stof(result) > pow(10,18)){
        cout << -1;
    } else {
        cout << result;
    }
    return 1;
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