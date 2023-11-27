// https://codeforces.com/gym/100962 - Frank Sinatra
// Tag: Mo on tree
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
#define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif

template <typename T>
struct FenwickTree {
private:
    vector<T> bit; // binary indexed tree
    T n;
public:
    FenwickTree(){}
    void build(T n) { this->n = n; bit.assign(n, 0); }
    void build(vector<T> a) { build(a.size()); for (int i = 0; i < (int) a.size(); i++) add(i, a[i]); }
    FenwickTree(vector<T> a) { build(a); }
    T sum(T r) {
        if (r==-1) return 0;
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
        return ret;
    }

    T sum(T l, T r) {
        assert(0 <= l && l <= r && r < n);
        return sum(r) - sum(l-1);
    }

    void add(T idx, T delta) {
        assert(0 <= idx && idx < n);
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
    }
    void set(T idx, T val) {
        T diff = val - sum(idx, idx);
        add(idx, diff);
    }

    vector<T> original(){ // Return original value of input vector
        vector<T> a;
        for (T i=0;i<this->n;i++) a.push_back(sum(i,i));
        return a;
    }
};

template<typename T>
vector<T> depth_on_tree(vector<vector<T>> tree) {
    vector<T> depth((ll) tree.size(), 0);
    std::function<void(T, T)> dfs = [&](T u, T p){
        for (auto v: tree.at(u)) {
            if (v!= p) {
                depth.at(v) = depth.at(u) + 1;
                dfs(v, u);
            }
        }
    };
    dfs(0, 0);
    return depth;
}

const ll blockSize = 500; // 300, 700

struct Query {
    ll l, r, index;
    friend bool operator<(Query a, Query b) {
        if (a.l / blockSize != b.l / blockSize)
            return a.l < b.l;
        return (a.l / blockSize & 1) ? (a.r < b.r) : (a.r > b.r);
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
    ll bound;
    FenwickTree<ll> fw;
    MoOnTree(vector<vector<ll>> adj, vector<ll> weight) {
        this->n = (ll) adj.size();
        this->weight = weight;
        lca.build(adj);
        eulertour = makeEulerTour(adj);
        vis.resize(n, false);
        bound = calBound();
        fw.build(bound);
        data.resize(bound, 0);
    }
    ll calBound() {
        vector<ll> w = this->weight;
        sort(w.begin(), w.end());
        dbg(w);
        ll bound = 0;
        for (int i=0;i<(int) w.size();i++) {
            if (bound == w[i]) continue;
            bound++;
            if (bound != w[i]) break;
        }

        // Xóa đi các phần tử lớn hơn bound
        for (int i=0;i<(int) this->weight.size();i++) {
            if (this->weight[i] > bound) this->weight[i] = -1;
        }
        return bound;
    }

    void add(ll index) {
        ll edge = eulertour[index];
        ll w = weight[edge];
        if (w != -1) { // -1 bỏ qua vì lớn hơn bound
            data[w]++;
            fw.set(w, 1);
        }
    }
    void remove(ll index) {
        ll edge = eulertour[index];
        ll w = weight[edge];
        if (w != -1) {
            data[w]--;
            if (data[w] == 0) fw.set(w, 0);
        }
    }
    void resolve(ll index) {
        ll edge = eulertour[index];
        vis[edge] = !vis[edge]; // vis 1 lần thì nó nằm trên đoạn, 2 lần thì nó nằm ngoài đoạn
        if (!vis[edge]) remove(index); else add(index);
    }
    ll getResult() {
        ll left=0, right= this->bound-1;
        while (left != right) {
            ll mid = (left+right)/2;
            if (fw.sum(mid) != mid+1) right = mid;
            else left = mid + 1;
        }
        if (fw.sum(left) == left +1) return left+1;
        return left;        
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
            if (vis[p]) {
                remove(first[p]);
                ans.push_back({query.index, getResult()});
                add(first[p]);
            } else {
                ans.push_back({query.index, getResult()});
            }
        }
        sort(ans.begin(), ans.end());
        for (auto v: ans) cout << v.val <<'\n';
    }
};
/*
MoOnTree mo(graph, weight_on_node);
mo.solve(vector<Query> queries);
Các hàm cần thay đổi để fit với từng bài: resolve(), add(), remove() và đoạn xét lca(u, v)
*/

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> adj(n);
    vector<vector<pair<ll,ll>>> adj_w(n);
    for (ll i=0;i<n-1;i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        adj_w[u].push_back({v, w});
        adj_w[v].push_back({u, w});
    }
    // chuyển trọng số từ cạnh xuống node bên dưới
    vector<ll> depth = depth_on_tree<ll>(adj);
    vector<ll> weight(n, LLONG_MAX);
    for (ll i=0;i<n;i++) {
        for (auto uv: adj_w[i]) {
            if (depth[i] > depth[uv.first]) {
                weight[i] = uv.second;
            } else weight[uv.first] = uv.second;
        }
    }

    /*
    Dựng Mo's on tree -
    tìm ra số nhỏ nhất bị rỗng trong đó
    đối với phần còn lại thì dùng binary search để tìm ra, binary search với fenwicktree
    */
    vector<Query> queries;
    for (ll i=0;i<q;i++) {
        ll l, r; cin >> l >> r;
        queries.push_back({--l, --r, i});
    }
    MoOnTree mo(adj, weight);
    mo.solve(queries);

    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Bài toán có 2 yêu cầu:
* Tìm số nhỏ nhất không tồn tại trong range
* Query trên tree

Query trên tree sẽ được giải quyết khi dùng MoOnTree
Phần quan tâm lúc này là tìm số nhỏ nhất không xuất hiện trong mảng
Giả sử mảng 0, 1, 1, 2, 5, 4 có số nhỏ nhất không xuất hiện là 3
Observation 1: số cần tìm luôn nhỏ hơn hoặc bằng 3 cho dù hiện tại có số nào đi chăng nữa
-> có 4,5 hay không có 4,5 đều không ảnh hưởng tới kết quả
-> tìm ra bound = 3 -> mọi số lớn hơn 3 biến hết thành -1 và trong quá trình duyệt,
mọi số -1 đều không cần quan tâm. 
Observation 2: độ dài vector lớn nhất là 10^5, giá trị tới 10^9 nhưng bound sẽ luôn <=10^5.
Do các phần tử lớn hơn bound đều bị xóa bỏ.
Khi này bài toán đưa về dạng:
cho dãy a có 10^5 phần tử và giá trị các phần tử từ 0->10^5
Dùng fenwicktree kết hợp với binary search.
fenwicktree check xem giá trị x có xuất hiện trong mảng hay không.
a = [1, 1, 1, 0, 1, 1] 1 là có, 0 là không, index chính là giá trị.
data trong Mo sẽ duy trì tần số xuất hiện của weight đó.
Khi data[w] = 0 thì fw.set(w, 0) còn không thì fw.set(w, 1)
Dùng binary search sẽ tìm ra được vị trí số 0 đầu tiên xuất hiện đó chính là giá trị 
cần tìm.

Bài này dùng technique giống như HLD, đó là đẩy weight từ cạnh xuống đỉnh bên dưới.
Khi đẩy cạnh xuống đỉnh bên dưới xét 2 type query (má trái, má phải).
Trong video tự quay mình cũng có đề cập.
Má trái sẽ là first->first.
Má phải là second ->first.
Bình thường má phải cần được xét riêng lca.
Nhưng tại đây má trái first->first thì đỉnh lca đã được tính nhưng không nằm trên đoạn nên ở đoạn // Xét tới lca.lca(u, v) đã remove rồi lấy giá trị rồi add lại
*/
