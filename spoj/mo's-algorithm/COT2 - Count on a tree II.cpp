// https://www.spoj.com/problems/COT2/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif

template<typename T>
struct Compress {
    vector<T> rcv; // recover - giá trị mảng ban đầu đã sort và xóa unique
    vector<T> cpr; // compressed - giá trị đã nén của mảng a
    Compress() {}
    Compress(vector<T> v) { build(v);}
    void build(vector<T> v) {
        rcv = v;
        sort(rcv.begin(), rcv.end());
        rcv.resize(unique(rcv.begin(), rcv.end()) - rcv.begin());

        cpr = v;
        for (int i = 0; i < (int) cpr.size(); ++i) {
            cpr[i] = lower_bound(rcv.begin(), rcv.end(), cpr[i]) - rcv.begin(); // O(logN) thay cho map
        }
    }
    T compressed_val(T originalVal) { // giá trị ban đầu sang giá trị đã compress
        T i = lower_bound(rcv.begin(), rcv.end(), originalVal) - rcv.begin();
        if (rcv[i] != originalVal) return -1;
        return i;
    }
    T compressed_val_by_index(T index) {
        return cpr[index];
    }
    ll recover(T compressedVal) {
        return rcv[compressedVal];
    }
};

const ll blockSize = 300; // 300, 700

struct Query {
    ll l, r, index;
    friend bool operator<(Query a, Query b) {
        // những cái thuộc cùng 1 block sẽ đứng cạnh nhau, những cái cùng block thì r sẽ xếp từ bé tới lớn
        if (a.l/blockSize == b.l/blockSize) return a.r < b.r;
        return a.l/blockSize < b.l/blockSize;
    }
    friend std::ostream& operator<<(std::ostream& os, const Query &s) { return os << destructure(s);}
};
struct Ans {
    ll index, val;
    friend bool operator<(Ans a, Ans b) {
        return a.index < b.index;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ans &s) { return os << destructure(s);}
};

struct MoOnTree {
private:
    template<typename LL>class LCA{struct Euler{LL vertex, height, index;};template<typename T>class LCASegmentTree{private:ll n;vector<T>dat;public:T merge(T a,T b){if(a.height>b.height)return b;return a;}LCASegmentTree(vector<T>v){int _n=v.size();n=1;while(n<_n)n*=2;dat.resize(2*n-1);for(int i=0;i<_n;i++)dat[n+i-1]=v[i];for(int i=n-2;i>=0;i--)dat[i]=merge(dat[i*2+1],dat[i*2+2]);} LCASegmentTree(int _n){n=1;while(n<_n)n*=2;dat.resize(2*n-1); } void set_val(int i,T x){i+=n-1;dat[i]=x;while(i>0){i=(i-1)/2;dat[i]=merge(dat[i*2+1],dat[i*2+2]);}}T query(int l,int r){r++;T left=T{INT_MAX,INT_MAX,INT_MAX},right=T{INT_MAX,INT_MAX,INT_MAX};l+=n-1;r+=n-1;while(l<r){if((l&1)==0)left=merge(left,dat[l]);if((r&1)==0)right=merge(dat[r-1],right);l=l/2;r=(r-1)/2;}return merge(left,right);}};public:int n;vector<vector<LL>> graph;vector<bool> visited;vector<Euler> eulertour, first;LCASegmentTree<Euler> *seg;LCA() {}LCA(vector<vector<LL>> graph, LL root = 0){build(graph, root);}void build(vector<vector<LL>> graph, LL root = 0) {this->graph = graph;n = graph.size();visited.resize(n);first.resize(n);makeEuler(root);}void makeEuler(LL root){std::fill(visited.begin(), visited.end(), false);int height =0;std::function<void(int)> explore = [&](int u){visited[u] = true;height++;eulertour.push_back(Euler{u, height, (int) eulertour.size()});for (auto v: this->graph[u]){if (!visited[v]) {explore(v);height--;eulertour.push_back(Euler{u, height, (int) eulertour.size()});}}};explore(root);std::fill(visited.begin(), visited.end(), false);for (auto e: eulertour){if (!visited[e.vertex]){visited[e.vertex] = true;first[e.vertex] = e;}}this->seg = new LCASegmentTree<Euler>(eulertour);}LL lca(LL u, LL v){LL uidx = first[u].index;LL vidx = first[v].index;if (uidx > vidx) swap(uidx, vidx);Euler a = seg->query(uidx, vidx);return a.vertex;}vector<LL> height(){vector<LL> h(this->n, 0);for (auto e: eulertour) h[e.vertex] = e.height;return h;}LL lca(LL r, LL u, LL v){LL ru = lca(r, u);LL rv = lca(r, v);LL uv = lca(u, v);if (ru == rv) return uv;if (ru == uv) return rv;return ru;}};
    std::vector<ll> first, second, eulertour;
    vector<ll> makeEulerTour(vector<vector<ll>> adj) {
        vector<ll> eulertour;
        first.resize(n); second.resize(n); // first[v] - thời điểm duyệt v, second[v] - thời điểm ra khỏi v
        ll clock = 0;
        std::function<void(ll, ll)> dfs = [&](ll u, ll p){
            eulertour.push_back(u);
            first[u] = clock++;
            for (auto v: adj[u]) {
                if (v != p) dfs(v, u);
            }
            second[u] = clock++;
            eulertour.push_back(u);        
        };
        dfs(0, 0);
        return eulertour;
    }
    // Chuyển query trên node sang query trên euler tour
    vector<Query> fromEdgeToEuler(vector<Query> queries) {
        vector<Query> res;
        for (auto q: queries) {
            ll u = q.l, v= q.r, idx = q.index;
            if (first[u] > first[v]) swap(u, v); 
            if (lca.lca(u, v) == u) {
                // first(u) -> first(v) (má trái)
                res.push_back(Query{first[u], first[v], idx});
            } else {
                // second(u) -> first(v)
                res.push_back({second[u], first[v], idx});
            }
        }
        return res;
    }
public:
    ll n;
    vector<ll> weight;
    vector<Query> queries; // l, r, index
    LCA<ll> lca;
    vector<bool> vis; // đánh dấu số lần đỉnh đó đã đi qua
    vector<ll> data; // lưu trạng thái hiện tại - lưu tần số của từng số có trong range [left, right] hiện tại
    vector<Ans> ans; // index, val
    ll cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    MoOnTree(vector<vector<ll>> adj, vector<ll> weight) {
        this->n = (ll) adj.size();
        this->weight = weight;
        data.resize(this->n, 0);
        lca.build(adj);
        eulertour = makeEulerTour(adj);
        vis.resize(n, false);
    }

    void add(ll index) {
        ll edge = eulertour[index];
        if (data.at(weight.at(edge)) == 0) cur_result++;
        data[weight[edge]]++;
    }
    void remove(ll index) {
        ll edge = eulertour[index];        
        if (data[weight[edge]] == 1) cur_result--;
        data[weight[edge]]--;

    }
    void resolve(ll index) {
        ll edge = eulertour[index];
        vis[edge] = !vis[edge]; // vis 1 lần thì nó nằm trên đoạn, 2 lần thì nó nằm ngoài đoạn
        if (!vis[edge]) remove(index); else add(index);
    }
    void solve(vector<Query> qrs) {
        queries = fromEdgeToEuler(qrs);
        sort(queries.begin(), queries.end());
        ll cur_l = 0, cur_r = -1;
        for (auto query: queries) {
            while (cur_l > query.l) resolve(--cur_l);
            while (cur_r < query.r) resolve(++cur_r);
            while (cur_l < query.l) resolve(cur_l++);
            while (cur_r > query.r) resolve(cur_r--);
            // Xét tới lca.lca(u, v)
            ll p = lca.lca(eulertour[query.l], eulertour[query.r]);
            if (!vis[p]) {
                add(first[p]);
                ans.push_back({query.index, cur_result});
                remove(first[p]);
            } else {
                ans.push_back({query.index, cur_result});
            }
        }
        sort(ans.begin(), ans.end());
        for (auto v: ans) cout << v.val <<'\n';
    }
};
/*
Mo mo(a, queries);
mo.solve();
for (auto v: mo.ans) cout << v << ' ';
*/
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto &v: a) cin >> v;
    Compress<ll> c(a);
    vector<ll> weight = c.cpr;
    vector<vector<ll>> g(n);
    for (ll i=0;i<n-1;i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }
    vector<Query> queries;
    for (ll i=0;i<q;i++) {
        ll u, v; cin >> u >> v; u--; v--;
        queries.push_back(Query{u, v, i});
    }
    MoOnTree mo(g, weight);
    mo.solve(queries);
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
