#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/allocate.h"

#define CUSTOM_LIB=1

#ifndef CUSTOM_LIB
#define custom_malloc malloc
#define custom_calloc calloc
#define custom_free free
#define print_mem_list() 
#endif

int main(int argc, char *argv[])
{
  char data[20];
  #ifdef CUSTOM_LIB
  printf("custom version\n");
  strcpy(data, "Custom");
  #else
  printf("glibc version\n");
  strcpy(data, "GLIBC");
  #endif

  // Begin Timer
  clock_t start = clock();

  printf("============================ %s malloc for %d times ==========================\n\n", data, atoi(argv[1]));
  
  char *ptr1; 
  int i = 0;
  for(i=0; i<atoi(argv[1]); i++)
  	ptr1 = (char *)custom_malloc(sizeof(char)*20);
  
  clock_t end = clock() ;
  double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC ;
  printf("Time taken = %lf\n", elapsed_time);

  return 0;    
}

