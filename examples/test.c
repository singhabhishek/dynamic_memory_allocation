#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/allocate.h"

//#define CUSTOM_LIB=1

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

  printf("============================ Custom malloc & free examples ==========================\n\n");
  // Allocate 20 bytes in ptr1 pointer, 40 bytes in ptr2 pointer, 60 bytes in ptr3 pointer
  char *ptr1 = (char *)custom_malloc(sizeof(char)*20);
  printf("Allocated 20 bytes using malloc ptr1 = %p\n", ptr1);
  char *ptr2 = (char *)custom_malloc(sizeof(char)*40);
  printf("Allocated 40 bytes using malloc ptr2 = %p\n", ptr2);
  char *ptr3 = (char *)custom_malloc(sizeof(char)*80);
  printf("Allocated 80 bytes using malloc ptr3 = %p\n", ptr3);
  char *ptr4 = (char *)custom_malloc(sizeof(char)*60);
  printf("Allocated 60 bytes using malloc ptr4 = %p\n", ptr4);
  char *ptr5 = (char *)custom_malloc(sizeof(char)*80);
  printf("Allocated 80 bytes using malloc ptr5 = %p\n", ptr5);

  // Free ptr1
  custom_free(ptr1);
  ptr1 = NULL;
  printf("Freed 20 bytes pointed by ptr1\n");
  
  // Free ptr3
  custom_free(ptr3);
  ptr3 = NULL;
  printf("Freed 80 bytes pointed by ptr3\n");
 
  // Free ptr4
  custom_free(ptr4);
  ptr4 = NULL;
  printf("Freed 60 bytes pointed by ptr4\n");

  printf("\n------- Linked list of dynamically allocated memory\n");
  print_mem_list();
  printf("Linked list of dynamically allocated memory --------\n");
 
  // Allocate 20 bytes in ptr6 pointer. It uses same block used by ptr1.
  char *ptr6 = (char *)custom_malloc(sizeof(char)*20);
  printf("\nAllocated 20 bytes using malloc ptr6 = %p\nSince we freed ptr1 and it was the first available block of sufficient size, it was used for memory allocation. In this case sbrk() is not called, because we already had memory chunk available with us which was not at the end of the heap memory and was not released backed to the OS.\n\n", ptr6);
  printf("\n------- Linked list of dynamically allocated memory\n");
  print_mem_list();
  printf("Linked list of dynamically allocated memory --------\n");

  // Allocate 60 bytes in ptr7 pointer. It uses same block used by ptr1.
  char *ptr7 = (char *)custom_malloc(sizeof(char)*60);
  printf("\nAllocated 60 bytes using malloc ptr7 = %p\nIn this case we had 2 memory chunks of 80 bytes pointed by ptr3 and 60 bytes pointed by ptr4. Since in Linked list ptr3 comes before ptr4 and has sufficient memort for allocation, that memory chunk is used\n\n", ptr7);
  printf("\n------- Linked list of dynamically allocated memory\n");
  print_mem_list();
  printf("Linked list of dynamically allocated memory --------\n");

  custom_free(ptr5);
  ptr5 = NULL;
  printf("Freed 20 bytes pointed by ptr1\n");
  printf("\nFreed 80 bytes pointed by ptr4\nSince the memory chunk pointed by ptr5 was last in the linked list, it was given back to OS when it was freed.");
  printf("\n------- Linked list of dynamically allocated memory\n");
  print_mem_list();
  printf("Linked list of dynamically allocated memory --------\n");


  // Free ptr2, ptr6, ptr7
  custom_free(ptr2);
  custom_free(ptr7);
  custom_free(ptr6);
  ptr2 = NULL;
  ptr6 = NULL;
  ptr7 = NULL;
  printf("Freed ptr2, ptr6, ptr7\n");

// Stop timer
  clock_t end = clock() ;

  double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC ;
  
  printf("Time taken = %lf\n", elapsed_time);

  return 0;    
}

