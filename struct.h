#ifndef STRUCT_H
#define STRUCT_H

typedef struct Item {
  unsigned int data;
  unsigned int key;
  struct Item* next;
} Item;

typedef struct Node {
  Item* item;
  struct Node* next;
  struct Node* right;
  struct Node* left;
  struct Node* root;
} Node;

typedef struct Tree {
  Node* parent;
} Tree;

#endif // STRUCT_H
