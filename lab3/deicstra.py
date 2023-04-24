import math

def get_link_v(v,D):
    for i, weight in enumerate(D[v]):
        if weight >0:
            yield i

def arg_min(T, S):
    amin = -1
    m = math.inf
    for i, t in enumerate(T):
        if t < m and i not in S:
            m = t
            amin = i

    return amin


adjacency_matrix = ((0, 6, 0, 0, 2, 0, 0, 0),
    (6, 0, 9, 0, 1, 5, 3, 0),
    (0, 9, 0, 12, 0, 0, 8, 0),
    (0, 0, 12, 0, 0, 0, 3, 4),
    (2, 1, 0, 0, 0, 7, 0, 0),
    (0, 5, 0, 0, 7, 0, 4, 0),
    (0, 3, 8, 3, 0, 4, 0, 16),
    (0, 0, 0, 4, 0, 0, 16, 0))

N = len(adjacency_matrix) 
T = [math.inf]*N 
v = 0 
Vs = {v} 
T[v] = 0 

while v != -1:
    for j in get_link_v(v, adjacency_matrix): 
        if j not in Vs:
            w = T[v] + adjacency_matrix[v][j]
            if w < T[j]:
                T[j] = w
    v = arg_min(T, Vs) 
    if v >= 0: 
        Vs.add(v) 
print(T)
