#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
#include <stdbool.h>

struct node
{
  size_t size;
  bool is_free;
  struct node *next;
};

#endif //LINKED_LIST_H
