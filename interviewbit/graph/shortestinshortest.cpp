// https://www.interviewbit.com/test/d2a24e448c/?signature=BAhpA9g0Ew%3D%3D--006683556a1f85ce6a0b2df03fbb56224d6e2891#/problem_1
/*
Tóm tắt đề bài:
Cho 1 graph vô hướng có trọng số
Xét 2 điểm start, end. Trong các đường đi ngắn nhất từ start tới end. Lấy ra đoạn nhỏ nhất.
Ví dụ: 
4 verticies
1->3 = 9
1->4 = 6
2->3 = 1
2->4 = 3
3->2 = 1
3->1 = 9
4->2 = 3
4->1 = 6
start = 2, end = 1
Từ 2->1 sẽ có 2->3(dis=1)->1(dis=9) -> dis=10 || 2->4(dis=3)->1(dis=6) -> dis=9
Khoảng cách ngắn nhất sẽ là 9. -> kết quả = min(3,6) = 3
Cách giải:
Sử dụng thuật toán dijkstra(). Với mỗi node thay vì chỉ lưu khoảng cách
thì giờ lưu thêm 1 giá trị nữa là đoạn ngắn nhất từ start tới node đó Dist{value, min_dist}
-> value chính là khoảng cách ngắn nhất còn min_dist sẽ là đoạn nhỏ nhất
Logic:
if (d+ G[u][i].second <dist[G[u][i].first].a){
    dist[G[u][i].first].a = d + G[u][i].second;
    dist[G[u][i].first].min_dist = min(G[u][i].second, dist[u].min_dist); // gán lại min_dist cho node đó
    Q.push({G[u][i].first, dist[G[u][i].first].a});
}
start->A + A->end < start->end
thì end.min_dist = min(A.min_dist, A->end)
*/

#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

struct Node {
    int id; ll dist;
    friend bool operator<(const Node &a, const Node &b){
        return a.dist > b.dist;
    }
};

struct Dist{
    ll a;
    int min_dist;
};
class WeightedDirectedGraph{
public:
    int V;
    vector<vector<pair<int,int>>> G;
    vector<bool> visited;
    WeightedDirectedGraph(int V){
        for (int i=0;i<=V;i++){
            G.push_back({});
            this->visited.push_back(false);
        }
        this->V = V;
    }
    void addEdge(int a, int b, ll w){
        G[a].push_back(make_pair(b,w));
    }
    void show(){
        cout << G.size() -1 << " verticies\n";
        for (int i=0;i<=V;i++){
            for (auto v: G[i]){
                cout << i << "->";
                cout << v.first << " = " << v.second << '\n';
            }
        }
    }
    void dijkstra(int start, int end){
        priority_queue<Node> Q;
        // vector<ll> dist(V+1, LLONG_MAX);
        vector<Dist> dist(V+1, Dist{LLONG_MAX, INT_MAX});
        dist[start] = Dist{0, INT_MAX}; 
        visited[start] = true;
        
        for (int i=0;i<G[start].size();i++){
            if (dist[G[start][i].first].a > G[start][i].second){
                dist[G[start][i].first].a = G[start][i].second;
                dist[G[start][i].first].min_dist = G[start][i].second;
            }
            visited[G[start][i].first] = true;
            Q.push({G[start][i].first, dist[G[start][i].first].a});
        }

        while (!Q.empty()){
            ll d = Q.top().dist;
            int u = Q.top().id;
            Q.pop();
            if (d>dist[u].a) continue;
            for (int i=0;i<G[u].size();i++){
                if (d+ G[u][i].second <dist[G[u][i].first].a){
                    dist[G[u][i].first].a = d + G[u][i].second;
                    dist[G[u][i].first].min_dist = min(G[u][i].second, dist[u].min_dist);
                    Q.push({G[u][i].first, dist[G[u][i].first].a});
                }
            }
        }
        cout << dist[end].min_dist;
        // for (int i=0;i<dist.size();i++){
        //     cout << i << ' '<< dist[i].a << ' '<< dist[i].min_dist << '\n';
        // }
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, V;
    cin >> N >> V;
    WeightedDirectedGraph g(N);
    for (int i=0;i<V;i++){
        int s, e; ll w;
        cin >> s >> e >> w;
        g.addEdge(s, e, w);
        g.addEdge(e, s, w);
    }
    int start, end;
    cin >> start >> end;
    g.dijkstra(start, end);
    g.show();
}

