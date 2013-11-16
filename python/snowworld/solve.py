#!/usr/bin/python
import sys

class Graph:
    # Object representing the graph problem

    def __init__(self, n=0, edges=None, edgelist=None):
        # initialize variables
        #be careful of mutable values as default. Make the default values
        #below instead
        self.n=n
        self.edges=edges if edges else [[]]
        self.edgelist=edgelist if edgelist else []

    def neighbors(self,vertex):
        # init list
        neighborlist=[]

        # Traverse association matrix on row v
        for i in range(self.n):
            edgeVal = self.edges[vertex][i]
            # if edge exists a!=-1, add it to the list
            if edgeVal!=-1:
                neighborlist.append((i,edgeVal))
        return neighborlist

"""
Graph G is a graph datastructure in the format:
    (n, edges, edgelist)

    n : number of vertices
    edges : Association Matrix for the graph (2D list/array),
            where -1 indicates there is no edge
            and a>=0 indicates an edge with a amount of snow
    edgelist : list of edges in the format (v1,v2,snow)
"""

def parse():
    n=int(raw_input())
    numedges=int(raw_input())
    alpha=float(raw_input())
    edgelist=[]
    for i in range(numedges):
        nums = raw_input().split()
        edgelist.append((int(nums[0]),int(nums[1]),int(nums[2])))

    edges = createEMatrix(edgelist,n)
    G = Graph(n, edges, edgelist)

    return (G,alpha)


def createEMatrix(edgelist,n):
    edges=[[ -1 for i in range(n)] for i in range(n)]
    for (v1,v2,m) in edgelist:   
       edges[v1][v2]=m
       edges[v2][v1]=m 

    return edges




    



def main():
    (G,alpha) = parse()
    soln=solve(G,alpha)
    print len(soln)
    for v in soln:
        print v 

#####
class Memoize:
    def __init__(self, f):
        self.f = f
        self.memo = {}
    def __call__(self, *args):
        if not args in self.memo:
            self.memo[args] = self.f(*args)
        else:
            pass
        return self.memo[args] 

#My code:

def make_path_list(G, visited, start):
    #visited is tuple
    #G is Graph
    results = []
    visited =  (start,) + visited
    for i in xrange(len(G.edges[start])):
        if (G.edges[start][i]!= -1) and (i not in visited):
                #assume in goes left to right, put start on left so its
                #seen first
            next_step = (make_path_list(G, visited, i))
            results.extend(next_step)
    if len(results)==0:
        return [[start]] #one path of length 1
    else:
        return [[start]+result for result in results]
make_path_list = Memoize(make_path_list)

def pick_up_snow(G, alpha, path):
    total = 0
    ratio = 1.0
    current_spot = path[0]
    for next_spot in path[1:]:
        edge_weight = G.edges[current_spot][next_spot]
        total += ratio * edge_weight
        ratio *= alpha
        current_spot = next_spot
    print total, path
    return total

def solve(G,alpha):
    paths = make_path_list(G, (), 0)
    best_path = max(paths, key=lambda path: pick_up_snow(G, alpha, path))
    print pick_up_snow(G, alpha, best_path)
    return best_path

if __name__ == '__main__':
    main()
