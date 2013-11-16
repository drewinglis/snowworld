#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "math.h"

using namespace std;


typedef vector<pair<pair<int, int>, double> > edgeList;
edgeList getEdgeList(int e); 
int **adjacencyMatrix(int n, edgeList edges); 
void freeMatrix(int **adjMat, int n); 
void solve();                        

int main(){
  int n, e;
  double alpha;
  scanf("%d %d %lf", &n, &e, &alpha);
  edgeList edges = getEdgeList(e);
  int** adjMat = adjacencyMatrix(n, edges);
  
  solve();

  freeMatrix(adjMat, n);
  return 0;
}

/* Solves and prints out solution */

void solve(){
  /* Unimplemented */
}

/* Given functions */

/* Reads from stdin and forms an edgeList of type edgeList */
edgeList getEdgeList(int e){
  int a, b;
  double c;
  edgeList edges;
  for(int i = 0; i < e; i++){
    scanf("%d %d %lf", &a, &b, &c);
    edges.push_back(make_pair(make_pair(a,b), c));
  }
  return edges;
}

/* Creates an adjacency matrix from the edgeList */
int **adjacencyMatrix(int n, edgeList edges){
  int **adjMat = new int*[n];
  for(int i = 0; i < n; i++){
    adjMat[i] = new int[n];
  }
  int to, from;
  for(int i = 0; i < edges.size(); i++){
    to = edges[i].first.first;
    from = edges[i].first.second;
    adjMat[to][from] = 1;
    adjMat[from][to] = 1;
  }
  return adjMat;
}

/* Deletes what was allocated (using delete) */
void freeMatrix(int **adjMat, int n){
  if(adjMat == NULL) return;
  for(int i = 0; i < n; i++){
    delete [] adjMat[i];
  }
  delete [] adjMat;
}
