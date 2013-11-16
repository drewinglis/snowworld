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

edgeList getEdgeList(int e);
int **adjacencyMatrix(int n, edgeList edges, int e);
void freeMatrix(int **adjMat, int n);
void solve();

#endif
