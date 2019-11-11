#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdio.h>
#include <stdbool.h>
#include "map.h"

////////////////////////////////////
// Basic types

bool save_int(int i, FILE* fdesc);
bool load_int(int *ip, FILE* fdesc);

bool save_char(char c, FILE* fdesc);
bool load_char(char *cp, FILE* fdesc);


////////////////////////////////////
// Arrays

bool save_float_tab(float* tab, int size, FILE* fdesc);
bool load_float_tab(float* *tabp, int *sizep, FILE* fdesc);

bool save_string(char* s, FILE* fdesc);
bool load_string(char* *sp, FILE* fdesc);


////////////////////////////////////
// Structure

typedef struct date_ {
  char day;
  char* month;
  int year;
} date;

bool save_date(date d, FILE* fdesc);
bool load_date(date *dp, FILE* fdesc);

bool save_date_tab(date* tab, int size, FILE* fdesc);
bool load_date_tab(date* *tabp, int *sizep, FILE* fdesc);


////////////////////////////////////
// Pointer

bool save_int_ptr(int* ptr, map m, FILE* fdesc);
bool load_int_ptr(int* *ptrp, map m, FILE* fdesc);

////////////////////////////////////
// Example: graph data structure

#include "graph.h"

bool save_node(node n, map m, FILE* fdesc);
bool load_node(node *np, map m, FILE* fdesc);

bool save_node_ptr(node* ptr, map m, FILE* fdesc);
bool load_node_ptr(node* *ptrp, map m, FILE* fdesc);

bool save_pointed_node(node* ptr, map m, FILE* fdesc);
bool load_pointed_node(node* *ptrp, map m, FILE* fdesc);

bool save_node_ptr_tab(node** tab, int size, map m, FILE* fdesc);
bool load_node_ptr_tab(node** *tabp, int *sizep, map m, FILE* fdesc);

bool save_pointed_node_tab(node** tab, int size, map m, FILE* fdesc);
bool load_pointed_node_tab(node** *tabp, int *sizep, map m, FILE* fdesc);

bool save_graph(graph g, FILE* fdesc);
bool load_graph(graph *gp, FILE* fdesc);


#endif //SERIALIZATION_H
