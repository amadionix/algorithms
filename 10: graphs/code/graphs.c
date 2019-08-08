#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// general utilities
struct ListNode {
	struct ListNode *next;
	int v;
};
struct Queue {
  struct ListNode *b;
  struct ListNode *f;
  int sz;
};
void *MyMalloc(size_t size);
struct ListNode *ListInsert(int w, struct ListNode *old_list);
void PrintList(struct ListNode *h);
struct Queue *CreateQueue(void);
struct Queue *EnQueue(struct Queue *old_queue, int i);
int DeQueue(struct Queue *old_queue);

// *** adjacency matrix ***
struct Graph1 {
	int v, e; // v = vertex num, e = edge num  
	int **A; // adjacency matrix
};
typedef struct Graph1 *Graph1;
// utils
Graph1 GraphNew1(int v);
void GraphDestroy1(Graph1 g);
void GraphEdgeInsert1(Graph1 g, int v, int w);
Graph1 GraphRead1(void);
void GraphPrint1(Graph1 g);
// DFS & BFS          // TO DO: BFS/DFS FROM A NODE (TAKING NODE AS INPUT)
void DFS1(Graph1 g);
void DFSUtil1(Graph1 g, int i, bool *visited);
void BFS1(Graph1 g);
void BFSUtil1(Graph1 g, int i, bool *visited);

// *** adjacency list ***
struct Graph2 {
	int v, e;
	struct ListNode **A;
};
typedef struct Graph2 *Graph2;
// utils
Graph2 GraphNew2(int v);
void GraphDestroy2(Graph2 g);
void GraphEdgeInsert2(Graph2 g, int v, int w);
Graph2 GraphRead2(void);
void GraphPrint2(Graph2 g);
// DFS & BFS
void DFSUtil2(Graph2 g, int i, bool *visited);
void DFS2(Graph2 g);
void BFS2(Graph2 g);
void BFSUtil2(Graph2 g, int i, bool *visited);
// graph operations
Graph2 Gen(float p, int v);
int Degree(Graph2 g, int v);
bool Path(Graph2 g, int v, int w);
int ConnectedComponentsCount(Graph2 g);
void BFSUtilCc(Graph2 g, int i, bool *visited);
void ConnectedComponentMembers(Graph2 g, int v);
Graph2 GetSpanTreeDFS(Graph2 g, int v);
void SpanTreeUtil(Graph2 g, Graph2 g2, int i, bool *visited);
void PrintSpanTreeAsSummary(Graph2 g, int v);
void SpanTreeAsSummaryUtil(Graph2 g, int i, bool *visited, int space);
Graph2 GetMinDepthSpanTree(Graph2 g, int v);
struct ListNode *GetMinPath(Graph2 g, int v, int w);
bool IsBipartite(Graph2 g);

/******************************************************************************/
// *** main ***
int main() {
  Graph2 g = Gen(0.3, 4);
  GraphPrint2(g);
  
  Graph2 span_tree = GetSpanTreeDFS(g, 0);
  GraphPrint2(span_tree);
  PrintSpanTreeAsSummary(span_tree, 0);

  Graph2 min_span_tree = GetMinDepthSpanTree(g, 0);
  GraphPrint2(min_span_tree);
  PrintSpanTreeAsSummary(min_span_tree, 0);

//  struct ListNode *l = GetMinPath(g, 5, 1);

  printf("%s", IsBipartite(g) ? "true" : "false");
}

// general utilities

void *MyMalloc(size_t size) {
	void *q = malloc(size);
	if(q == NULL)
		return NULL;
	return q;
}

struct ListNode *ListInsert(int w, struct ListNode *old_list) {
  struct ListNode *node = malloc(sizeof(struct ListNode));
  node->v = w;  
  node->next = NULL;
  struct ListNode *new_list = node;
	new_list->next = old_list;
	return new_list;
}

void PrintList(struct ListNode *h) {
	for (; h; h = h->next)
		printf("%d ", h->v);
	printf("\n");
}

struct Queue *CreateQueue(void) {
  struct Queue *q = malloc(sizeof(struct Queue));
  q->b = NULL;
  q->f = NULL;
  q->sz = 0;
  return q;
}

struct Queue *EnQueue(struct Queue *old_queue, int i) {
  struct ListNode *p = malloc(sizeof(struct ListNode));
  p->v = i;
  p->next = NULL;
  if(old_queue->sz == 0) { 
    old_queue->f = old_queue->b = p;
  } else {
    old_queue->f->next = p;
    old_queue->f = p;
  }
  old_queue->sz++;
  return old_queue;
}

int DeQueue(struct Queue *old_queue) {
  struct ListNode *out = NULL;
  if(old_queue->sz == 0) {
    return -1;
  }
  out = old_queue->b;
  old_queue->b = old_queue->b->next;
  old_queue->sz--;
  return out->v;
}

/******************************************************************************/
// *** adjacency matrix functions ***

Graph1 GraphNew1(int v) {
	Graph1 g = malloc(sizeof(struct Graph1));
	g->A = calloc(v, sizeof(int *));
	g->v = v;
	g->e = v*v;
	for (int i = 0; i < v; i++) 
		g->A[i] = calloc(v, sizeof(int));
	return g;
}

void GraphDestroy1(Graph1 g) {
  for(int i = 0; i < g->v; i++) 
    free(g->A[i]); 
  free(g->A);
  free(g);
}

void GraphEdgeInsert1(Graph1 g, int v, int w) {
  g->A[v][w] = 1;
  g->A[w][v] = 1;
}

Graph1 GraphRead1(void) {
  int v = 0, y = 0, w = 0, e = 0;
  Graph1 g;
  printf("How many nodes does your graph have?\n");
  scanf("%d", &v); 
  g = GraphNew1(v);
  printf("How many edges does your graph have?\n");
  scanf("%d", &e); 
  while (e > 0) {
    printf("Insert an edge by typing the two nodes separated by a comma"
           ", use the same node twice if it's an edgeless graph:\n");
    if(2 != scanf("%d,%d", &y, &w)) {
      printf("Invalid input\n"); 
      break;
    } else {
      if (y >= v || w >= v) {
        printf("Invalid input: graph doesn't contain these vertices\n\n");
      } else { 
        if (y != w)
          e--;
        GraphEdgeInsert1(g, y, w);
        }
    }  
  }
  printf("\n");
  return g;
}

void GraphPrint1(Graph1 g) {
  printf("\n");
  for (int i = 0; i < g->v; i++) {
    for (int j = 0; j < g->v; j++) 
      printf("%d ", g->A[i][j]);
  }
}

void DFS1(Graph1 g) {
  bool visited[g->v]; 
  int i;
  for (i = 0; i < g->v; i++) 
    visited[i] = false;
  for (i = 0; i < g->v; i++) {
    if(!visited[i]) 
      DFSUtil1(g, i, visited);
  }
  printf("\n");
}

void DFSUtil1(Graph1 g, int i, bool *visited) {
  for (int j = 0; j < g->v; j++) {
    if (g->A[i][j]) {
      if(!visited[i]) {
        printf("\n%d", i);
        visited[i] = true;
      }
      if (i != j && !visited[j]) {
        printf("\n%d", j);
        visited[j] = true;        
        DFSUtil1(g, j, visited);
      }
    }
  }  
}

void BFS1(Graph1 g) {
  bool visited[g->v]; 
  int i;
  for (i = 0; i < g->v; i++) 
    visited[i] = false;
  for (i = 0; i < g->v; i++) {
    if (!visited[i])
      BFSUtil1(g, i, visited);
  }
  printf("\n");  
}

void BFSUtil1(Graph1 g, int i, bool *visited) {
  struct Queue *q = CreateQueue();
  visited[i] = true;
  printf("\n%d", i);
  EnQueue(q, i);
  while (q->sz) { 
    i = DeQueue(q);
    for (int j = 0; j < g->v; j++) {
      if (!visited[j] && g->A[i][j]) {
        visited[j] = true;      
        EnQueue(q, j);
        printf("\n%d", j);
      }
    }
  }
}

/******************************************************************************/
// *** adjacency list functions ***

Graph2 GraphNew2(int v) {
	Graph2 g = malloc(sizeof(struct Graph2));
	g->v = v;
	g->e = 0;
	g->A = calloc(v, sizeof(struct ListNode *));
	return g;	
}

void GraphDestroy2(Graph2 g) {
  free(g->A);
  free(g);
}

void GraphEdgeInsert2(Graph2 g, int v, int w) {
  // if (v,w) is already in the graph I don't add it
	struct ListNode *q = NULL;    
  for (q = g->A[v]; q != NULL; q = q->next) 
    if (q->v == w) return;                   
  // each vertex has a self loop, empty graphs only have self loops
  if(!g->A[v]) 
    g->A[v] = ListInsert(v, g->A[v]);
  if(!g->A[w]) 
    g->A[w] = ListInsert(w, g->A[w]);
  g->e++;
  if (v != w) {
    g->A[v] = ListInsert(w, g->A[v]);
    g->A[w] = ListInsert(v, g->A[w]);
  }  
}

Graph2 GraphRead2(void) {
  int v = 0, y = 0, w = 0, e = 0;
  Graph2 g;
  printf("How many nodes does your graph have?\n");
  scanf("%d", &v); 
  g = GraphNew2(v);
  printf("How many edges does your graph have?\n");
  scanf("%d", &e); 
  while (e > 0) {
    printf("Insert an edge by typing the two nodes separated by a comma"
           ", use the same node twice if it's an edgeless graph:\n");
    if(2 != scanf("%d,%d", &y, &w)) {
      printf("Invalid input\n"); 
      break;
    } else { 
      if (y >= v || w >= v) {
        printf("Invalid input: graph doesn't contain these vertices\n\n");
      }  else { 
        if (y != w)
          e--;
        GraphEdgeInsert2(g, y, w);
        }
      }  
  }
  printf("\n");
  return g;
}

void GraphPrint2(Graph2 g) {
	struct ListNode *p = NULL;  
  for (int i = 0; i < g->v; i++) {
    printf("%d: ", i);
    for (p = g->A[i]; p != NULL; p = p->next) 
      printf("%d ", p->v);
    printf("\n");
  }
  printf("\n");
}

void DFS2(Graph2 g) {
  bool visited[g->v]; 
  for (int i = 0; i < g->v; i++) 
    visited[i] = false;
  for (int i = 0; i < g->v; i++) {
    if(!visited[i] && g->A[i] != NULL) {
      printf("\n%d", i);
      DFSUtil2(g, i, visited);
    }
  }
  printf("\n");
}

void DFSUtil2(Graph2 g, int i, bool *visited) {
  struct ListNode *p = g->A[i];  
  visited[i] = true;
  while (p) {
    if(!visited[p->v]) {
      printf("\n%d", p->v);
      DFSUtil2(g, p->v, visited);
    }
    p = p->next;
  }  
}

void BFS2(Graph2 g) {
  bool visited[g->v]; 
  int i;
  for (i = 0; i < g->v; i++) 
    visited[i] = false;
  for (i = 0; i < g->v; i++) {
    if (!visited[i] && g->A[i] != NULL)
      BFSUtil2(g, i, visited);
  }
  printf("\n");
}

void BFSUtil2(Graph2 g, int i, bool *visited) {
  struct ListNode *p;  
  struct Queue *q = CreateQueue();
  visited[i] = true;
  printf("\n%d", i);
  EnQueue(q, i);
  while (q->sz) { 
    i = DeQueue(q);
    for (p = g->A[i]; p; p = p->next) {
      if (!visited[p->v]) {
        visited[p->v] = true;      
        EnQueue(q, p->v);
        printf("\n%d", p->v);
      }
    }
  }
}

Graph2 Gen(float p, int v) { 
  Graph2 g = GraphNew2(v);
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      if ((float)(rand())/RAND_MAX < p)
        GraphEdgeInsert2(g, i, j);
    }
  }
  return g;
}

int Degree(Graph2 g, int v) {
  struct ListNode *p;
  int i = 0;
  for (p = g->A[v]; p != NULL; p = p->next) 
    if (p->v != i) i++;
  return i;
}

bool Path(Graph2 g, int v, int w) {
  if (v == w) return true;
  if (!g->A[v]) return false;
  // variables declaration and initialization 
  struct ListNode *p;  
  int i = 0;
  struct Queue *q = CreateQueue();
  bool visited[g->v]; 
  for (int i = 0; i < g->v; i++) 
    visited[i] = false;
  // BFS logic
  visited[v] = true;
  EnQueue(q, v);
  while (q->sz) { 
    i = DeQueue(q);
    for (p = g->A[i]; p; p = p->next) {
      if (!visited[p->v]) {
        visited[p->v] = true;      
        EnQueue(q, p->v);
        if (p->v == w) return true;
      }
    }
  }
  return false;
}

int ConnectedComponentsCount(Graph2 g) {
  int i, j = 0;
  bool visited[g->v]; 
  for (i = 0; i < g->v; i++) 
    visited[i] = false;
  for (i = 0; i < g->v; i++) {
    if (!visited[i] && g->A[i] != NULL) {
      j++;
      BFSUtilCc(g, i, visited);
    }  
  }
  return j;
}

void BFSUtilCc(Graph2 g, int i, bool *visited) {
  struct ListNode *p;  
  struct Queue *q = CreateQueue();
  visited[i] = true;
  EnQueue(q, i);
  while (q->sz) { 
    i = DeQueue(q);
    for (p = g->A[i]; p; p = p->next) {
      if (!visited[p->v]) {
        visited[p->v] = true;      
        EnQueue(q, p->v);
      }
    }
  }
}

void ConnectedComponentMembers(Graph2 g, int v) {
  if (!g->A[v]) {
    printf("the given vertex doesn't belong to graph g\n");
    return;
  } else {
    bool visited[g->v]; 
    for (int i = 0; i < g->v; i++) 
      visited[i] = false;
    BFSUtil2(g, v, visited);
  }
}

Graph2 GetSpanTreeDFS(Graph2 g, int v) {
  if (!g->A[v]) return NULL;
  bool visited[g->v]; 
  Graph2 g2 = GraphNew2(g->v);
  for (int i = 0; i < g->v; i++) 
    visited[i] = false;
  GraphEdgeInsert2(g2, v, v);
  SpanTreeUtil(g, g2, v, visited);
  return g2;
}

void SpanTreeUtil(Graph2 g, Graph2 g2, int i, bool *visited) {
  struct ListNode *p = g->A[i];;
  visited[i] = true;
  while (p) {
    if(!visited[p->v]) {
      GraphEdgeInsert2(g2, i, p->v);
      SpanTreeUtil(g, g2, p->v, visited);
    }
    p = p->next;
  }  
}

void PrintSpanTreeAsSummary(Graph2 g, int v) {
  if (!g->A[v]) return NULL;
  int space = 0;
  bool visited[g->v]; 
  for (int i = 0; i < g->v; i++) 
    visited[i] = false;
  printf("%d\n", v);
  SpanTreeAsSummaryUtil(g, v, visited, space);
  printf("\n");
}

void SpanTreeAsSummaryUtil(Graph2 g, int i, bool *visited, int space) {
  struct ListNode *p;  
  visited[i] = true;
  space++;
  for (p = g->A[i]; p; p = p->next) {
    if(!visited[p->v]) {
      for(int k = space; k; k--) printf(" ");
      printf("%d\n", p->v);
      SpanTreeAsSummaryUtil(g, p->v, visited, space);
    }
  }  
}

Graph2 GetMinDepthSpanTree(Graph2 g, int v) {
  if (!g->A[v]) return NULL;
  int i = 0;
  struct ListNode *p;  
  struct Queue *q = CreateQueue();
  bool visited[g->v]; 
  Graph2 g2 = GraphNew2(g->v);
  for (i = 0; i < g->v; i++) 
    visited[i] = false;
  // push the root
  visited[v] = true;
  GraphEdgeInsert2(g2, v, v);
  EnQueue(q, v);
  // core BFS 
  while (q->sz) { 
    i = DeQueue(q);
    for (p = g->A[i]; p; p = p->next) {
      if (!visited[p->v]) {
        visited[p->v] = true;      
        EnQueue(q, p->v);
        GraphEdgeInsert2(g2, i, p->v);
      }
    }
  }
  return g2;
}
 
struct ListNode *GetMinPath(Graph2 g, int root, int dest) {
  if (!g->A[root]) return NULL;
  struct ListNode *l = NULL;
  if (dest == root) return ListInsert(root, l);
  int pred[g->v];
  int i = 0;
  struct ListNode *p;    
  struct Queue *q = CreateQueue();
  bool visited[g->v]; 
  for (i = 0; i < g->v; i++) 
    visited[i] = false;
  // handle root
  visited[root] = true;
  pred[root] = -1;
  EnQueue(q, root);
  // core BFS 
  while (q->sz) { 
    i = DeQueue(q);
    for (p = g->A[i]; p; p = p->next) {
      if (!visited[p->v]) {
        visited[p->v] = true;
        pred[p->v] = i;
        EnQueue(q, p->v);
      }
    }
  }
  // filling mininum path list
  l = ListInsert(dest, l); 
  for (i = dest; pred[i] != root; i = pred[i])
    l = ListInsert(pred[i], l);
  l = ListInsert(root, l); 
  return l;
}

bool IsBipartite(Graph2 g) {
  int i;
  int v = 0; // arbitrary root
  struct ListNode *p;  
  struct Queue *q = CreateQueue();
  int color[g->v]; 
  for (i = 0; i < g->v; i++) 
    color[i] = -1;
  color[v] = 1;
  EnQueue(q, v);      
  while (q->sz) { 
    i = DeQueue(q);
    for (p = g->A[i]; p; p = p->next) {
      if (color[p->v] == -1) {
        EnQueue(q, p->v);
        color[p->v] = 1 - color[i];
      } else {
        if (color[p->v] == color[i] && i != p->v) return false;
      }
    }
  }
  return true;
}





