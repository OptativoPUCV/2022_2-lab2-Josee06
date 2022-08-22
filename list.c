#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) 
{
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() 
{
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void *firstList(List *list)
{
  if (!list->head) return NULL;
  list->current = list->head;
  return (list->head->data);
}

void *nextList(List *list) 
{
  if(  !list->current || !list->current->next)
  { 
    return NULL;
  }
  list->current=list->current->next;
  return(list->current->data);
}

void *lastList(List *list) 
{ 
  if(!list->tail)
  {
    return NULL;
  }
  list->current=list->tail;
  return(list->tail->data);
}

void *prevList(List *list) 
{ 
  if(!list->current || !list->current->prev){ 
    return NULL;
  }
  list->current=list->current->prev;
  return(list->current->data);
}

void pushFront(List *list, void *data) 
{
  Node* n = createNode(data);
  n->next= list->head;
  if(list->head==NULL){
    list->head = n;  
    list->tail=n;
  }
  else{
    list->head->prev=n;
  }
  list->head = n;
  n->prev=NULL;
}


void pushBack(List *list, void *data) 
{
  list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List *list, void *data) 
{
  Node* n = createNode(data);
  if(list->head==NULL)
  {
    list->head=n;
    list->tail=n;
  }
  else{
    if(list->tail == list->current){
      list->tail=n;
      list->current->next=n;
      n->prev=list->current;
    }
    else{
      list->current->next->prev=n;
      n->prev=list->current;
      n->next=list->current->next;
      list->current->next=n;
    }
  }
}

void *popFront(List *list) 
{
 list->current = list->head;
    return popCurrent(list);
}

void *popBack(List *list) 
{
  list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List *list) 
{
  Node* eliminado=list->current;
  void* data=list->current->data;
  
  if(list->head != list->current && list->tail != list->current )
  {
    list->current->prev->next=list->current->next;
    list->current->next->prev=list->current->prev;
    list->current=list->current->next; 
  }
  else{
    if(list->current==list->head)
    {
      list->current->next->prev = NULL;
      list->current = list->current->next;
      list->head = list->current;         
    }
    else
    {
      list->current->prev->next = NULL;
      list->current = list->current->prev;
      list->tail = list->current;    
    } 
  }
  free(eliminado);
  return data; 
}

void cleanList(List *list) 
{
  while (list->head != NULL) {
    popFront(list);
  }
}