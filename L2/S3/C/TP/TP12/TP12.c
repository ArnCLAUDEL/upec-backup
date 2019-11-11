#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NOOPTION  NULL

typedef struct option_s {
  const char* keyword;
  enum { OptVoid = 1, OptInt = 2, OptString = 3, OptFloat = 4 } spec;
  union {
    void (*opt_void)();
    void (*opt_int)(int);
    void (*opt_str)(const char*);
    void (*opt_float)(float);
  } fct;
  struct option_s* next;
} option_t;



option_t* opt_void(option_t* l, const char* kw, void (*f)()) {
   option_t* new_option = malloc(sizeof(option_t));
   new_option->keyword = kw;
   new_option->spec = OptVoid;
   new_option->fct.opt_void = f;
   new_option->next = l;
   return new_option;
 }

option_t* opt_int(option_t* l, const char* kw, void (*f)(int)) {
   option_t* new_option = malloc(sizeof(option_t));
   new_option->keyword = kw;
   new_option->spec = OptInt;
   new_option->fct.opt_int = f;
   new_option->next = l;
   return new_option;
 }
 
 option_t* opt_float(option_t* l, const char* kw, void (*f)(float)) {
   option_t* new_option = malloc(sizeof(option_t));
   new_option->keyword = kw;
   new_option->spec = OptFloat;
   new_option->fct.opt_float = f;
   new_option->next = l;
   return new_option;
 }
 
 option_t* opt_str(option_t* l, const char* kw, void (*f)(const char*)) {
   option_t* new_option = malloc(sizeof(option_t));
   new_option->keyword = kw;
   new_option->spec = OptString;
   new_option->fct.opt_str = f;
   new_option->next = l;
   return new_option;
 }
 /*
int stringToInt(char* s) {
	
}

float stringToFloat(char* s) {

}
*/
 void process_options(option_t* l, int argc, char* *argv) {
   int i = 0;
   option_t* optr = l;
   for(i = 0; i < argc; i++) printf("%s ",argv[i]);
   printf("\n");
	 bool wExit;
   for(i = 1; i < argc; i++) {
		optr = l;
		wExit = false;
		while(wExit == false && strcmp(argv[i],optr->keyword)) {
			optr = optr->next;
			if(optr == NULL) wExit = true;
		}
		if(!wExit) {
			if(optr->spec == 1) {
				optr->fct.opt_void();
			} else if(optr->spec == 2) {
				i++;
				optr->fct.opt_int(atoi(argv[i]));
	   		} else if(optr->spec == 3) {
				i++;
				optr->fct.opt_str(argv[i]);
			} else if(optr->spec == 4) {
				i++;
				optr->fct.opt_float(atof(argv[i]));
			}
		} else {
			printf("Unknow option.\n");
		}
   }
 }


void f1(const char* str) {
  printf("F1: %s\n", str);
}
 
void f2(int i) {
  printf("F2: %d\n", i);
}
 
void f3() {
  printf("F3: no param\n");
}
 
void f4(float f) {
  printf("F4: %f\n", f);
}
int main(int argc, char** argv) {
  option_t* opt = NOOPTION;
  opt = opt_str(opt, "-a", f1);
  opt = opt_int(opt, "-b", f2);
  opt = opt_void(opt, "-c", f3);
  opt = opt_float(opt, "-d", f4);
  process_options(opt, argc, argv);
	return EXIT_SUCCESS;
}
