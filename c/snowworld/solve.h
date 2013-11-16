#ifndef SOLVE_H
#define SOLVE_H

typedef struct elem{
  int to;
  int from;
  double snow;
} edge;

typedef edge* edgeList;

typedef struct vertex_t {
  int degree;
  edgeList edges;
} vertex;

typedef vertex* vertexList;

edgeList getEdgeList(int e);
int **adjacencyMatrix(int n, edgeList edges, int e);
vertex *getVertexList(int n, edgeList edges, int e);
void printVertexList(int n, vertex * vlist);
void freeMatrix(int **adjMat, int n);
void printMaxDFS(vertexList vertices, int currentVertex, bool visited[]);
void solve(vertexList vertices, edgeList edges, int n);

#endif
