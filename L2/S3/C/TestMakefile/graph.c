#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

graph create_graph(int nb_node) {
  graph g; int i;
  g.nb_node = nb_node;
  g.nodes = (node**)malloc(nb_node*sizeof(node*));
  for(i=0;i<nb_node;i++) {
    g.nodes[i] = (node*)malloc(sizeof(node));
    g.nodes[i]->label = NULL;
    g.nodes[i]->nb_succ = 0;
    g.nodes[i]->succ = NULL;
    g.nodes[i]->nb_pred = 0;
    g.nodes[i]->pred = NULL;
  }
  return g;
}

void delete_graph(graph g) {
  int i;
  for(i=0;i<g.nb_node;i++) {
    free(g.nodes[i]->label);
    free(g.nodes[i]->succ);
    free(g.nodes[i]->pred);
    free(g.nodes[i]);
  }
  free(g.nodes);
}

void set_graph_label(graph g, int n, const char* label) {
  assert(n<g.nb_node);
  free(g.nodes[n]->label);

  g.nodes[n]->label = (char*)malloc(sizeof(char)*(strlen(label)+1));
  strcpy(g.nodes[n]->label, label);  
}

void set_graph_arrow(graph g, int n1, int n2) {
  assert(n1<g.nb_node);
  assert(n2<g.nb_node);

  g.nodes[n1]->nb_succ++;
  g.nodes[n1]->succ = realloc(g.nodes[n1]->succ, sizeof(node*)*g.nodes[n1]->nb_succ);
  g.nodes[n1]->succ[g.nodes[n1]->nb_succ-1] = g.nodes[n2];

  g.nodes[n2]->nb_pred++;
  g.nodes[n2]->pred = realloc(g.nodes[n2]->pred, sizeof(node*)*g.nodes[n2]->nb_pred);
  g.nodes[n2]->pred[g.nodes[n2]->nb_pred-1] = g.nodes[n1];
}

void print_graph(graph g) {
  int i;
  for(i=0;i<g.nb_node;i++) {
    int j;
    printf("node %i [%s] => ", i, g.nodes[i]->label);
    for(j=0;j<g.nodes[i]->nb_succ;j++)
      printf("%s ", g.nodes[i]->succ[j]->label);
    //printf("| ", i, g.nodes[i]->label);
    printf("| ");
    for(j=0;j<g.nodes[i]->nb_pred;j++)
      printf("%s ", g.nodes[i]->pred[j]->label);
    //printf("\n", i, g.nodes[i]->label);
    printf("\n");
  }
}




