#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "solve.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define RATIO 0.7

int main(){
  int n, e;
  double alpha;

  scanf("%d %d %lf", &n, &e, &alpha);
  edgeList edges = getEdgeList(e);
  vertex *vlist = getVertexList(n, edges, e);
  int** adjMat = adjacencyMatrix(n, edges, e);
  solve(n, vlist);

  freeMatrix(adjMat, n);
  return 0;
}

void printVertexList(int n, vertex * vlist) {
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
              int path[n], int depth, int curval) {
  path[depth] = cur;
  
  edgeList edges = vlist[cur].edges;
  int degree = vlist[cur].degree;
  
  int first = -1;
  for (int i=0; i<degree; i++) {
    if (!visited[edges[i].to]) {
      first = i;
      break;
    }
  }

  double ret = curval;

  if (first != -1) {
    ret = minmax(n, vlist, visited, first, path, depth+1,
                 curval + edges[first].snow);
    for (int i=first+1; i<degree; i++) {
      
      int neighbor = edges[i].to;
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        
        double est = estimate(n, vlist, visited) + edges[i].snow;
        if (est * 0.7 >= ret) {
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
    printPath(path, depth, curval);
  }
  
  path[depth] = -1;

  return ret;
      
}

void solve(int n, vertex *vlist) {
  printVertexList(n, vlist);
}

int comp(const void * elem1, const void * elem2) {
  double s1 = ((edge*)elem1)->snow;
  double s2 = ((edge*)elem2)->snow;
  if (s1 > s2) return -1;
  if (s2 > s1) return 1;
  return 0;
}

vertex * getVertexList(int n, edgeList edges, int e) {
  qsort(edges, e, sizeof(edge), comp);
  
  vertex * ret = malloc(n * sizeof(vertex));
  
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

/* Given functions */

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
