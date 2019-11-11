#ifndef ARGS_C
#define ARGS_C

// lancé un programme avec une option GDB:
//	gcc -g
// gdb tp12.exe
// run

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "args.h"
#include "image.h"
#include "menu.h"

option_t* opt_void(option_t* l, const char* kw, void (*f)()){
	option_t* new_option = malloc(sizeof(option_t));
	new_option->keyword = kw;
	new_option->spec = OptVoid;
	new_option->fct.opt_void = f;
	new_option->next = l;
	return new_option;
}

option_t* opt_bw(option_t* l, const char* kw, void (*f)(int)){
	option_t* new_option = malloc(sizeof(option_t));
	new_option->keyword = kw;
	new_option->spec = OptInt;
	new_option->fct.opt_bw = f;
	new_option->next = l;
	return new_option;
}
option_t* opt_r(option_t* l, const char* kw, void (*f)(unsigned int, unsigned int)){
	option_t* new_option = malloc(sizeof(option_t));
	new_option->keyword = kw;
	new_option->spec = OptInt;
	new_option->fct.opt_r = f;
	new_option->next = l;
	return new_option;
}
option_t* opt_c(option_t* l, const char* kw, void (*f)(unsigned int, unsigned int, unsigned int, unsigned int)){
	option_t* new_option = malloc(sizeof(option_t));
	new_option->keyword = kw;
	new_option->spec = OptInt;
	new_option->fct.opt_c = f;
	new_option->next = l;
	return new_option;
}

option_t* opt_str(option_t* l, const char* kw, void (*f)(const char*)){
	option_t* new_option = malloc(sizeof(option_t));
	new_option->keyword = kw;
	new_option->spec = OptString;
	new_option->fct.opt_str = f;
	new_option->next = l;
	return new_option;
}





void ProcessArguments(option_t* l, int argc, char* *argv){
  int i = 0;
  for(i = 0; i < argc; i++)  printf("%s ", argv[i]);
  option_t* cursor;
  printf("\n\n");
  i = 1;
  bool done = false;
  for(i = 1; i < argc ; i+=2){
    done = false;
    cursor = l;
    while(cursor != NULL && done == false){
      if(strcmp(cursor->keyword, argv[i]) == 0){  //strcmp renvoi 0 si c'est egal
        if(cursor->spec == OptVoid)       {cursor->fct.opt_void(); i--; done = true;}
        else if(cursor->spec == OptString)   {cursor->fct.opt_str(argv[(i+1)]);}
        else if(cursor->spec == OptInt){

          if((strcmp(cursor->keyword,"-bw") == 0) || (strcmp(cursor->keyword, "-black_white") == 0) )
            cursor->fct.opt_bw(atoi(argv[(i+1)])); // effectue la conversion *char en int

          if((strcmp(cursor->keyword,"-r") == 0) || (strcmp(cursor->keyword, "-resize") == 0) ) {
            cursor->fct.opt_r(atoi(argv[(i+1)]), atoi(argv[(i+2)]));
            i++;
          }
          if((strcmp(cursor->keyword,"-c") == 0) || (strcmp(cursor->keyword, "-crop") == 0) ) {
            cursor->fct.opt_c(atoi(argv[(i+1)]), atoi(argv[(i+2)]), atoi(argv[(i+3)]), atoi(argv[(i+4)]));
            i += 3;
          }
        }     
      }
      cursor = cursor->next;
    }
}
}


option_t* CreateOption(option_t* opt){
  	opt = opt_str(opt, "-i", ArgLoad);
  	opt = opt_str(opt, "-open", ArgLoad);
  	opt = opt_str(opt, "-load", ArgLoad);
    
    opt = opt_str(opt, "-o", ArgSave);
    opt = opt_str(opt, "-save", ArgSave);
    
    opt = opt_void(opt, "-p", ArgPrintDataImg);
    opt = opt_void(opt, "-print", ArgPrintDataImg);
    
    opt = opt_void(opt, "-n", ArgNegative);
    opt = opt_void(opt, "-negative", ArgNegative);
    
    opt = opt_void(opt, "-g", ArgGrayScale);
    opt = opt_void(opt, "-grayscale", ArgGrayScale);

    opt = opt_bw(opt, "-bw", ArgBlackWhiteSeuil);
    opt = opt_bw(opt, "-black_white", ArgBlackWhiteSeuil);
    
    opt = opt_void(opt, "-bwAvg", ArgBlackWhiteAVG);

    opt = opt_void(opt, "-bwMed", ArgBlackWhiteMediane);

    opt = opt_void(opt, "-RH", Arghflip);
    opt = opt_void(opt, "-RV", Argvflip);

  	opt = opt_void(opt, "-RR", ArgReturnRight);
  	opt = opt_void(opt, "-RL", ArgReturnLeft); 
    
  	opt = opt_c(opt, "-c", ArgCrop);
  	opt = opt_c(opt, "-crop", ArgCrop);
  	
    opt = opt_r(opt, "-r", ArgResize);
    opt = opt_r(opt, "-resize", ArgResize);

    opt = opt_void(opt, "-h", Help);
    opt = opt_void(opt, "-H", Help);
    opt = opt_void(opt, "-help", Help);
    opt = opt_void(opt, "-Help", Help);
    opt = opt_void(opt, "--help", Help);
    opt = opt_void(opt, "-man", Help);
    

      return opt;
}
#endif