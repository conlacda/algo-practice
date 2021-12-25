#include <bits/stdc++.h>
// https://cses.fi/problemset/task/1193
// Use BFS()
// format code: http://format.krzaq.cc/
// Sử dụng thuật toán BFS(). Do mọi cạnh đều bằng nhau nên ko có Dijkstra
// Mở rộng các điểm theo layer. Layer chính là khoảng cách từ điểm A tới node đó
// Để in ra đường đi. Nếu node x->y. khoảng cách y tăng 1 so với x
// path[y] = {U,D,R,L} thể hiện hành động đi từ y->x. Ví dụ x nằm trên y-> path[y] =U
// Sau khi dùng BFS() lan tới toàn bộ đồ thị, từ B dùng path[] lần ngược distance lần là tới điểm A
// Ví dụ path[B] = 'U' -> di chuyển B đi lên, 'R' di chuyển B qua phải.
using namespace std;
int N, M;
bool visited[1000][1000];
int dist[1000][1000];
char path[1000][1000];
int sx, sy, ex, ey;
vector<pair<int, int> > Q;

int main()
{
    cin >> N >> M;
    string s;
    for (int i = 0; i < N; i++) {
        cin >> s;
        for (int j = 0; j < M; j++) {
            if (s[j] == '#') {
                visited[i][j] = true;
            }
            else {
                visited[i][j] = false;
                if (s[j] == 'A') {
                    sx = i;
                    sy = j;
                }
                else if (s[j] == 'B') {
                    ex = i;
                    ey = j;
                }
            }
        }
    }

    Q.push_back({ sx, sy });
    dist[sx][sy] = 0;
    while (!Q.empty()) {
        pair<int, int> p = Q[0];
        Q.erase(Q.begin());
        int x = p.first;
        int y = p.second;
        if (x - 1 >= 0 && !visited[x - 1][y]) {
            visited[x - 1][y] = true;
            dist[x - 1][y] = dist[x][y] + 1;
            path[x - 1][y] = 'U';
            Q.push_back({ x - 1, y });
        }
        if (x + 1 < N && !visited[x + 1][y]) {
            visited[x + 1][y] = true;
            dist[x + 1][y] = dist[x][y] + 1;
            path[x + 1][y] = 'D';
            Q.push_back({ x + 1, y });
        }
        if (y - 1 >= 0 && !visited[x][y - 1]) {
            visited[x][y - 1] = true;
            dist[x][y - 1] = dist[x][y] + 1;
            path[x][y - 1] = 'L';
            Q.push_back({ x, y - 1 });
        }
        if (y + 1 < M && !visited[x][y + 1]) {
            visited[x][y + 1] = true;
            dist[x][y + 1] = dist[x][y] + 1;
            path[x][y + 1] = 'R';
            Q.push_back({ x, y + 1 });
        }
    }
    vector<char> ans;
    if (dist[ex][ey] == 0) {
        cout << "NO";
    }
    else {
        cout << "YES" << '\n';
        cout << dist[ex][ey] << '\n';
        int x, y;
        x = ex;
        y = ey;
        for (int i = 0; i < dist[ex][ey]; i++) {
            ans.push_back(path[x][y]);
            if (path[x][y] == 'D') {
                x--;
            }
            else if (path[x][y] == 'U') {
                x++;
            }
            else if (path[x][y] == 'L') {
                y++;
            }
            else if (path[x][y] == 'R') {
                y--;
            }
        }
        for (int i = ans.size() - 1; i >= 0; i--) {
            cout << ans[i];
        }
    }
}
