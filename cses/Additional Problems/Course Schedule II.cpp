// Reference: https://usaco.guide/problems/cses-1757-course-schedule-ii/solution
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g (N+1, vector<int>{});
    vector<int> dependence(N+1, 0);
    for (int i=0;i<M;i++){
        int a, b;
        cin >> a >> b;
        dependence[a]++;
        g[b].push_back(a);
    }
    priority_queue<int> Q;
    for (int i=1;i<=N;i++) 
        if (dependence[i] == 0) Q.push(i);
    vector<int> ans;
    while (Q.size() >0){
        int u = Q.top(); Q.pop();
        ans.push_back(u);
        for (int i=0;i<g[u].size();i++){
            dependence[g[u][i]]--;
            if (dependence[g[u][i]] == 0) Q.push(g[u][i]);
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto v: ans) cout << v << ' ';
}
/*
ĐẶT VẤN ĐỀ
Bài này đưa ra 1 cách nhìn khác về topo sort
Topo sort thường thấy sẽ sử dụng DFS() rồi mỗi lần đi về sẽ in ra.
Ý tưởng ban đầu sẽ là nếu có môn 4 5 phải học trước 2. 
Thì duyệt từ 2 tới 1,3 theo DFS() rồi lấy topo khi này mọi môn trước 2 đã được lấy ra rồi mới tới 2.
def explore():
    if (!vis[u]){
        for (v: adj[u]){
            explore(v)
        }
        cout << u // đây là topo
    }
For i in range(1,N+1): // vòng for đảm bảo số nhỏ sẽ được in ra trước cùng với các dependencies của nó
    explore(i) 
Với bài toán này sử dụng topo sort thông thường sẽ bị lỗi tại trường hợp
3->5->1 4->1 2. Vì khi duyệt nó sẽ in 4 3 5 1 2 thay vì 3 4 5 1 2, do 3,4 nằm khác nhánh khi duyệt

HƯỚNG GIẢI QUYẾT
Toposort ở đây sử dụng dependence để đánh dấu các node có thể lấy ra mà ko còn bị phụ thuộc.
Xét đồ thị ngược G_re. với a,b nghĩa là b->a
Ví dụ:
3->5->1 4->1 2. ta sẽ có dependence[1] [2] = 0 thể hiện rằng nó ko bị phụ thuộc
dependence[3] = 1. [5] = 1. [4] = 1
Hình dung về kết quả:

? ? ? 1 2. (1)
Số 1,2 cùng dependence nên sẽ lấy ra trước. theo (1) thì 2 lấy ra trước. rồi tới 1
Mỗi khi lấy ra 1 đỉnh thì mọi đỉnh kề với nó giảm đi 1.
Khi này depend[3] = 1. [5,4] = 0 do không còn phần tử trỏ vào (1 đã xử lý)
Tương tự thì Q sẽ như sau
Q = {2, 1} ans = {}
Q = {1} ans = {2}
Q = {5, 4} ans = {2, 1}
Q = {4, 3} ans = {2, 1, 5}
Q = {3} ans = {2, 1, 5, 4}
Q = {} ans = {2, 1, 5, 4, 3}
Revere a rồi in ra là xong
*/
