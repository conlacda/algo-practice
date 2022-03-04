// https://www.spoj.com/problems/QTREE/
#include<bits/stdc++.h>
 
typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
 
using namespace std;
 
// Copy from nealwu's template - http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }
 
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
 
// Reference: https://cp-algorithms.com/graph/lca.html - toÃ n bá»� source code implement theo hÆ°á»�ng dáº«n
// Verification: https://www.spoj.com/status/LCA,hoanglongvn/
struct Euler{
    int vertex, height, index;
};
class LCA{
    // Verification: https://atcoder.jp/contests/practice2/submissions/25073318
    template<typename T>
    class LCASegmentTree {
        private:
            ll n;
            vector<T> dat;
        public:
            T merge(T a, T b){
                if (a.height > b.height) return b;
                return a;
            }
            LCASegmentTree(vector<T> v) {
                int _n = v.size();
                n = 1;
                while (n < _n)n *= 2;
                dat.resize(2 * n - 1);
                for (int i=0;i<_n;i++) dat[n + i - 1] = v[i];
                for (int i = n - 2; i >= 0; i--)dat[i] = merge(dat[i * 2 + 1], dat[i * 2 + 2]);
            }
            LCASegmentTree(int _n) {
                n = 1;
                while (n < _n)n *= 2;
                dat.resize(2 * n - 1);
            }
            void set_val(int i, T x) {
                i += n - 1;
                dat[i] = x;
                while (i > 0) {
                    i = (i - 1) / 2;
                    dat[i] = merge(dat[i * 2 + 1], dat[i * 2 + 2]);
                }
            }
            T query(int l, int r){
                r++;
                T left = T{INT_MAX, INT_MAX, INT_MAX}, right = T{INT_MAX, INT_MAX, INT_MAX};
                l += n - 1; r += n - 1;
                while (l < r) {
                    if ((l & 1) == 0)left = merge(left, dat[l]);
                    if ((r & 1) == 0)right = merge(dat[r - 1], right);
                    l = l / 2;
                    r = (r - 1) / 2;
                }
                return merge(left, right);
            }
            // Custom
            T query(int l){
                return query(l, l);
            }
            void add(int i, T x){
                set_val(i, query(i) + x);
            }
    };
    /*
    LÆ°u Ã½: dÃ²ng T left = 0, right = 0; náº¿u merge lÃ  hÃ m min() thÃ¬ chuyá»�n vá»� LLONG_MAX. Má»¥c Ä�Ã­ch lÃ  Ä�á»� ko lÃ m áº£nh hÆ°á»�ng tá»�i cÃ¢y khi báº¯t Ä�áº§u vÃ o hÃ m while
    Tham kháº£o: https://cses.fi/problemset/result/2691498/
    vector<ll> a(n);
    LCASegmentTree<ll> seg(a);
    seg.set_val(index, value);
    seg.query(start, end); //[start, end]
    seg.query(start, start); // start
    */
public:
    int n;
    vector<vector<int>> graph;
    vector<bool> visited;
    vector<Euler> eulertour;
    vector<Euler> first;
    LCASegmentTree<Euler> *seg;
    LCA(vector<vector<int>> graph){
        this->graph = graph;
        this->n = graph.size();
        visited.resize(n);
        first.resize(n);
        this->makeEuler();
    }
 
    // Euler tour of tree
    void makeEuler(int root = 0){
        // Euler tour táº¡o ra verticies, heights, index
        std::fill(visited.begin(), visited.end(), false);
        int height =0;
        auto explore = y_combinator([&] (auto explore, int u) -> void {
                visited[u] = true;
                height++;
                eulertour.push_back(Euler{u, height, (int) eulertour.size()});
                for (auto v: this->graph[u]){
                    if (!visited[v]) {
                        explore(v);
                        height--;
                        eulertour.push_back(Euler{u, height, (int) eulertour.size()});
                    }
                }
        });
        explore(root);
        // Táº¡o ra máº£ng first
        std::fill(visited.begin(), visited.end(), false);
        for (auto e: eulertour){
            if (!visited[e.vertex]){
                visited[e.vertex] = true;
                first[e.vertex] = e;
            }
        }
        // Táº¡o 1 segment tree Ä�á»� query trÃªn máº£ng height
        this->seg = new LCASegmentTree<Euler>(eulertour);
    }
 
    int lca(int u, int v){
        int uidx = first[u].index;
        int vidx = first[v].index;
        if (uidx > vidx) swap(uidx, vidx);
        Euler a = seg->query(uidx, vidx);
        return a.vertex;
    }
    vector<int> height(){
        vector<int> h(this->n, 0);
        for (auto e: eulertour){
            h[e.vertex] = e.height;
        }
        return h;
    }
};
/*
LÆ°u Ã½: LCA cháº¡y vá»�i 1 SCC, náº¿u cÃ³ nhiá»�u SCC thÃ¬ pháº£i dÃ¹ng DSU check trÆ°á»�c. 
Náº¿u 2 node ko cÃ¹ng 1 cÃ¢y cÃ³ thá»� gÃ¢y ra lá»�i
*/
 
template<typename T>
class SegmentTree {
private:
    ll n;
    vector<T> dat;
public:
    T merge(T a, T b){
        // CHANGE HERE
        return max(a, b); // easily modify to another function like sum()
    }
    SegmentTree(vector<T> v) {
        int _n = v.size();
        n = 1;
        while (n < _n)n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<_n;i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)dat[i] = merge(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
    SegmentTree(int _n) {
        n = 1;
        while (n < _n)n *= 2;
        dat.resize(2 * n - 1);
    }
    void set_val(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat[i] = merge(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    T query(int l, int r){
        r++;
        T left = 0, right = 0;
        l += n - 1; r += n - 1;
        while (l < r) {
            if ((l & 1) == 0)left = merge(left, dat[l]);
            if ((r & 1) == 0)right = merge(dat[r - 1], right);
            l = l / 2;
            r = (r - 1) / 2;
        }
        return merge(left, right);
    }
    // Custom
    T query(int l){
        return query(l, l);
    }
    void add(int i, T x){
        set_val(i, query(i) + x);
    }
};
 
// Reference: https://cp-algorithms.com/graph/hld.html
// Verification: https://cses.fi/problemset/result/3568717/
//               https://cses.fi/problemset/result/3573305/
class HeavyLightDecomposition{
public:
    int n;
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    vector<int> pos_to_vertex; // vá»�i Ä�á»�nh u -> pos[u] + 1 lÃ  Ä�á»�nh tiáº¿p theo Ä�Æ°á»£c duyá»�t. -> pos_to_vertex[pos[u]+1] ra id cá»§a Ä�á»�nh káº¿ tiáº¿p u
    // dá»±a vÃ o Ä�Ã³ sáº½ láº¥y Ä�Æ°á»£c vá»� trÃ­ phÃ­a dÆ°á»�i trong chain (subtree) - táº¡m hiá»�u lÃ  child
    
    HeavyLightDecomposition(vector<vector<int>> adj) {
        this->n = adj.size();
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 0;
        // Recursive lambda function
        auto dfs = y_combinator([&] (auto dfs, int v) -> int {
            int size = 1;
            int max_c_size = 0;
            for (int c : adj[v]) {
                if (c != parent[v]) {
                    parent[c] = v, depth[c] = depth[v] + 1;
                    int c_size = dfs(c);
                    size += c_size;
                    if (c_size > max_c_size)
                        max_c_size = c_size, heavy[v] = c;
                }
            }
            return size;    
        });
    
        auto decompose = y_combinator([&] (auto decompose, int v, int h) -> void {
            head[v] = h, pos[v] = cur_pos++;
            if (heavy[v] != -1)
                decompose(heavy[v], h);
            for (int c : adj[v]) {
                if (c != parent[v] && c != heavy[v])
                    decompose(c, c);
            }
        });
        // 2 hÃ m nÃ y sáº½ tÃ­nh toÃ¡n toÃ n bá»� cÃ¡c vector<int> parent, depth, heavy, head, pos;
        dfs(0);
        decompose(0, 0);
        // Tá»« pos láº¥y ra Ä�á»�nh. Hiá»�n táº¡i máº£ng pos[vertex] = value => táº¡o ra map[value] = vertex 
        auto mappos_to_value = [&] () -> void {
            pos_to_vertex.resize(this->n);
            for (int v=0;v<pos.size();v++){
                pos_to_vertex[pos[v]] = v;
            }   
        };
        mappos_to_value();
        // dbg(parent); dbg(depth); dbg(heavy); dbg(head); dbg(pos);dbg(pos_to_vertex);
    }
    // Path tá»« nÃºt con tá»�i LCA. vá»�i 2 nÃºt u, v báº¥t ká»³: path(u, v) = path(u, lca(u,v)) + path(v, lca(u, v))
    vector<pair<int,int>> path(int u, int p){
        // assert(lca(u, p) == u || lca(u,p) == p)
        vector<pair<int,int>> pth; // path
        while (head[p] != head[u]){
            pth.push_back({u, head[u]});
            u = parent[head[u]]; // cháº¡y tá»« u tá»�i Ä�iá»�m Ä�áº§u substree rá»�i láº¥y parent sáº½ ra Ä�iá»�m cuá»�i cá»§a subtree cha
        }
        // CHANGE HERE - Ä�á»� im náº¿u trá»�ng sá»� náº±m trÃªn cáº¡nh. Trá»�ng sá»� Ä�á»�nh thÃ¬ sá»­ dá»¥ng Ä�oáº¡n code dÆ°á»�i
        // Loáº¡i bá»� Ä�iá»�m p ra khá»�i path - vÃ¬ weight cá»§a u->p Ä�Ã£ cháº¡y vá»� u nÃªn chá»� giá»¯ láº¡i u
        if (u!=p){
            int pp = pos[p]; // pp+1=> Ä�iá»�m tiáº¿p theo trong chu trÃ¬nh 
            pth.push_back({u, pos_to_vertex[pp+1]});
        }
        // pth.push_back({u, p}); 
        return pth;
    }
 
    SegmentTree<int> *seg;
    void buildSegTree(vector<int> weight){ // w nÃ y náº±m trÃªn Ä�á»�nh. náº¿u náº±m trÃªn cáº¡nh thÃ¬ chuyá»�n qua Ä�á»�nh phÃ­a dÆ°á»�i edge(u,v) chá»�n u vá»�i u lÃ  con v
        // pos[] lÆ°u vá»� trÃ­ cá»§a cÃ¡c node theo thá»© tá»± duyá»�t. Duyá»�t trong 1 khá»�i (subtree, chain) -> duyá»�t tá»« khá»�i nÃ y ná»�i sang khá»�i khÃ¡c
        vector<int> wvt(n); // weight of verticies - lÃ m pháº³ng tree ra dáº¡ng [[chain1][chain2][...]...]
        // khi nÃ y muá»�n query(u, v) thÃ¬ sáº½ chia ra [u..->tailu][...][headv..->v] rá»�i query tá»«ng khÃºc 1
        for (int i=0;i<n;i++) wvt[pos[i]] = weight[i]; // lÃ m pháº³ng cÃ¢y ra thÃ nh 1 máº£ng vá»�i cÃ¡c Ä�oáº¡n segment ná»�i tiáº¿p nhau
        this->seg = new SegmentTree<int>(wvt);
    }
 
    int query(int u, int p){
        // assert(lca(u,p) == u || lca(u,p) == v)
        vector<pair<int,int>> pathu = path(u, p);
        int ans = 0; // lÆ°u Ã½ trÆ°á»�ng há»£p u=p vá»�i weight trÃªn cáº¡nh sáº½ ko cÃ³ path u->u do bá»� cáº¯t Ä�áº§u. NÃªn ans sáº½ ko thay Ä�á»�i váº«n = 0
        for (auto chain: pathu){
            // CHANGE HERE max() to any function
            ans = max(ans, seg->query(pos[chain.second], pos[chain.first])); // chain lÆ°u cÃ¡c Ä�á»�nh. chuyá»�n cÃ¡c Ä�á»�nh Ä�Ã³ vá»� vá»� trÃ­ trong seg thÃ¬ = pos[u]
        }
        return ans;
    }
 
    void set_val(int u, int val){
        seg->set_val(pos[u], val);
    }
};
/*
vector<vector<int>> adj(N); adj[u].push_back(v); adj[v].push_back(u);
HeavyLightDecomposition hld(adj);
 
vector<int> w(N); // weight táº¡i Ä�Ã¢y chÃ­nh lÃ  trá»�ng sá»� cá»§a Ä�á»�nh Ä�Ã³.
// Náº¿u trá»�ng sá»� trÃªn Edge(u,v) thÃ¬ chuyá»�n w vá»� cho Ä�á»�nh con trong 2 Ä�á»�nh u,v (cÃ³ thá»� so sÃ¡nh depth)
hld.buildSegTree(w);
 
LCA lca(adj);
hld.query(u, lca.lca(u, v)); hld.query(v, lca.lca(u,v));
 
==========================
Náº¿u trá»�ng sá»� náº±m trÃªn cáº¡nh cáº§n chuyá»�n trá»�ng sá»� vá»� cho Ä�á»�nh 
// trong hÃ m main adj_w lÃ  vector<vector<pair<int (v), int (w)>>> adj_w;
//                adj lÃ  vector<vector<int>> loáº¡i bá»� w tá»« adj_w
LCA lca(adj);
vector<int> height = lca.height();
// Ä�áº©y háº¿t trá»�ng sá»� cáº¡nh sang cho node con
vector<int> weight(N, -1);
for (int i=0;i<adj_w.size();i++){
    for (auto vw: adj_w[i]){
        int v = vw.first, w = vw.second;
        if (height[i] > height[v]) weight[i] = w;
        else weight[v] = w;
    }
}
HeavyLightDecomposition hld(adj); // khá»�i táº¡o vá»�i adj ko weight
hld.buildSegTree(weight); // build segtree cÃ³ weight sau khi Ä�Ã£ khá»�i táº¡o
*/
void solve(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<vector<pair<int,int>>> adj_w(n);
    vector<pair<int,int>> seq;
    for (int i=0;i<n-1;i++){
        int u, v, w;
        cin >> u>>v>>w; u--; v--;
        adj[u].push_back(v); adj[v].push_back(u);
        adj_w[u].push_back({v, w}); adj_w[v].push_back({u, w});
        seq.push_back({u, v});
    }
    LCA lca(adj);
    vector<int> height = lca.height();
    HeavyLightDecomposition hld(adj);
    vector<int> weight(n, -1);
    for (int i=0;i<adj_w.size();i++){
        for (auto vw: adj_w[i]){
            int v = vw.first, w = vw.second;
            if (height[i] > height[v]) weight[i] = w;
            else weight[v] = w;
        }
    }
    hld.buildSegTree(weight);
    // Query
    while (true){
        string s; 
        cin >> s;
        if (s == "DONE") return;
        int u, v; cin >> u >> v; u--;
        if (s == "QUERY"){
            v--;
            int p = lca.lca(u, v);
            cout << max(hld.query(u, p), hld.query(v, p)) <<'\n';
        }
        else {
            // Update
            int p1 = seq[u].first;
            int p2 = seq[u].second;
            if (height[p1] > height[p2]){
                hld.set_val(p1, v);
            }
            else hld.set_val(p2, v);
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
    int N;
    cin >> N;
    while (N--) solve();
}