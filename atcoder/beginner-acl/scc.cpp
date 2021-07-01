//https://atcoder.jp/contests/practice2/tasks/practice2_g
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

class DirectedGraph{
public:
    int V;
    vector<vector<int>> G, G_re;
    vector<bool> visited, visited_re;
    DirectedGraph(int V){
        for (int i=0;i<=V;i++){
            G.push_back({});
            G_re.push_back({});
            this->visited.push_back(false);
            this->visited_re.push_back(false);
        }
        this->V = V;
    }
    void addEdge(int a, int b){
        G[a].push_back(b);
        G_re[b].push_back(a);
    }
    void show(){
        cout << G.size() << " verticies\n";
        for (int i=0;i<=V;i++){
            cout << i << "->";
            for (auto v: G_re[i]){
                cout << v << ' ';
            }
            cout << '\n';
        }
    }
    // SCC function
    vector<int> post_re, post, buff;
    vector<vector<int>> scc;
    void explore_re(int start){
        if (!visited_re[start]){
            visited_re[start] = true;
            for (auto v: G_re[start]){
                if (!visited_re[v]) explore_re(v);
            }
            post_re.push_back(start);
        }
    }
    void dfs_re(){
        for (int i=0;i<V;i++){
            explore_re(i);
        }
    }
    void explore(int start){
        if (!visited[start]){
            visited[start] = true;
            for (auto v: G[start]){
                if (!visited[v]) explore(v);
            }
            buff.push_back(start);
        }
    }
    void dfs(){
        for (auto v: post){
            if (!visited[v]) explore(v);
            if (buff.size()>0) scc.push_back(buff);
            buff.clear();
        }
    }
    void findSCC(){
        dfs_re();
        reverse(post_re.begin(), post_re.end());
        post= post_re;
        dfs();
        cout << scc.size() << '\n';
        for (int i=scc.size()-1;i>=0;i--){
            if (scc[i].size() > 0) cout << scc[i].size() << ' ';
            for (auto v: scc[i]){
                cout << v << ' ';
            }
            cout << '\n';
        }
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("inp.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int N,M;
    cin >> N >> M;
    DirectedGraph g(N);
    for (int i=0;i<M;i++){
        int a,b;
        cin >> a >>b;
        if (a!=b) g.addEdge(a,b);
    }
    g.findSCC();
}