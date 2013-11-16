#!/usr/bin/python
import sys

class Graph:
    # Object representing the graph problem

    def __init__(self, n=0, edges=[[]], edgelist=[]):
        # initialize variables
        self.n=n
        self.edges=edges
        self.edgelist=edgelist

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




def solve(G,alpha):
    raise NotImplemented



def main():
    (G,alpha) = parse()
    soln=solve(G,alpha)
    print len(soln)
    for v in soln:
        print v 


if __name__ == '__main__':
    main()
