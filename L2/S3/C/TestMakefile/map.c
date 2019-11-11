#include "map.h"
#include <stdlib.h>
#include <assert.h>

struct couple* create_couple(int id, void* ptr, struct couple* next) {
  struct couple * cpl = (struct couple *)malloc(sizeof(struct couple));
  if (cpl==NULL) {
    fprintf(stderr, "map: create_couple: memory allocation failed");
    exit(1);
  }
  cpl->id = id;
  cpl->ptr = ptr;
  cpl->next = next;
  return cpl;
}

map new_map() {
  map d = (map)malloc(sizeof(struct map_));
  d->dico = create_couple(0,NULL,NULL);
  d->size = 1;
  return d;
}

void delete_map(map m) {
  assert(m!=NULL);
  while(m->dico != NULL) {
    struct couple * cpl = m->dico->next;
    free(m->dico);
    m->dico = cpl;
  }
  m->size = 0;
  free(m);
}

int get_id(map m, void* ptr) {
  assert(m!=NULL);
  struct couple * cpl = m->dico;
  while(cpl != NULL) {
    if (ptr == cpl->ptr) return cpl->id;
    cpl = cpl->next;
  }
  m->dico = create_couple(m->size++,ptr,m->dico);
  return m->dico->id;
}

void* get_ptr(map m, int id, size_t sz) {
  assert(m!=NULL);
  struct couple * cpl = m->dico;
  while(cpl != NULL) {
    if (id == cpl->id) return cpl->ptr;
    cpl = cpl->next;
  }
  void* ptr = malloc(sz);
  m->dico = create_couple(id,ptr,m->dico);
  m->size++;
  return m->dico->ptr;
}

