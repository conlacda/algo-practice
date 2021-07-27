# K-th zero problem

## URL

https://www.hackerrank.com/contests/modena-coding-oct-2017/challenges/kthzero/problem

## Mô tả: 
cho dãy a[]  
Cho n query. query loại 1 chỉ ra vị trí số 0 thứ k của dãy  
query loại 2 cập nhật giá trị tại index i thành giá trị x  
Ví dụ: a = 0 1 0 2 0 3  
q1 = 3 -> return 4 (a[0] = a[2] = a[4] = 0)  
q2 = 1 0 -> a = 0 0 0 2 0 3  

## Thuật toán  
### Fenwicktree (range query, point update)
Thuật toán này coi dãy a chỉ gồm số 0 và 1 (mọi số khác 0 là 1). Dựng fenwicktree cho mảng.  
q2 sẽ tương ứng với thao tác update (point update)  
q1 sẽ dùng binary search.  
Dùng range query để tính số lượng số 0 có trong khoảng đó cho tới khi tìm ra điểm có số lượng số 0 thỏa mãn  
Ví dụ: 0 1 0 1 0 0 1  k = 1  
left = 0 right = 6  
fw.range_query(middle =3) => 2 số 0 >1 -> right = middle-1  
-> left = 0 right = middle-1 = 2  
fw.range_query(middle=1) -> 1 số 0 -> ok right = middle   
-> left = 0 right = middle = 0 -> 1 số 0 và left=right -> cout << r; chính là index cần tìm

**Độ phức tạp thuật toán**
Với input_size = 100000 (N) và query = 100000 (Q)  
Với mỗi thao tác cập nhật sẽ là QlogN  
Thao tác tìm kiếm sẽ tốn QlogN*logN. Vì thao tác tìm fw.range_query(middle) = logN. thao tác binarysearch logN nữa. và có Q query.  
Thời gian thực hiện: ~8s
```c++
//https://www.hackerrank.com/contests/modena-coding-oct-2017/challenges/kthzero/forum
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Full example: https://github.com/conlacda/algo/blob/master/data-structure/fenwick-tree.md
// Range query, point update
struct FenwickTree { // Zero-base indexing
    vector<long long> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0); // bit = vector<long long> (n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    long long sum(int r) {
        if (r==-1) return 0;
        long long ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    long long sum(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    vector<int> original(){ // Return original value of input vector
        vector<int> a;
        for (int i=0;i<this->n;i++){
            a.push_back(sum(i,i));
        }
        for (auto v: a) cout << v<< ' '; cout << '\n';
        return a;
    }
};
/*
Initialize:
vector<long long> a{1,2,3,4,5};
FenwickTree fw(a);
---OR---
FenwickTree fw(N);
for (int i=0;i<N;i++){
    int x; cin >> x;
    fw.add(i,x);
}
Sum: fw.sum(r) // from 0->r (includes r)
     fw.sum(l,r) // from l->r (includes l,r)
Add: fw.add(r, k) // a[r] = a[r] + k
*/
int number_zero(FenwickTree fw, int idx){
    int s = fw.sum(idx);
    return idx+1-s;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N, 0);
    for (int i=0;i<N;i++){
        int x; cin >> x;
        if (x !=0) a[i] = 1;
    }
    FenwickTree fw(a);
    while (Q--){
        int q, p, v;
        cin >> q;
        if (q==1){
            cin >> p;
            // Find k-th index
            if (number_zero(fw,N-1) <p){
                cout << "NO" << '\n';
            } else{
                int left=0, right=N-1;
                while (left<=right) {
                    int mid = (left+right)/2;
                    int z = number_zero(fw, mid);
                    if (z < p){
                        left = mid+1;
                    } else if(z > p){
                        right = mid-1;
                    } else {
                        right = mid;
                        if (right==left) break;
                    }
                }
                cout << right << '\n';
            }
        } else { // q == 2
            cin >> p >> v;
            if (v!=0) v=1;
            if (a[p] !=v){
                int delta = v - a[p];
                fw.add(p, delta);
                a[p] = v;
            }
            // fw.original();
        }
    }
}
```

## Thuật toán 2

Dùng 1 mảng s lưu lại vị trí của các số 0  
a = 0 1 0 1 1 1  
s = 0 2  
Thao tác cập nhật:  
Nếu index có trong s thì nếu value!=0 -> xóa vị trí đó. còn không thì giá trị vẫn giữ nguyên  
Nếu index không có trong s mà value=0 -> thêm index đó vào trong s. còn không thì bỏ qua  
Ví dụ: a = 0 2 0 3 4 5  
s = 0 2
a[1] = 5 -> a = 0 5 0 3 4 5 -> s giữ nguyên  
a[0] = 7 -> a = 7 5 0 3 4 5 -> xóa số 0 trong s đi  
a[2] = 0 -> a = 7 5 0 3 4 5 -> không thay đổi gì
a[1] = 0 -> a = 7 0 0 3 4 5 -> thêm giá trị 1 vào s [1,2]
```c++
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

int indexOf(int value, vector < int > a) {
    vector < int > ::iterator low;
    low = lower_bound(a.begin(), a.end(), value);
    int x = low - a.begin();
    if (x >= a.size() || a[x] != value) return -1;
    return x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif
    int N, Q;
    cin >> N >> Q;
    vector < int > a;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        if (x == 0) a.push_back(i);
    }
    // for (auto v: a) cout << v << ' '; cout << '\n';
    while (Q--) {
        int q;
        cin >> q;
        if (q == 1) {
            int idx;
            cin >> idx;
            if (idx > a.size()) cout << "NO" << '\n';
            else cout << a[idx - 1] << '\n';
        } else {
            int idx, value;
            cin >> idx >> value;
            if (value != 0) {
                int x = indexOf(idx, a);
                if (x != -1) {
                    a.erase(a.begin() + x);
                }
            } else {
                int x = indexOf(idx, a);
                if (x == -1) {
                    int p = lower_bound(a.begin(), a.end(), idx) - a.begin();
                    a.insert(a.begin() + p, idx);
                }
            }
        }
        // for (auto v: a) cout << v << ' '; cout << '\n';
    }
}
```