#ifndef ARGS_H
#define ARGS_H

#include "image.h"

#define NOOPTION (NULL)

typedef struct option_s {
  const char* keyword;
  enum { OptVoid, OptInt, OptString} spec;
  union { void (*opt_void)();
  		  void (*opt_bw)(int); 
  		  void (*opt_r)(unsigned int, unsigned int); 
  		  void (*opt_c)(unsigned int, unsigned int, unsigned int, unsigned int); 
  		  void (*opt_str)(const char*); } fct;
  struct option_s* next;
} option_t;

option_t* 	opt_void(option_t* l, const char* kw, void (*f)());
option_t* 	opt_bw(option_t* l, const char* kw, void (*f)(int));
option_t* 	opt_r(option_t* l, const char* kw, void (*f)(unsigned int, unsigned int));
option_t* 	opt_c(option_t* l, const char* kw, void (*f)(unsigned int, unsigned int, unsigned int, unsigned int));
option_t* 	opt_str(option_t* l, const char* kw, void (*f)(const char*));
option_t* 	CreateOption(option_t* opt);	

void 		ProcessArguments(option_t* l, int argc, char* *argv);
#endif