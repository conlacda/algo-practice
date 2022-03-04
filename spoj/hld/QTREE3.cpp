// https://www.spoj.com/problems/QTREE3/
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

#ifdef DEBUG
    #include"debug.cpp"
#endif

class LCA{
    struct Euler{
        int vertex, height, index;
    };
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
        // Euler tour tạo ra verticies, heights, index
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
        // Tạo ra mảng first
        std::fill(visited.begin(), visited.end(), false);
        for (auto e: eulertour){
            if (!visited[e.vertex]){
                visited[e.vertex] = true;
                first[e.vertex] = e;
            }
        }
        // Tạo 1 segment tree để query trên mảng height
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

template<typename T>
class SegmentTree {
private:
    ll n;
    vector<T> dat;
public:
    T merge(T a, T b){
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

class HeavyLightDecomposition{
public:
    int n;
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    vector<int> pos_to_vertex; // với đỉnh u -> pos[u] + 1 là đỉnh tiếp theo được duyệt. -> pos_to_vertex[pos[u]+1] ra id của đỉnh kế tiếp u
    // dựa vào đó sẽ lấy được vị trí phía dưới trong chain (subtree) - tạm hiểu là child
    
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
        // 2 hàm này sẽ tính toán toàn bộ các vector<int> parent, depth, heavy, head, pos;
        dfs(0);
        decompose(0, 0);
        // Từ pos lấy ra đỉnh. Hiện tại mảng pos[vertex] = value => tạo ra map[value] = vertex 
        auto mappos_to_value = [&] () -> void {
            pos_to_vertex.resize(this->n);
            for (int v=0;v<pos.size();v++){
                pos_to_vertex[pos[v]] = v;
            }   
        };
        mappos_to_value();
        // dbg(parent); dbg(depth); dbg(heavy); dbg(head); dbg(pos);dbg(pos_to_vertex);
    }
    // Path từ nút con tới LCA. với 2 nút u, v bất kỳ: path(u, v) = path(u, lca(u,v)) + path(v, lca(u, v))
    vector<pair<int,int>> path(int u, int p){
        // assert(lca(u, p) == u || lca(u,p) == p)
        vector<pair<int,int>> pth; // path
        while (head[p] != head[u]){
            pth.push_back({u, head[u]});
            u = parent[head[u]]; // chạy từ u tới điểm đầu substree rồi lấy parent sẽ ra điểm cuối của subtree cha
        }
        pth.push_back({u, p}); 
        return pth;
    }
 
    SegmentTree<int> *seg;
    void buildSegTree(vector<int> weight){
        // pos[] lưu vị trí của các node theo thứ tự duyệt. Duyệt trong 1 khối (subtree, chain) -> duyệt từ khối này nối sang khối khác
        vector<int> wvt(n); // weight of verticies - làm phẳng tree ra dạng [[chain1][chain2][...]...]
        // khi này muốn query(u, v) thì sẽ chia ra [u..->tailu][...][headv..->v] rồi query từng khúc 1
        for (int i=0;i<n;i++) wvt[pos[i]] = weight[i]; // làm phẳng cây ra thành 1 mảng với các đoạn segment nối tiếp nhau
        this->seg = new SegmentTree<int>(wvt);
    }
 
    int query(int u, int p){
        // assert(lca(u,p) == u || lca(u,p) == v)
        vector<pair<int,int>> pathu = path(u, p);
        int ans = 0; // lưu ý trường hợp u=p với weight trên cạnh sẽ ko có path u->u do bị cắt đầu. Nên ans sẽ ko thay đổi vẫn = 0
        for (auto chain: pathu){
            // CHANGE HERE max() to any function
            ans = max(ans, seg->query(pos[chain.second], pos[chain.first])); // chain lưu các đỉnh. chuyển các đỉnh đó về vị trí trong seg thì = pos[u]
        }
        return ans;
    }

    // verification: https://www.spoj.com/status/QTREE,hoanglongvn/
    void set_val(int u, int val){
        // với weight trên edge(u, v) thì if (lca.height[u] > lca.height[v]) hld.set_val(u) else hld.set_val(v). hld.set_val(child) do weight chuyển về child
        seg->set_val(pos[u], val);
    }

    // verification: https://www.spoj.com/status/QTREE2,hoanglongvn/
    int kth_ancestor(int u, int k){ // kth_ancestor(u, 0) = u;
        assert(depth[0] +k <= depth[u]);
        auto pathur = path(u, 0); // path u to root
        int step = 0;
        for (auto uv: pathur){
            step += pos[uv.first] - pos[uv.second]; // nhảy cuối lên đầu chain
            if (step >= k) {
                int p = pos[uv.second] + step -k; // lấy điểm đầu chạy (step-k) bước là ra pos điểm cần tìm
                return pos_to_vertex[p];
            }
            step++; // nhảy từ chain này sang chain khác
        }
        return 0;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, m;
    cin >> N>> m;
    vector<vector<int>> adj(N);
    for (int i=0;i<N-1;i++){
        int u, v;
        cin >> u>> v; u--; v--;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    vector<int> w(N, 0);
    LCA lca(adj);
    HeavyLightDecomposition hld(adj);
    hld.buildSegTree(w);
    for (int i=0;i<m;i++){
        int u, v;
        cin >> u>>v; v--;
        if (u == 0){
            // Change color
            int color = hld.query(v, v);
            hld.set_val(v, 1-color);
        } else {
            if (hld.query(v, 0) == 0) {
                cout << -1<< '\n'; continue;
            }
            // query first black
            // Binary search
            int right = hld.depth[v], left = hld.depth[0];
            while (left < right){
                int mid = (left+right)/2;
                int k = hld.kth_ancestor(v, hld.depth[v] - mid);
                if (hld.query(k, 0) == 1){
                    right = mid;
                } else {
                    left = mid+1;
                }
            }
            cout << hld.kth_ancestor(v, hld.depth[v] - right) +1<<'\n';
        }
    }
}
// bài này coi white có giá trị node là 0
// black có giá trị node là 1
// cập nhật thì dùng segmenttree.set_val(node, val)
/* query trên path từ v tới 0 (là 1 ancestor của v)
  left, right, mid sẽ là chiều cao của node
  seg.query(node có depth = mid, root node)
  Sử dụng hàm kth_ancestor dễ dàng lấy ra được node có chiều cao mid
  trên đường di chuyển từ v tới root. Node đó cách root mid khoảng cách 
  nghĩa là node đó là (right-mid) th-ancestor của v.
  -> tìm ra được node x mà tại đó seg.query(x, 0) = 1. in ra node đó
*/