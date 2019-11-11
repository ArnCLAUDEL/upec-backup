#include "serialization.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>


////////////////////////////////////
// Basic types

bool save_int(int i, FILE* fdesc) {
  return (fwrite(&i,sizeof(int),1,fdesc) == 1);
}

bool load_int(int *ip, FILE* fdesc) {
  return (fread(ip,sizeof(int),1,fdesc) == 1);
}

bool save_char(char c, FILE* fdesc) {
  return (fwrite(&c,sizeof(char),1,fdesc) == 1);
}

bool load_char(char *cp, FILE* fdesc) {
  return (fread(cp,sizeof(char),1,fdesc) == 1);
}


////////////////////////////////////
// Arrays

bool save_float_tab(float* tab, int size, FILE* fdesc) {

  // save the array size
  if (!save_int(size, fdesc)) return false;

  // save the array
  return ((unsigned int)size == fwrite(tab, sizeof(float), size, fdesc));
}

bool load_float_tab(float* *tabp, int *sizep, FILE* fdesc){

  // load the array size
  if (!load_int(sizep, fdesc)) return false;

  // allocate enough memory to store the array
  if ((*tabp = (float*)malloc(*sizep*sizeof(float))) == NULL)
    return false;

  // load the array in the allocated memory
  return ((unsigned int)(*sizep) == fread(*tabp, sizeof(float), *sizep, fdesc));
}

bool save_string(char* s, FILE* fdesc) {

  // save the string length
  int size = strlen(s);
  if (!save_int(size,fdesc)) return false;

  // save the string
  return ((unsigned int)size == fwrite(s,sizeof(char),size,fdesc));
}

bool load_string(char* *sp, FILE* fdesc) {

  // load the string length
  int size;
  if (!load_int(&size,fdesc)) return false;

  // allocate enough memory to store the string
  *sp = (char*)malloc((size+1)*sizeof(char));
  if (*sp == NULL) return false;

  // set the last character to '\0'
  (*sp)[size] = '\0';

  // load the string in the allocated memory
  return ((unsigned int)size == fread(*sp,sizeof(char),size,fdesc));
}


////////////////////////////////////
// Struct

bool save_date(date d, FILE* fdesc) {

  // save the struct fields one after the other
  if (!save_char(d.day, fdesc)) return false;
  if (!save_string(d.month, fdesc)) return false;
  if (!save_int(d.year, fdesc)) return false;

  return true;
}

bool load_date(date *dp, FILE* fdesc) {

  // load the struct fields one after the other
  if (!load_char(&(dp->day), fdesc)) return false;
  if (!load_string(&(dp->month), fdesc)) return false;
  if (!load_int(&(dp->year), fdesc)) return false;

  return true;
}

bool save_date_tab(date* tab, int size, FILE* fdesc) {

  // save the array size
  if (!save_int(size, fdesc)) return false;

  // save each element
  int i = 0;
  for(i=0;i<size;i++)
    if (!save_date(tab[i],fdesc)) return false;

  return true;
}

bool load_date_tab(date* *tabp, int *sizep, FILE* fdesc) {

  // load the array size
  if (!load_int(sizep, fdesc)) return false;

  // allocate enough memory to store the array
  if ((*tabp = (date*)malloc(*sizep*sizeof(date))) == NULL)
    return false;

  // load the array in the allocated memory
  int i = 0;
  for(i=0;i<*sizep;i++)
    if (!load_date(&((*tabp)[i]),fdesc)) return false;

  return true;
}


////////////////////////////////////
// Pointer

bool save_int_ptr(int* ptr, map m, FILE* fdesc) {
  int id = get_id(m,(void*)ptr);
  return save_int(id,fdesc);
}

bool load_int_ptr(int* *ptrp, map m, FILE* fdesc) {
  int id;
  if (!load_int(&id,fdesc)) return false;
  *ptrp = (int*)get_ptr(m,id,sizeof(int));
  return true;
}


////////////////////////////////////
// Graph

bool save_node(node n, map m, FILE* fdesc) {
  if (!save_string(n.label,fdesc)) return false;
  if (!save_node_ptr_tab(n.succ,n.nb_succ,m,fdesc)) return false;
  if (!save_node_ptr_tab(n.pred,n.nb_pred,m,fdesc)) return false;
  return true;
}

bool load_node(node *np, map m, FILE* fdesc) {
  if (!load_string(&(np->label),fdesc)) return false;
  if (!load_node_ptr_tab(&(np->succ),&(np->nb_succ),m,fdesc)) return false;
  if (!load_node_ptr_tab(&(np->pred),&(np->nb_pred),m,fdesc)) return false;
  return true;
}

bool save_node_ptr(node* ptr, map m, FILE* fdesc) {
  int id = get_id(m,(void*)ptr);
  return save_int(id, fdesc);
}

bool load_node_ptr(node* *ptrp, map m, FILE* fdesc) {
  int id;
  if (!load_int(&id, fdesc)) return false;
  *ptrp = (node*)get_ptr(m,id,sizeof(node));
  return true;
}

bool save_pointed_node(node* ptr, map m, FILE* fdesc) {
  if (!save_node_ptr(ptr, m, fdesc)) return false;
  return save_node(*ptr, m, fdesc);
}

bool load_pointed_node(node* *ptrp, map m, FILE* fdesc) {
  if (!load_node_ptr(ptrp, m, fdesc)) return false;
  return load_node(*ptrp, m, fdesc);
}

bool save_node_ptr_tab(node** tab, int size, map m, FILE* fdesc) {
  int i;
  if (!save_int(size, fdesc)) return false;
  for(i=0;i<size;i++)
    if (!save_node_ptr(tab[i], m, fdesc)) return false;
  return true;
}

bool load_node_ptr_tab(node** *tabp, int *sizep, map m, FILE* fdesc) {
  int i;
  if (!load_int(sizep, fdesc)) return false;
  *tabp = (node**)malloc(*sizep*sizeof(node*));
  if (*tabp == NULL) return false;
  for(i=0;i<*sizep;i++)
    if (!load_node_ptr(&((*tabp)[i]), m, fdesc)) return false;
  return true;
}

bool save_pointed_node_tab(node** tab, int size, map m, FILE* fdesc) {
  int i;
  if (!save_int(size, fdesc)) return false;
  for(i=0;i<size;i++)
    if (!save_pointed_node(tab[i], m, fdesc)) return false;
  return true;
}

bool load_pointed_node_tab(node** *tabp, int *sizep, map m, FILE* fdesc) {
  int i;
  if (!load_int(sizep, fdesc)) return false;
  *tabp = (node**)malloc(*sizep*sizeof(node*));
  if (*tabp == NULL) return false;
  for(i=0;i<*sizep;i++)
    if (!load_pointed_node(&((*tabp)[i]), m, fdesc)) return false;
  return true;
}

bool save_graph(graph g, FILE* fdesc) {
  map m = new_map();
  bool ret = save_pointed_node_tab(g.nodes,g.nb_node,m,fdesc);
  delete_map(m);
  return ret;
}

bool load_graph(graph *gp, FILE* fdesc) {
  map m = new_map();
  bool ret = load_pointed_node_tab(&(gp->nodes),&(gp->nb_node),m,fdesc);
  delete_map(m);
  return ret;
}





/*



bool save_node(node* n, FILE* fdesc, dico* d) {

  int id, i;

  // get the id associated with address n
  if (!get_id(*d,(void*)n,&id)) *d = add_ptr(*d,(void*)n,&id);

  // save id
  if (!save_int(id,fdesc)) return false;

  // save label
  if (!save_string(n->label,fdesc)) return false;

  // save nb_succ
  if (!save_int(n->nb_succ,fdesc)) return false;

  // save successors id
  for(i=0;i<n->nb_succ;i++) {
    int succ_id;
    // get the id associated with ith successor
    if (!get_id(*d,(void*)n->succ[i],&succ_id)) *d=add_ptr(*d,(void*)n->succ[i],&succ_id);
    // save successor's id
    if (!save_int(succ_id,fdesc)) return false;
  }

  // save nb_pred
  if (!save_int(n->nb_pred,fdesc)) return false;

  // save predecessors id 
  for(i=0;i<n->nb_pred;i++) {
    int pred_id;
    // get the id associated with ith predecessor
    if (!get_id(*d,(void*)n->pred[i],&pred_id)) *d=add_ptr(*d,(void*)n->pred[i],&pred_id);
    // save predecessor's id
    if (!save_int(pred_id,fdesc)) return false;
  }

  return true;
}

bool save_graph(graph g, FILE* fdesc) {

  if (!save_int(g.nb_node,fdesc)) return false;

  int i;
  dico d = new_dico();
  for(i=0;i<g.nb_node;i++)
    if (!save_node(g.nodes[i],fdesc,&d)) return false;
  delete_dico(d);
  return true;
}



bool load_node(node** np, FILE* fdesc, dico* d) {

  int id, i;

  // load id
  if (!load_int(&id,fdesc)) return false;

  // get the address associated with id
  if (!get_ptr(*d,id,(void**)np)) *d = add_id(*d,id,(void*)(*np = (node*)malloc(sizeof(node))));

  // load label
  if (!load_string(&((*np)->label),fdesc)) return false;

  // load nb_succ 
  if (!load_int(&((*np)->nb_succ),fdesc)) return false;

  // allocation of succ array 
  (*np)->succ = (node**)malloc((*np)->nb_succ*sizeof(node*));

  // load successors id 
  for(i=0;i<(*np)->nb_succ;i++) {
    int succ_id;
    // load successor's id 
    if (!load_int(&succ_id,fdesc)) return false;
    // get the address associated with succ_id 
    if (!get_ptr(*d,succ_id,(void**)&((*np)->succ[i]))) *d = add_id(*d,succ_id,(void*)((*np)->succ[i] = (node*)malloc(sizeof(node))));
  }


  // load nb_pred 
  if (!load_int(&((*np)->nb_pred),fdesc)) return false;

  // allocation of pred array 
  (*np)->pred = (node**)malloc((*np)->nb_pred*sizeof(node*));

  // load predecessors id 
  for(i=0;i<(*np)->nb_pred;i++) {
    int pred_id;
    // load predecessor's id 
    if (!load_int(&pred_id,fdesc)) return false;
    // get the address associated with pred_id 
    if (!get_ptr(*d,pred_id,(void**)&((*np)->pred[i]))) *d = add_id(*d,pred_id,(void*)((*np)->pred[i] = (node*)malloc(sizeof(node))));
  }

  return true;
}

bool load_graph(graph* g, FILE* fdesc) {

  if (!load_int(&(g->nb_node),fdesc)) return false;

  g->nodes = (node**)malloc(g->nb_node*sizeof(node*));

  int i;
  dico d = new_dico();
  for(i=0;i<g->nb_node;i++)
    if (!load_node(&(g->nodes[i]),fdesc,&d)) return false;
  delete_dico(d);
  return true;
}

*/
