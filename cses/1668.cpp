/*
https://cses.fi/problemset/task/1668/
Sử dụng duyệt DFS()
Mỗi khi duyệt tới 1 node thì đánh dấu số team cho nó (mặc định là 1)
Nếu node u được duyệt graph[u] = [v,...]. Có team[u]==team[v] -> ko thỏa mãn
còn nếu ko thì đánh dấu u =1 thì v=2, u=2 => v=1
*/
#include<bits/stdc++.h>

using namespace std;

int n, v;
vector<int> team;
vector<vector<int>> g;
vector<bool> visited;
bool impossible = false;
void explore(int u){
	if (!visited[u]){
		visited[u] = true;
		if (team[u] == 0) team[u] = 1;
		for (int i=0;i<g[u].size();i++){
			if (!visited[g[u][i]]){
				if (team[u] == 1){
					team[g[u][i]] = 2;
				} else team[g[u][i]] = 1;
				explore(g[u][i]);
			} else if (team[u] == team[g[u][i]]){
				impossible = true;
			}
		}
	}
}
void dfs(){
	for(int i=0;i<n;i++){
		explore(i);
	}
}

int main(){
	// freopen("inp.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	cin >> n >>v;

	for (int i=0;i<=n;i++){
		team.push_back(0);
		vector<int> x={};
		g.push_back(x);
		visited.push_back(false);
	}
	for(int i=0;i<v;i++){
		int a,b;
		cin >> a >>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs();
	if (!impossible){
		for (int i=1;i<team.size();i++){
			cout << team[i] << ' ';
		}
	} else {
		cout << "IMPOSSIBLE";
	}
}
