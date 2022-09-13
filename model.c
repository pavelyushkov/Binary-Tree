#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readline.h"
#include "struct.h"

void treeTolist(Tree* tree, Node* node){
  if(tree->parent == node)
    tree->parent = NULL;
  if(node->left != NULL)
    treeTolist(tree, node->left);
  if(node->right != NULL)
    treeTolist(tree, node->right);
  if(tree->parent == NULL)
    tree->parent = node;
  else{
    Node* head = tree->parent;
    while(head->right != NULL)
      head = head->right;
    head->right = node;
    node->left = head;
    node->right = NULL;
  }
}

void freeNode(Node* tmp){
  Item* item = tmp->item;
  Item* pass;
  while(item != NULL){
    pass = item;
    item = item->next;
    free(pass);
  }
  free(tmp);
  tmp = NULL;
}

void freeTree(Node* node){
  if(node == NULL)
    return;
  freeTree(node->left);
  freeTree(node->right);
  freeNode(node);
}

unsigned int get_integer(){
  unsigned int res = 0;
  int q, i, flag = 1;
  char* input = NULL;
  while(flag == 1){
   if(input != NULL)
      free(input);
    input = readline("");
    if(input == NULL)
      return 0;
    q = strlen(input);
    for(i = 0; i < q; i++){
      if(!isdigit(input[i])){
        printf("\nWrong input. Try again:   ");
        flag = 1;
        break;
      }
      if(i == (q - 1))
        flag = 0;
    }
    res = atoi(input);
    if(res < 0){
      printf("\nWrong input. Try again:   ");
      flag = 1;
    }
  }
  free(input);
  return res;
}

unsigned int get_key(){
  unsigned int key;
  printf("\nEnter key:  ");
  key = get_integer();
  return key;
}

Item* get_item(){
  Item* item = (Item*) malloc(sizeof(Item));
  printf("\nEnter key:  ");
  item->key = get_integer();
  printf("\nEnter data:  ");
  item->data = get_integer();
  item->next = NULL;
  return item;
}

Node* find_max(Node* node){
  if(node != NULL)
    while(node->right != NULL){
      node = node->right;
    }
  return node;
}

Node* find_min(Node* parent){
  Node* elem = parent;
  while(elem->left != NULL)
    elem = elem->left;
  return elem;
}

Node* find_next(Tree* tree, Node* node){
  if(find_max(tree->parent) == node){
    node->next = NULL;
    return NULL;
  }
  if(node->right != NULL){
    node->next = find_min(node->right);
    return node->next;
  }
  else{
    Node* elem = node;
    while(elem->root->left != elem)
      elem = elem->root;
    node->next = elem->root;
    return node->next;
  }
}

void stitch(Tree* tree){
  if(tree->parent == NULL)
    return;
  Node* node = find_min(tree->parent);
  while(1){
    node->next = find_next(tree, node);
    if(node->next == NULL)
      return;
    node = node->next;
  }
}

Node* find_by_key(Node* node, unsigned int key){
  Node* res;
  if(node == NULL)
    return NULL;
  else{
    if(key == node->item->key)
      return node;
    else if(key < node->item->key)
      res = find_by_key(node->left, key);
    else if(key > node->item->key)
      res = find_by_key(node->right, key);
    return res;
  }
}

void delete_element(Tree* tree, Node* tmp){
  if(tmp == NULL)
    return;
  if(tmp == tree->parent){
    if(tmp->left == NULL && tmp->right == NULL){
      freeNode(tmp);
      tree->parent = NULL;
      return;
    }
    if(tmp->right != NULL){
      Node* elem = tmp->right;
      while(elem->left != NULL){
        elem = elem->left;
      }
      elem->left = tmp->left;
      if(tmp->left != NULL)
        tmp->left->root = elem;
      tree->parent = tmp->right;
      tree->parent->root = NULL;
      freeNode(tmp);
      return;
    }
    if(tmp->left != NULL){
      tree->parent = tmp->left;
      tree->parent->root = NULL;
      freeNode(tmp);
      return;
    }
  }
  else{
    Node* parent = tmp->root;
    if(tmp->root->right == tmp){
      if(tmp->right != NULL){
        parent->right = tmp->right;
        tmp->right->root = parent;
        Node* elem = tmp->right;
        while(elem->left != NULL){
          elem = elem->left;
        }
        elem->left = tmp->left;
        if(tmp->left != NULL)
          tmp->left->root = elem;
        freeNode(tmp);
        return;
      }
      if(tmp->left != NULL){
        parent->right = tmp->left;
        tmp->left->root = parent;
        freeNode(tmp);
        return;
      }
    }
    else if(tmp->root->left == tmp){
      if(tmp->right != NULL){
        parent->left = tmp->right;
        tmp->right->root = parent;
        Node* elem = tmp->right;
        while(elem->left != NULL){
          elem = elem->left;
        }
        elem->left = tmp->left;
        if(tmp->left != NULL)
          tmp->left->root = elem;
        freeNode(tmp);
        return;
      }
      if(tmp->left != NULL){
        parent->left = tmp->left;
        tmp->left->root = parent;
        freeNode(tmp);
        return;
      }
    }
    if(tmp->left == NULL && tmp->right == NULL){
      if(tmp->root->left == tmp)
        tmp->root->left = NULL;
      else
        tmp->root->right = NULL;
      freeNode(tmp);
      return;
    }
  }
}

void delete_by_index(Node* tmp, unsigned int index){
  Item* item = tmp->item;
  if(index == 0){
    tmp->item = item->next;
    free(item);
  }
  else{
    for(unsigned int i = 0; i < (index - 1); ++i){
      item = item->next;
    }
    Item* pass = item->next;
    item->next = item->next->next;
  }
}

void add_element(Tree* tree, Item* item){
  if(tree->parent == NULL){
    tree->parent = (Node*) malloc(sizeof(Node));
    tree->parent->item = item;
    tree->parent->left = NULL;
    tree->parent->right = NULL;
    tree->parent->root = NULL;
  }
  else{
    Node* elem = tree->parent;
    while(1){
      if(item->key < elem->item->key){
        if(elem->left != NULL)
          elem = elem->left;
        else{
          elem->left = (Node*) malloc(sizeof(Node));
          elem->left->item = item;
          elem->left->root = elem;
          elem = elem->left;
          elem->left = NULL;
          elem->right = NULL;
          break;
        }
      }
      else if(item->key > elem->item->key){
        if(elem->right != NULL)
          elem = elem->right;
        else{
          elem->right = (Node*) malloc(sizeof(Node));
          elem->right->item = item;
          elem->right->root = elem;
          elem = elem->right;
          elem->left = NULL;
          elem->right = NULL;
          break;
        }
      }
      else{
        Item* ptr = elem->item;
        while(ptr->next != NULL){
          ptr = ptr->next;
        }
        ptr->next = item;
        break;
      }
    }
  }
}

Item* create_new_item(){
  Item* item;
  item = (Item*) calloc(1, sizeof(Item));
  item->next = NULL;
  return item;
}

void write_node(Node* node, FILE* file){
  Item* item = node->item;
  while(item != NULL){
    fwrite(&item->key, 4, 1, file);
    fwrite(&item->data, 4, 1, file);
    item = item->next;
  }
}

void write_to_file(Node* node, FILE* file){
  if(node == NULL)
    return;
  else{
    write_node(node, file);
    write_to_file(node->left, file);
    write_to_file(node->right, file);
  }
}

void load_from_file(Tree* tree, FILE* file){
  int c = 0;
  unsigned int n = 0;
  Item* item;
  fseek(file, 0, SEEK_END);
  int fsize = ftell(file);
  fseek(file, 0, SEEK_SET);
  while(ftell(file) <= fsize - 1){
    item = create_new_item();
    fread(&n, 4, 1, file);
    item->key = n;
    fread(&n, 4, 1, file);
    item->data = n;
    add_element(tree, item);
  }
  return;
}

Tree* create_tree(){
  Tree* tree = (Tree*) malloc(sizeof(Tree));
  tree->parent = NULL;
  return tree;
}

int check_duplicate(Node* tmp){
  int res = 0;
  Item* item = tmp->item;
  while(item != NULL){
    item = item->next;
    ++res;
  }
  return res;
}
