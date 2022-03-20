#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
  Node* nodo = (Node*) malloc (sizeof(Node));
  nodo->data = data;
  nodo->next = NULL;
  nodo->prev = NULL;
  return nodo;
}

List * createList() {
  List* lista = (List*) malloc (sizeof(List));
  lista->head = NULL;
  lista->current = NULL;
  lista->tail = NULL;
  return lista;
}

void * firstList(List * list) {
  list->current = list->head;
  if (list->current != NULL){
    return list->current->data;
  }
  return NULL;
}

void * nextList(List * list) {
  if(list->current == NULL){return NULL;}
  if(list->current->next != NULL){
    list->current = list->current->next;
    if(list->current != NULL){
      return list->current->data;
    }
  }
  return NULL;
}

void * lastList(List * list) {
  list->current = list->tail;
  if (list->current != NULL){
    return list->current->data;
  }
  return NULL;
}

void * prevList(List * list) {
  if(list->current == NULL){return NULL;}
  list->current = list->current->prev;
  if (list->current != NULL){
    return list->current->data;
  }
  return NULL;
}

void pushFront(List * list, void * data) {
  Node *nodo = createNode(data);
  if(list->head == NULL){
    list->head = nodo;
    list->current = nodo;
    list->tail = nodo;
  }
  else{
    nodo->next = list->head;
    nodo->prev = NULL;
    list->head->prev = nodo;
    list->head = nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if(list->current->next == NULL){
    Node *nodo = createNode(data);
    nodo->prev = list->current;
    nodo->next = NULL;
    list->current->next = nodo;
    list->tail = nodo;
  }
  else{
    Node *nodo = createNode(data);
    nodo->prev = list->current;
    nodo->next = list->current->next;
    list->current->next = nodo;
  }

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list->current == NULL){return NULL;}

  Node * nodo = createNode(list->current->data);
  nodo->next = list->current->next;
  nodo->prev = list->current->prev;

  if((list->current->next == NULL) && (list->current->prev != NULL)){
    list->current = list->current->prev;
    list->current->next = NULL;
    free(list->tail);
    list->tail = list->current;
  }

  if((list->current->next != NULL) && (list->current->prev == NULL)){
    list->current = list->head->next;
    list->current->prev = NULL;
    free(list->head);
    list->head = list->current;
  }
  
  if((list->current->next != NULL) && (list->current->prev != NULL)){
    free(list->current);
    list->current = nodo->prev;
    list->current->next = nodo->next;
    list->current->next->prev = nodo->prev;
  }

  return nodo->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}