
# Đúng 10/11 bài test - chưa tuyệt đối
from collections import defaultdict
# Duyệt DFS() rồi lưu lại thứ tự duyệt.
# Phần tử về cuối là source -> sink của graph ban đầu.
# Duyệt từ sink dần đi là ra SCC
graph = defaultdict(lambda:[])
reversed_graph = defaultdict(lambda: [])
v_num, e_num = [int(i) for i in input().split()]
for _ in range(e_num):
    u,v = [int(i) for i in input().split()]
    if u!=v:
        graph[u].append(v)
        reversed_graph[v].append(u)

visited = [False] * v_num
post_v = []
def explore(u, graph):
    if not visited[u]:
        visited[u] = True
        for edge in graph[u]:
            explore(edge, graph)
        post_v.append(u)

def dfs_re():
    for i in range(v_num):
        explore(i, reversed_graph)
dfs_re()
# print(post_v)
post = post_v[::-1] # topo order
visited= [False] * v_num
def explore_main(u, scc):
    if not visited[u]:
        scc.append(u)
        visited[u]= True
        for edge in graph[u]:
            explore_main(edge, scc)
SCC = []
def dfs_main():
    for i in post:
        scc = []
        explore_main(i, scc)
        if len(scc) != 0:
            SCC.append(scc)

dfs_main()
print(len(SCC))
for it in SCC[::-1]:
    print(len(it), end=' ')
    for i in it:
        print(i, end=' ')
    print()