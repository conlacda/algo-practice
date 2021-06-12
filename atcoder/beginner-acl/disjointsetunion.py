# Chưa hiểu sai cái gì
"""
scc = defaultdict(
    1: [...], # scc số 1 đang có ... các đỉnh trong mảng đó
    2: [...],
    ...
    scc_num: [...]
)
scc_verticies = [2,2,....., scc_num,1,3] # ghi lại các đỉnh đang thuộc scc nào.
scc_verticies[1] = 2 -> đỉnh 1 đang thuộc scc số 2
"""
from collections import defaultdict

verticies_num, queries = [int(i) for i in input().split(' ')]

scc_num = 0
scc = defaultdict(lambda: [])
scc_verticies = [-1] * verticies_num

for i in range(queries):
    demand, u, v = [int(i) for i in input().split(' ')]
    if demand == 0:
        # add edge
        if scc_verticies[u] == -1:
            if scc_verticies[v] == -1:
                scc[scc_num].append(u)
                scc[scc_num].append(v)
                scc_verticies[u] = scc_num
                scc_verticies[v] = scc_num
                scc_num += 1
            else:
                # u khong, v co
                scc_verticies[u] = scc_verticies[v]
                scc[scc_verticies[v]].append(u)
        elif scc_verticies[u] != -1:
            if scc_verticies[v] == -1:
                # u co, v khong
                scc_verticies[v] = scc_verticies[u]
                scc[scc_verticies[v]].append(v)
            else:
                # v co, u co
                if scc_verticies[u] == scc_verticies[v]:
                    pass
                else:
                    uscc = scc_verticies[u]
                    vscc = scc_verticies[v]
                    # scc[scc_verticies[u]] += scc[scc_verticies[v]]
                    for i in range(len(scc[vscc])-1, -1, -1):
                        scc_verticies[scc[vscc][i]] = uscc
                        scc[uscc].append(scc[vscc][i])
                        scc[vscc].pop()
    else:
        # print 1 or 0
        if scc_verticies[u] == scc_verticies[v] and scc_verticies[u] !=-1:
            print(1)
        else:
            print(0)