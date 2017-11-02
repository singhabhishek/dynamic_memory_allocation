#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/allocate.h"

#ifndef CUSTOM_LIB
#define custom_malloc malloc
#define custom_calloc calloc
#define custom_free free
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
  
  // Allocate 20 bytes in ptr1 pointer, 40 bytes in ptr2 pointer, 60 bytes in ptr3 pointer
  char *ptr1 = (char *)custom_malloc(sizeof(char)*20);
  printf("Allocated 20 bytes using calloc ptr1 = %p\n", ptr1);
  char *ptr2 = (char *)custom_malloc(sizeof(char)*40);
  printf("Allocated 40 bytes using calloc ptr2 = %p\n", ptr2);
  char *ptr3 = (char *)custom_malloc(sizeof(char)*60);
  printf("Allocated 60 bytes using calloc ptr3 = %p\n", ptr3);

  // Free ptr1
  custom_free(ptr1);
  ptr1 = NULL;
  printf("Freed ptr1\n");
 
  // Allocate 20 bytes in ptr4 pointer. It uses same block used by ptr1.
  char *ptr4 = (char *)custom_calloc(sizeof(char),20);
  printf("Allocated 20 bytes using calloc ptr4 = %p\n", ptr4);

  // Srop timer
  clock_t end = clock() ;

  double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC ;
  
  // Free ptr2, ptr3, ptr4
  custom_free(ptr2);
  custom_free(ptr3);
  custom_free(ptr4);
  ptr2 = NULL;
  ptr3 = NULL;
  ptr4 = NULL;
  printf("Freed ptr2, ptr3, ptr4\n");
  printf("Time taken = %lf\n", elapsed_time);

  return 0;    
}

