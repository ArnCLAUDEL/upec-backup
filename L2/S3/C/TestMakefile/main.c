#include <stdio.h>
#include <stdlib.h>

#include "serialization.h"
#include "graph.h"

////////////////////////////////////
// Main function

int main() {

  int i = 345;
  char* s = "helloword";
  float ftab[5] = { 0.4, 2, 1.5, 0.3, 7.3 };

  date d;
  d.day = 24;
  d.month = "September";
  d.year = 2011;

  date dtab[3];
  dtab[0].day = 14;
  dtab[0].month = "February";
  dtab[0].year = 2011;
  dtab[1].day = 18;
  dtab[1].month = "August";
  dtab[1].year = 1988;
  dtab[2].day = 1;
  dtab[2].month = "Januar";
  dtab[2].year = 1970;

  graph g = create_graph(4);
  set_graph_label(g,0,"a");
  set_graph_label(g,1,"b1");
  set_graph_label(g,2,"b2");
  set_graph_label(g,3,"c");
  set_graph_arrow(g,0,1);
  set_graph_arrow(g,0,3);
  set_graph_arrow(g,0,2);
  set_graph_arrow(g,1,3);
  set_graph_arrow(g,2,3);
  set_graph_arrow(g,3,0);

  FILE* fd = fopen("/tmp/test.sav","wb");
  if (fd==NULL) return 1;
  save_int(i,fd);
  save_string(s,fd);
  save_float_tab(ftab,5,fd);
  save_date(d,fd);
  save_date_tab(dtab,3,fd);
  save_graph(g,fd);
  fclose(fd);

  int j;
  char* t = NULL;
  float* gtab = NULL;
  int gtab_size = 0;
  date e;
  date* etab = NULL;
  int etab_size = 0;
  graph h = create_graph(0);

  fd = fopen("/tmp/test.sav","rb");
  if (fd==NULL) return 1;
  load_int(&j,fd);
  load_string(&t,fd);
  load_float_tab(&gtab,&gtab_size,fd);
  load_date(&e,fd);
  load_date_tab(&etab,&etab_size,fd);
  load_graph(&h,fd);
  fclose(fd);

  printf("send int \"%i\", get int \"%i\"\n", i, j);
  printf("send string \"%s\", get string \"%s\"\n", s, t);
  printf("send float tab[5] [| ");
  for(i=0;i<5;i++) printf("%f ",ftab[i]);
  printf("|]\n get float tab[%i] [| ", gtab_size);
  for(i=0;i<gtab_size;i++) printf("%f ",gtab[i]);
  printf("|]\n");
  printf("send date \"%i %s, the %ith\", get date \"%i %s, the %ith\"\n", d.year, d.month, d.day, e.year, e.month, e.day);
  printf("send date tab[3] [| ");
  for(i=0;i<3;i++) printf("\"%i %s, the %ith\" ",dtab[i].year,dtab[i].month,dtab[i].day);
  printf("|]\n get date tab[%i] [| ", etab_size);
  for(i=0;i<etab_size;i++) printf("\"%i %s, the %ith\" ",etab[i].year,etab[i].month,etab[i].day);
  printf("|]\n");
  printf("send graph\n");
  print_graph(g);
  printf(" get graph\n");
  print_graph(h);

  free(t);
  free(gtab);
  free(e.month);
  free(etab);
  delete_graph(h);

  return 0;
}



