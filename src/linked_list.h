#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

struct node
{
  size_t size;
  bool is_free;
  struct node *next;
};

struct node *get_free_blk(size_t size);
void print_list();
struct node *get_head();
void update_head(struct node *head);


#endif //LINKED_LIST_H
