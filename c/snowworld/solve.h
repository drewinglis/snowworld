#ifndef SOLVE_H
#define SOLVE_H

typedef struct elem {
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
double estimate(int n, vertex *vlist, bool visited[n]);
double minmax(int n, vertex *vlist, bool visited[n], int cur,
              int path[n], int depth, double curval);
void freeMatrix(int **adjMat, int n);
void printMaxDFS(
  vertexList vertices,
  int currentVertex,
  bool visited[],
  int path[],
  int depth
);
void printPathIfGreater(int *path, int depth, double weight);
void printPath(int *path, int depth);
int *greedy(vertexList vertices, edgeList edges, int n);
void solve(vertexList vertices, int n);
double estimate2(bool exclude[], int startIndex, int depth, int n);

#endif
