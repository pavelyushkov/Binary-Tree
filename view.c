#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void menu(){
  printf("\nEnter 1 to add element");
  printf("\nEnter 2 to delete element");
  printf("\nEnter 3 to output tree");
  printf("\nEnter 4 to find element");
  printf("\nEnter 5 to find element with the biggest key");
  printf("\nEnter 6 to format output");
  printf("\nEnter 7 to read tree from file");
  printf("\nEnter 8 to write tree into file");
  printf("\nEnter 9 to change in list");
  printf("\nEnter 10 to out list");
  printf("\nEnter 0 to end\n");
}

void out_node(Node* node){
  Item* item = node->item;
  while(item != NULL){
    printf("  %d", item->data);
    item = item->next;
  }
}

void out_all(Node* node){
  if(node == NULL)
    return;
  out_all(node->left);
  out_node(node);
  out_all(node->right);
}

void out_from_key(Node* head, unsigned int key){
  Node* elem = head;
  while(elem != NULL){
    if(elem->item->key > key)
      out_node(elem);
    elem = elem->next;
  }
}

void format_output(Node* node, int k, int root){
  if(node == NULL)
    return;
 else{
    format_output(node->left, k + 1, 1);
    for(int i = 0; i < k; ++i){
      printf("      ");
    }
    printf("%d\n\n", node->item->key);
    format_output(node->right, k + 1, -1);
  }
}

void printList(Tree* tree){
  Node* elem = tree->parent;
  while(elem != NULL){
      printf("\t%d(%d)", elem->item->key, elem->item->data);
      elem = elem->right;
  }
  return;
}
