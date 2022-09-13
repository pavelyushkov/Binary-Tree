#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readline.h"
#include "struct.h"

void left_rotate(Node* parent, Node* node){
  Node* p = parent->parent;
  if(p->key < parent->key)
    p->right = node;
  else
    p->left = node;
  node->parent = p;
  Node* elem = node;
  while(elem->left != NULL)
    elem = elem->left;
  elem->left = parent;
  parent->parent = elem;
  return;
}

void right_rotate(Node* parent, Node* node){
  Node* p = parent->parent;
  if(p->key < parent->key)
    p->right = node;
  else
    p->left = node;
  node->parent = p;
  Node* elem = node;
  while(elem->right != NULL)
    elem = elem->right;
  elem->right = parent;
  parent->parent = elem;
  return;
}
