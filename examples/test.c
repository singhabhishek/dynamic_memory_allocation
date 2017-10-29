#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/allocate.h"

int main(int argc, char *argv[])
{
  char *data = (char *)custom_calloc(sizeof(char),20);
  //char *data = (char *)custom_malloc(sizeof(char)*20);
  //data = (char *)custom_realloc(data, 40);
  strcpy(data, "Hello World");
  printf("%s\n", data);
  custom_free(data);
  return 0;    
}

