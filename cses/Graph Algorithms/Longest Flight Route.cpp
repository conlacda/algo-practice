//https://cses.fi/problemset/result/2886656/
/*
Cho đồ thị có hướng, ko trọng số. 
Hỏi từ 1->N có thể đi qua tối đa bao nhiêu đỉnh
Bài này có cách giải đầu tiên nghĩ tới là chuyển trọng số về -1.
Khi này sẽ thành bài toán tìm đường đi ngắn nhất với dijkstra.
Nhưng kết quả sẽ bị TLE với 1 testcase.

Hướng tiếp cận khác:
Dùng toposort.
Sau khi sắp xếp topo thì tuần tự theo sắp xếp đó tính ra trọng số của đỉnh là 
số đỉnh tối đa có thể đi.
Ví dụ: 1->4->3->5 thì w[1]=1; w[4]=2; w[3] =3; w[5]=4;
Vì ko có cycle nên khi duyệt qua đỉnh u thì sẽ ko có việc v->u nữa. nếu như thế thì toposort phải là v ..u.. và v được xử lý trước
*/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;
/*
Thêm topo sort thành 1 hàm
*/

class Graph{ // graph chung cho tất cả
public:
    // General part
    int V; // vertex num 0->V-1
    vector<vector<pair<int,int>>> G, Gre;
    vector<bool> visited;
    Graph(int V){
        this->V  = V +1;
        G.resize(this->V, {});
        Gre.resize(this->V, {});
        visited.resize(this->V, false);
    }
    void addEdge(int u, int v, int w = -1){
        G.at(u).push_back({v, w});
        Gre.at(v).push_back({u, w});
    }
    // Topo sort -> thử biến đổi hàm này về dạng lambda function
    vector<int> topo;
    void topo_explore(int start){
        if (!visited[start]) {
            visited[start] = true;
            for (auto p: G[start]){
                int v = p.first;
                if (!visited[v]) topo_explore(v);
            }
            topo.push_back(start);
        }
    }
    void toposort(){
        topo_explore(1);
        reverse(topo.begin(), topo.end()); // 1 2 ... N
        // for (auto v: topo) cout << v << ' '; cout <<'\n';
    }
    void solve(){
        vector<int> ans(V, 1);
        vector<int> trace(V, -1);
        /*
        Lấy ra được topo sort sau đó từ đỉnh sẽ mở rộng dần ra
        Vì là sắp xếp topo nên những đỉnh đứng trước sẽ xử lý trước
        Nên những đỉnh đứng trước đã được cập nhật sẽ ko cập nhật lại
        if (hasEdge(u->v)) ans[v] = max(ans[u]+1, ans[v])
        khi có cạnh uv thì v sẽ lấy theo u nếu u+1>v
        Ví dụ:
        1->3->5->6->4 ans[4] = 5
        1->2->4. Khi chạy tới 2 thì 2 có ans[2] = 2. thì 4 sẽ ko cập nhật theo 2 nữa.
        Những đỉnh được xử lý rồi thì sẽ ko bị quay ngược lại như xử lý tự do kiểu
        1->2->4 rồi lại có 3->2 làm cho 4 ko còn đúng. khi này topo sẽ là 1 3 2 4 và đảm bảo 2 ko được xử lý 2 lần
        Thêm phần trace vào trong câu lệnh trên sẽ được
        if (hasEdge(u->v)) {
            ans[v] = max(ans[u]+1, ans[v])
            trace[v] = u; // parent[v] = u;
        }
        Retrive path:
        while (x=V-1 != start=1){
            path.push_back(x);
            x = trace[x]; // x = parent[x];
        }
        */
        for (auto t: topo){
            for (int i=0;i<G[t].size();i++){
                int u = G[t][i].first;
                if (ans[t] + 1> ans[u]) {
                    ans[u] = ans[t]+1;
                    trace[u] = t;
                }
            }
        }
        if (ans.at(V-1) == 1) cout << "IMPOSSIBLE";
        else{
            cout << ans.at(V-1)<< '\n';
            vector<int> t{V-1};
            int x = V-1;
            while (x!=1){
                x = trace[x];
                t.push_back(x);
            }
            reverse(t.begin(), t.end());
            for (auto v: t) cout << v<< ' ';
        }
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, M;
    cin >> N >> M;
    Graph g(N);
    for (int i=0;i<M;i++){
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }
    g.toposort();
    g.solve();
}
