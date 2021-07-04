/*
Giải tự động nonogram
Input
5 -> số N*N
2 1 1 -> 2 là chỉ ra dòng này bao nhiêu số. hàng 1 = {1,1}
1 3 -> hàng 2 = {3}
1 2 
1 3
1 3 -> 5 dòng đầu là row
1 2 -> 5 dòng sau này là column
1 1
2 2 2
1 3
1 3
Output: 
1 0 1 0 0 
1 1 1 0 0 
0 0 0 1 1 
0 0 1 1 1 
0 0 1 1 1 
----------
Sử dụng thuật toán backtracking để giải
*/
#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<vector<bool>> board;
vector<vector<int>> rows, cols;
int N;
void print(){
    for(int i =0;i<N;i++){
        for (int j=0;j<N;j++){
            if (board[i][j]) {
                cout << 1 << ' ';
            } else cout << 0 << ' ';
        }
        cout << '\n';
    }
    cout << "----------\n";
}

bool is_possible(vector<bool> rl, vector<int> row, int idx){
    // rl = {0,0,1,1,1}  row = {1,1};
    vector<int> hint;
    int cnt=0;
    for (int i=0; i<N; i++){
        if (rl[i]) {
            cnt ++;
        } else {
            if (cnt>0) hint.push_back(cnt);
            cnt = 0;
        }
    }
    if (cnt>0) hint.push_back(cnt);
    if (idx+1>=N && hint!=row) return false; 
    if (hint.size() > row.size()) return false;
    else {
        for (int i=0;i< hint.size();i++){
            if (hint[i] > row[i]) return false;
        }
    }
    return true;
}
vector<bool> get_column(int idx){
    vector<bool> result;
    for (int i=0;i<N;i++){
        result.push_back(board[i][idx]);
    }
    return result;
}
bool solve(int x, int y){
    // cout << x << ' '<<  y << '\n';
    // print();
    if (x>=N) {
        print();
        return true;
    }
    int next_x, next_y;
    if (y+1<N) {
        next_y = y+1; next_x = x;
    } else {next_y = 0; next_x= x+1;}
    board[x][y] = true;
    if (is_possible(board[x], rows[x], y) && is_possible(get_column(y), cols[y], x) && solve(next_x, next_y)){
        return true;
    }
    //  else {
    //     for (auto v: board[x])  cout << v << ' ';cout << '~';
    //     for (auto v: rows[x]) cout << v << ' '; cout << '|'; cout<< "index="<< y;cout << "->";
    //     cout << is_possible(board[x], rows[x], y) <<'\n';
    // }
    board[x][y] = false;
    if (is_possible(board[x], rows[x], y) && is_possible(get_column(y), cols[y], x) && solve(next_x, next_y)){
        // cout << "FOUND";
        return true;
    }
    return false;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    // #ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    // #endif
    cin >> N;
    for (int i=0;i<N;i++){
        int x,k;
        vector<int> row;
        cin >> x;
        for (int j=0;j<x;j++){
            cin >> k;
            row.push_back(k);
        }
        rows.push_back(row); 
    }
    for (int i=0;i<N;i++){
        int x,k;
        vector<int> col;
        cin >> x;
        for (int j=0;j<x;j++){
            cin >> k;
            col.push_back(k);
        }
        cols.push_back(col); 
    }
    // Initial board
    for (int i=0;i<N;i++){
        vector<bool> x;
        for (int j=0;j<N;j++){
            x.push_back(false);
        }
        board.push_back(x);
    }
    solve(0,0);// 0 0 0 0 
    // cout << is_possible({true, true, false, true, false}, {2,2}, 3);
}
