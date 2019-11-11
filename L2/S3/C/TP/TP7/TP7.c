#include <stdlib.h>
#include <stdio.h>

int* f(int n) {
  int j;
  int* q;
  printf("  0 - In f: %p, %d\n", &n, n);
  q = &j;
  printf("  1 - In f: %p, %d\n", q, *q);
  j = n;
  printf("  2 - In f: %p, %d\n", q, *q);
  return q;
}
 
void* g(int n) {
  int k;
  int* r;
  printf("  0 - In g: %p, %d\n", &n, n);
  r = &k;
  printf("  1 - In g: %p, %d\n", r, *r);
  k = n;
  printf("  2 - In g: %p, %d\n", r, *r);
  return NULL;
}
 
 
size_t strlen_1(const char* s) {
  size_t cptr = 0;  
  while(*(s+cptr) != 0){
      cptr++;
  }
  return cptr;
}

void strcpy_1(char* dst, const char* src) {
  int cpr =-1;
   do {
     cpr++;
    *(dst+cpr) = *(src+cpr);
  } while(*(src+cpr) != 0);
}

int strcmp_1(const char* s1, const char* s2) {
  if(strlen_1(s1) < strlen_1(s2)) return -1;
  if(strlen_1(s1) > strlen_1(s2)) return 1;
  return 0;
}

void* array_alloc(size_t len, size_t sz) {
    if(len == 0 || sz == 0) return NULL;
    size_t* s = (size_t*) malloc(len*sz+2*sizeof(size_t));
    *s = sz;
    *(s+1) = len;
    return (void*)(s+2);
}

void array_free(void* a) {
  
}

int main() {
    // Adresse des variables locales
  /*
  int i = 0;
  int* p = &i;
  printf("Before f: %p, %d\n", p, *p);
  p = f(1234);s
  printf("After f: %p, %d\n", p, *p);
  g(4321);
  printf("After g: %p, %d\n", p, *p);
  
    //Allocation, désallocation et erreur de segmentation
  
  int *p = NULL;
  printf("Contenu de *p : %d\n", *p);
  
  int* p = (int*) malloc(100*sizeof(int));
  int inf = 1;
  int cpr = 0;
  while(inf == 1) {
    printf("N°%d adresse : %p, valeur : %d\n",cpr,p,*p);
    p++;
    cpr++;
  }
  */
  /*
  int* p1 = calloc(100,sizeof(int));
  int cpr = 0;
  while(cpr < 101) {
    p1[cpr] = cpr;
     printf("N°%d adresse : %p, valeur : %d\n",cpr,p1,*(p1+cpr));
    cpr++;
  }
  free(p1);
  cpr = 0;
  while(cpr < 100) {
    printf("N°%d adresse : %p, valeur : %d\n",cpr,p1,*(p1+cpr));
    cpr++;
  }
  *//*
  int* p2 = calloc(100,sizeof(int));
  while(cpr<101) {
      printf("N°%d a.c.p1 : %p, v.p1 : %d, a.c.p2 : %p, v.p2 : %d\n",cpr,p1,*p1,p2,*p2);
      cpr++;
      p1++;
      p2++;
  }
  free(p2+1);
  */
  /*
    //Manipulation de chaînes de carctères
  char* s = "ouii";
  char* s2 = "non";
//   printf("%lu\n",strlen_1(s));
  char s1[100];
  strcpy_1(s1,s);
  printf("%d\n", strcmp_1(s,s2)); 
//  printf("%s %s",s1,s);
*/
  
  //Bibliothèque de manipulation de tableaux
  
  
  return EXIT_SUCCESS;
}
