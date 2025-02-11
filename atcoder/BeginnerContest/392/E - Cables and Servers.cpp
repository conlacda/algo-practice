#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

struct DSU {
private:
    struct Node {
        int size = 1;
        // thêm các trường thông tin mà root có thể giữ// ***
    };
public:
    vector<int> parent;
    vector<Node> data; // data[dsu.find(i)];
    int n;
    DSU(int _n) {
        n = _n;
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        data.resize(n); // data[i] = Node{1};// ***
    }

    int find(int v) {
        assert(0 <= v && v < n);
        if (v == parent[v]) return v;
        parent[v] = find(parent[v]);
        return parent[v];
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (data[a].size < data[b].size) swap(a, b);
        parent[b] = a;

        data[a].size += data[b].size;
        // cập nhật thông tin cho node root// ***
        return true;
    }
    bool isSame(int a, int b) {
        return find(a) == find(b);
    }
    Node& operator[](int index) {
        index = find(index);
        return data[index];
    }
};

struct X {
    int index, start, end;
};

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Kết nối lại cap
    Ta thấy không thể cắt đi 1 bridge edge được
    Cắt đi 1 edge không phải bridge và sẽ nối nó vào các thành phần liên thông khác
    ta thấy có bao nhiêu CC thì bằng đó lần cần phải nối
    Nếu ta dựng DSU lên thì mỗi cạnh thừa ta sẽ biết được
    => Các cạnh thừa đó sẽ được nối vào các liên thông khác
    */
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    vector<X> redundant;
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (dsu.isSame(u, v)) {
            redundant.push_back({i, u, v});
        } else {
            dsu.merge(u, v);
        }
    }
    set<int> root;
    for (int i=0;i<n;i++)
        root.insert(dsu.find(i));
    cout << root.size() - 1 << '\n';
    // Lấy cap thừa nối các cái leader lại vào với nhau
    int k = (int) root.size() - 1;
    for (int i=0;i<k;i++) {
        // Lấy ra cái sợi cáp cuối
        // Nối sợi cáp đó sang bất kỳ 1 root nào bên ngoài
        // Sau khi nối vào thì 1 root sẽ bị mất đi
        auto cable = redundant[(int) redundant.size() - 1];
        int curroot = dsu.find(cable.start);
        int anotherroot = -1;
        for (auto&v: root) {
            if (v != curroot) {
                anotherroot = v;
                break;  
            }
        }
        assert(anotherroot != -1);
        dsu.merge(curroot, anotherroot);
        cout << cable.index + 1 << ' ' << cable.end + 1 << ' ' << anotherroot + 1<< '\n';
        auto newroot = dsu.find(curroot);
        if (newroot == curroot)
            root.erase(anotherroot);
        else
            root.erase(curroot);

        redundant.pop_back();
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
