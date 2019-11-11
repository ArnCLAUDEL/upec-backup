#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct node_ {
  char*           label;   // label of a node
  int             nb_succ; // number of successors
  struct node_ ** succ;    // array of pointers to the successor nodes
  int             nb_pred; // number of predecessors
  struct node_ ** pred;    // array of pointers to the predecessor nodes
} node;

typedef struct graph_ {
  int     nb_node; // number of nodes in the graph
  node ** nodes;   // array of pointers to the nodes
} graph;

graph create_graph(int nb_node);
void  delete_graph(graph g);
void  print_graph(graph g);

void  set_graph_label(graph g, int n, const char* label);
void  set_graph_arrow(graph g, int n1, int n2);

#endif //GRAPH_H
