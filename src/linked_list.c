#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct node *head = NULL;

struct node *get_free_blk(size_t size)
{
  struct node *temp = head;

  while(temp)
  {
    printf("%p -> ", temp);
    if((temp->size > size) && temp->is_free)  
    {
      return temp;    
    }
  }
  printf("\n");
  return NULL;
}

void print_list()
{
  struct node *temp = head;
  while(temp)
  {
    printf("Address = %p, Size = %zu, Is_free = %d, Next_address= %p\n", temp, temp->size, temp->is_free, temp->next);
  }
}

struct node *get_head()
{
  return head;    
}

void update_head(struct node *new_head)
{
  printf("new_head = %p\n", new_head);
  head = new_head;    
}



