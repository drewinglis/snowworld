#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "math.h"
#include "solve.h"

double alpha;

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define RATIO 0.7

int main(){
  int n, e;

  scanf("%d %d %lf", &n, &e, &alpha);
  edgeList edges = getEdgeList(e);
  vertexList vlist = getVertexList(n, edges, e);
  int** adjMat = adjacencyMatrix(n, edges, e);

  solve(vlist, edges, n);

  freeMatrix(adjMat, n);
  return 0;
}

void printVertexList(int n, vertexList vlist) {
  printf("%d\n", n);
  for (int i=0; i<n; i++) {
    printf("%d: ", i);
    for (int j=0; j<vlist[i].degree; j++) {
      printf("%d ",vlist[i].edges[j].to);
    }
    printf("\n");
  }
}

/* Solves and prints out solution */

double estimate(int n, vertex *vlist, bool visited[n]) {
  double total = 0;
  for (int i=0; i<n; i++) {
    if (!visited[i]) {
      for (int j=0; j<vlist[i].degree; j++) {
        if (!visited[vlist[i].edges[j].to]) {
          total += vlist[i].edges[j].snow;
          break;
        }
      }
    }
  }
  return total;
}

double minmax(int n, vertex *vlist, bool visited[n], int cur,
              int path[n], int depth, double curval) {
  //printf("depth %d visiting %d\n", depth, cur);
  path[depth] = cur;
  
  edgeList edges = vlist[cur].edges;
  int degree = vlist[cur].degree;
  
  int first = -1;
  for (int i=0; i<degree; i++) {
    if (!visited[edges[i].to]) {
      first = edges[i].to;
      break;
    }
  }

  double ret = curval;

  if (first != -1) {
    visited[first] = true;
    //printf("marking %d as visited: %d\n", first, visited[first]);
    ret = minmax(n, vlist, visited, first, path, depth+1,
                 curval + edges[first].snow);
    visited[first] = false;
    //printf("unmarking %d as visited\n", first);
    for (int i=first+1; i<degree; i++) {
      
      int neighbor = edges[i].to;
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        
        double est = estimate(n, vlist, visited) + edges[i].snow;
        //    printf("level %d | %lf  %lf\n", depth, est, ret);
        if (est * 0.7 >= ret) {
          // printf("HELLO\n");
          double realval = minmax(n, vlist, visited, neighbor,
                                  path, depth+1, curval + edges[i].snow);
          if (realval > ret) {
            ret = realval;
          }
        }
        
        visited[neighbor] = false;
      }
    }
  } else {
    printPathIfGreater(path, depth, curval);
  }
  
  path[depth] = -1;

  return ret;
      
}

int comp(const void * elem1, const void * elem2) {
  double s1 = ((edge*)elem1)->snow;
  double s2 = ((edge*)elem2)->snow;
  if (s1 > s2) return -1;
  if (s2 > s1) return 1;
  return 0;
}

vertexList getVertexList(int n, edgeList edges, int e) {
  qsort(edges, e, sizeof(edge), comp);

  vertexList ret = malloc(n * sizeof(vertex));

  for (int i=0; i<e; i++) {
    ret[edges[i].to].degree++;
    ret[edges[i].from].degree++;
  }

  int count[n];

  for (int i=0; i<n; i++) {
    ret[i].edges = malloc(ret[i].degree * sizeof(edge));
    count[i] = 0;
  }

  for (int i=0; i<e; i++) {
    int a = edges[i].to;
    int b = edges[i].from;
    int ca = count[a]++;
    int cb = count[b]++;

    ret[a].edges[ca].from = a;
    ret[a].edges[ca].to = b;
    ret[a].edges[ca].snow = edges[i].snow;

    ret[b].edges[cb].from = b;
    ret[b].edges[cb].to = a;
    ret[b].edges[cb].snow = edges[i].snow;
  }

  return ret;
}

/* Solves and prints out solution */
void solve(vertexList vertices, edgeList edges, int n){
  bool visited[n];
  int path[n];
  int depth = 0;

  memset(visited, false, sizeof(bool)*n);
  memset(path, -1, sizeof(int)*n);
  visited[0] = true;
  //printMaxDFS(vertices, 0, visited, path, 0);

  //  int *path = greedy(vertices, edges, n);
  //printPath(path, n);

  double weight = minmax(n, vertices, visited, 0, path, 0, 0);
}

int *greedy(vertexList vertices, edgeList edges, int n) {
  bool visited[n];
  int *path = malloc(n*sizeof(int));
  int depth = 1;
  int currentIndex = edges[0].from;

  memset(visited, false, sizeof(bool)*n);
  memset(path, -1, sizeof(int)*n);

  visited[0] = true;
  path[0] = 0;

  while (true) {
    vertex current = vertices[currentIndex];
    int i;
    int next;

    visited[currentIndex] = true;
    path[depth] = currentIndex;
    depth += 1;

    for (i = 0; i < current.degree; i += 1) {
      next = current.edges[i].to;

      if (false == visited[next]) {
        currentIndex = next;
        break;
      }
    }
 
    if (i == current.degree) {
      break;
    }

    next = currentIndex;
  }

  return path;
}

void printMaxDFS(
  vertexList vertices,
  int currentIndex,
  bool visited[],
  int path[],
  int depth
) {
  vertex current = vertices[currentIndex];
  int next;

  visited[currentIndex] = true;
  path[depth] = currentIndex;
  depth += 1;

  for (int i = 0; i < current.degree; i += 1) {
    next = current.edges[i].to;
    printf("next: %d\n", next);

    printf("false: %d visited[next]: %d\n", false, visited[next]);
    if (false == visited[next]) {
      printMaxDFS(vertices, next, visited, path, depth);
    }
  }

  printPath(path, depth);

  depth -= 1;
  path[depth] = -1;
  visited[currentIndex] = false;
  return;
}

void printPathIfGreater(int path[], int depth, double weight) {
  static double maxweight;
  if (weight > maxweight) {
    maxweight = weight;
    printf("%d\n", depth);
    for (int i = 0; i < depth; i += 1) {
      printf("%d\n", path[i]);
    }
  }
}

void printPath(int path[], int depth) {
  printf("%d\n", depth);
  for (int i = 0; i < depth; i += 1) {
    printf("%d\n", path[i]);
  }
}

/* Reads from stdin and forms an edgeList of type edgeList */
edgeList getEdgeList(int e){
  edgeList edges = (edge *)malloc(e*sizeof(edge));
  int a, b;
  double c;
  for(int i = 0; i < e; i++){
    scanf("%d %d %lf", &a, &b, &c);
    edges[i].to = a;
    edges[i].from = b;
    edges[i].snow = c;
  }
  return edges;
}

/* Creates an adjacency matrix from the edgeList */
int **adjacencyMatrix(int n, edgeList edges, int e){
  int **adjMat;
  if( (adjMat = (int **)malloc(n*sizeof(edges)) ) == NULL)
    exit(1);
  for(int i = 0; i < n; i++){
    if((adjMat[i] = (int *)malloc(n*sizeof(int))) == NULL)
      exit(1);
  }
  int to, from;
  for(int i = 0; i < e; i++){
    to = edges[i].to;
    from = edges[i].from;
    adjMat[to][from] = 1;
    adjMat[from][to] = 1;
  }
  return adjMat;
}

/* Deletes what was allocated (using delete) */
void freeMatrix(int **adjMat, int n){
  if(adjMat == NULL) return;
  for(int i = 0; i < n; i++){
    if(adjMat[i] != NULL)
      free(adjMat[i]);
  }
  free(adjMat);
}
