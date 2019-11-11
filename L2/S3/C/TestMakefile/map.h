#ifndef MAP_H
#define MAP_H

#include <stdio.h>

struct couple {
  int            id;
  void*          ptr;
  struct couple* next;
};

typedef struct map_ {
  struct couple* dico;
  int            size;
} * map;

map new_map();
void delete_map(map m);

int   get_id(map m, void* ptr);
void* get_ptr(map m, int id, size_t sz);

#endif //MAP_H
