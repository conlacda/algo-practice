#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

vector<string> board;
int N;
int c=0;
bool is_possible(int row, int col){
    for (int i=0;i<N; i++){
        if (board[row][i] == 'Q') return false;
        if (board[i][col] == 'Q') return false;
        if ( row-i >=0 && col-i >=0 &&board[row-i][col-i] == 'Q') return false;
        if (row+i<N && col-i>=0 && board[row+i][col-i] == 'Q') return false;
    }
    return true;
}
void solve(int col){
    if (col >=N){
        // for (int i = 0;i< N;i++){
        //     cout << board[i] << '\n';
        // }
        // cout << "---------\n";
        c++;
    } else{
        for (int i=0;i<N;i++){
            if (board[i][col] != '*' && is_possible(i, col)){
                board[i][col] = 'Q';
                solve(col+1);
                board[i][col] = '.';
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s;
    cin >> s;
    board.push_back(s);
    N = s.size();
    for (int i=0;i<N-1;i++){
        cin >> s;
        board.push_back(s);
    }
    // for (int i = 0;i< N;i++){
    //     cout << board[i] << ' ';
    //     cout << '\n';
    // }
    solve(0);
    cout << c;
}
"""
Sử dụng thuật toán backtracking để giải"""