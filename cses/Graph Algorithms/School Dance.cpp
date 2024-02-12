// https://cses.fi/problemset/task/1696/
#include<bits/stdc++.h>
 
typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
 
using namespace std;
 
// Copy from nealwu's template - http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result { Fun fun_; public:template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {} template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }}; template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }
 
#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif
 
ll m, f, q;
/*
** Dinic's algorithm for maximum flow problem
** Explain video: https://www.youtube.com/watch?v=duKIzgJQ1w8&ab_channel=FitCoder
** Reference: https://github.com/fit-coder/fitcoderyoutube/blob/master/graph/dinic_algorithm.cpp
** Graph Playlist: https://youtube.com/playlist?list=PLFj4kIJmwGu3m30HfYDDufr3PZBfyngr0
** Complexity: O(E*V*V)
*/
class Dinic_Maxflow{
private:
	ll n;
	vector<vector<ll>> graph;
	vector<vector<ll>> residualGraph;
	vector<ll> level, count_;
public:
	Dinic_Maxflow(vector<vector<ll>> graph){
		this->graph = graph;
		this->n = graph.size();
		level.resize(n, -1);
		count_.resize(n, 0);
	}
	bool bfs(ll source, ll sink) // on residualGraph
	{
	    fill(level.begin(), level.end(), -1);
	    level[source] = 0;
	    
	    queue<ll> q;
	    q.push(source);
	 
	    while (!q.empty())
	    {
	        ll u = q.front();
	        q.pop();
	        for (ll v=0; v < n; v++)
	        {
	            if (u != v && residualGraph[u][v] > 0 && level[v] < 0)
	            {
	                // Level of current vertex is level of parent + 1
	                level[v] = level[u] + 1;
	                q.push(v);
	            }
	        }
	    }
	    // IF we can not reach to the sink we
	    // return false else true
	    return level[sink] < 0 ? false : true ;
	}
 
	ll sendFlow(ll u, ll sink, ll flow){ // on residualGraph
	    // Sink reached
	    if (u == sink)
	        return flow;
	 
	    if (count_[u] == (ll) residualGraph[u].size())
	        return 0;
	 
	    // Traverse all adjacent edges one-by-one.
	    for (ll v=0; v < n; v++)
	    {
	        if (residualGraph[u][v] > 0)
	        {
	            count_[u]++;
	            if (level[v] == level[u]+1)
	            {
	                // find minimum flow from u to sink
	                ll curr_flow = min(flow, residualGraph[u][v]);
	 
	                ll min_cap = sendFlow(v, sink, curr_flow);
	                if (min_cap > 0){
	                    residualGraph[u][v] -= min_cap;
	                    residualGraph[v][u] += min_cap;
	                    return min_cap;
	                }
	            }
	        }
	    }
	    return 0;
	}
 
	vector<pair<ll, ll>> mincut_edges;
	ll max_flow(ll source, ll sink){
	    if (source == sink)
	        return -1;
	 
	    ll max_flow = 0;
	    residualGraph = graph;
	 
	    // Augment the flow while there is path from source to sink
	    while (bfs(source, sink) == true){
	        // store how many neighbors are visited
	        fill(count_.begin(), count_.end(), 0);
	 
	        // while flow is not zero in graph from source to sink
	        while (ll flow = sendFlow(source, sink, LLONG_MAX))
	            max_flow += flow;
	    }
	    cout << max_flow <<'\n';
	    dbg(m, f);
	    for (ll i=0;i<m;i++){
	    	for (ll j=0;j<f;j++){
	    		if (residualGraph[i+2][m+2+j] == 0 && graph[i+2][m+2+j] == 1){
	    			cout << i+1<<' ' << j+1<<'\n';
	    		}
	    	}
	    }
	    return max_flow;
	}
};
/*
Thuật toán này copy nên mình ko hiểu về cách nó hoạt động. Lưu ý graph là 1 bảng n*n nên n thường khá nhỏ <= 1000
vector<vector<ll>> graph(n, vector<ll> (n, 0));
graph[u][v] = c; // += c nếu nó cho phép u->v có nhiều đường
Dinic_Maxflow dinic(graph);
cout << dinic.max_flow(start, end);
dbg(dinic.mincut_edges); // verification submission: https://cses.fi/problemset/result/4275176/
*/
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
    #endif
	// cout << setprecision(2);
	
	cin >> m>> f>> q;
	ll n = 2+m+f;
	vector<vector<ll>> graph(n, vector<ll>(n, 0));
	for (ll i=0;i<m;i++)
		graph[0][2+i] = 1;
	for (ll i=0;i<f;i++){
		graph[2+m+i][1] = 1;
	}
	for (ll i=0;i<q;i++){
		ll u, v; cin >> u>> v; u--; v--;
		graph[u+2][2+m+v] = 1;
	}
	Dinic_Maxflow dinic(graph);
	dinic.max_flow(0, 1);
	cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}