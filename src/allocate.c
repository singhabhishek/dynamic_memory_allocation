#include "../inc/allocate.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct node *tail = NULL;
pthread_mutex_t memory_lock;

struct node *global_head;

struct node *get_local_free_blk(size_t size)
{
  struct node *temp = global_head;
  while(temp)
  {
    if((temp->size >= size) && temp->is_free)  
    {
      return temp;    
    }
    temp = temp->next;
  }
  return NULL;
}

void *custom_malloc(size_t size)
{
  size_t total_size;
  void *blk;
  struct node *head = NULL;
  if(!size)
    return NULL;
  pthread_mutex_lock(&memory_lock);
  head = get_local_free_blk(size);
  if(head)
  {
    head->is_free = 0;
    pthread_mutex_unlock(&memory_lock);
    return (void*)(head + 1);
  }
  total_size = sizeof(struct node) + size;
  blk = sbrk(total_size);
  if(blk == (void*)-1)
  {
    pthread_mutex_unlock(&memory_lock);
    return NULL;
  }

  head = blk;
  head->size = size;
  head->is_free = 0;
  head->next = NULL;
  if(!global_head)
      global_head = head;
  if(tail)
      tail->next = head;
  tail = head;
  pthread_mutex_unlock(&memory_lock);
  return (void *)(head + 1);
}

void custom_free(void *ptr)
{
  struct node *head, *tmp;
  void *programbreak;
  if(!ptr)
    return;
  pthread_mutex_lock(&memory_lock);
  head = (struct node*)ptr - 1;
  programbreak = sbrk(0);

  if((char*)ptr + head->size == programbreak)
  {
    if(global_head == tail)
    {
      global_head = NULL;
      tail = NULL;
    }
    else
    {
      printf("Inside Else ************************************\n");
      tmp = global_head;
      while(tmp)
      {
        if(tmp->next == tail)
        {
	  printf("Inside if *****************\n");
          tmp->next = NULL;
          tail = tmp;
        }
        tmp = tmp->next;
      }
    }
    sbrk(0 - head->size - sizeof(struct node));
    pthread_mutex_unlock(&memory_lock);
    return;
  }
  head->is_free = 1;
  pthread_mutex_unlock(&memory_lock);
}

void *custom_calloc(size_t nmemb, size_t size)
{
  size_t s;
  void *blk;
  if(!nmemb || !size)
      return NULL;
  s = nmemb*size;
  if(size != s/nmemb)
      return NULL;
  blk = custom_malloc(s);
  if(!blk)
    return NULL;
  memset(blk, 0, s);
  return blk;
}

void *custom_realloc(void *ptr, size_t size)
{
  struct node *head;
  void *ret;
  if(!ptr || !size)
    return custom_malloc(size);
  head = (struct node *)ptr - 1;
  if(head->size >= size)
    return ptr;
  ret = custom_malloc(size);
  if(ret)
  {
    memcpy(ret, ptr, head->size);
    custom_free(ptr);
  }
  return ret;
}

void print_mem_list()
{
  struct node *curr = global_head;
  printf("Head = %p, tail = %p,\n", (void*)((char*)curr + 24), (void*)((char*)tail + 24));
  while(curr)
  {
	printf("address = %p, chunk_size = %zu bytes, memory_available? = %u\n", (void*)((char*)curr  +24), curr->size, curr->is_free);	  
	curr = curr->next;
  }
}
