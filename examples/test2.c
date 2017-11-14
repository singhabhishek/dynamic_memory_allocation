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

  #ifdef CUSTOM_LIB
  printf("custom version\n");
  #else
  printf("glibc version\n");
  #endif
  
  // Begin Timer
  clock_t start = clock() ;

  printf("============================ Custom Calloc example ==========================\n\n");
  // Allocate 20*4 bytes in ptr1 pointer
  int *ptr1 = (int *)custom_calloc(sizeof(int),20);
  printf("Allocated 20*4 bytes using calloc ptr1 = %p\n", ptr1);
  int i = 0;
  for(i = 0; i < 20; i++)
  {
	printf("ptr1[%d] = %d\n", i, ptr1[i]);	  
  }
  
  printf("============================ Custom Realloc example ========================\n\n");
  // Allocate 5*4 bytes in ptr1 pointer
  ptr1 = (int*) custom_realloc(ptr1, sizeof(int)*5);
  printf("Allocated 5*4 bytes using realloc ptr1 = %p\nWe allocated 80 bytes for ptr1 intially, later we used realloc to change size to 20 bytes. Since intial chunk was sufficient to store 20 bytes, it uses same memory chunk.\n\n", ptr1);
  printf("\n------- Linked list of dynamically allocated memory\n");
  print_mem_list();
  printf("Linked list of dynamically allocated memory --------\n\n");

  ptr1 = (int*) custom_realloc(ptr1, sizeof(int)*100);
  printf("Allocated 100*4 bytes using realloc ptr1 = %p\nNow we have 80 bytes of memory chunk pointed by ptr1, later we used realloc to change size to 400 bytes. Since intial chunk was insufficient to store 400 bytes, it uses different memory chunk.\n\n", ptr1);
  printf("\n------- Linked list of dynamically allocated memory\n");
  print_mem_list();
  printf("Linked list of dynamically allocated memory --------\n\n");

  // Stop timer
  clock_t end = clock() ;
  double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC ;
  
  printf("Time taken = %lf\n", elapsed_time);

  return 0;    
}

