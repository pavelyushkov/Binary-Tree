#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "readline.h"
#include "struct.h"
#include "view.h"
#include "model.h"

int main(){
  unsigned int check = 10;
  Tree* tree = create_tree();
  while(check != 0){
    menu();
    printf("\nYour input: ");
    check = get_integer();
    if(check == 1){
      Item* item = get_item();
      add_element(tree, item);
      stitch(tree);
      printf("\nElement added\n");
    }
    else if(check == 2){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        unsigned int key = get_key();
        Node* tmp = find_by_key(tree->parent, key);
        if(tmp == NULL)
            printf("\nNo element with this key\n");
        else{
          unsigned int index = 0;
          int a = check_duplicate(tmp);
          if(a != 1){
            printf("\nEnter index of element to delete:  ");
            while(1){
              index = get_integer();
              if(index >= a)
                printf("\nWrong input. Try again:   ");
              else
                break;
            }
            delete_by_index(tmp, index);
          }
          else{
            delete_element(tree, tmp);
            stitch(tree);
          }
          printf("\nElement deleted\n");
        }
      }
    }
    else if(check == 3){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        printf("\nEnter 1 to special output and 0 to output all tree:  ");
        unsigned int k;
        while(1){
          k = get_integer();
          if(k == 0 || k == 1)
            break;
          else
            printf("\nWrong input. Try again:   ");
        }
        if(k == 1){
          unsigned int key = get_key();
          printf("\n");
          Node* head = find_min(tree->parent);
          out_from_key(head, key);
          printf("\n");
        }
        else{
          printf("\n");
          out_all(tree->parent);
          printf("\n");
        }
      }
    }
    else if(check == 4){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        unsigned int key = get_key();
        Node* elem =  find_by_key(tree->parent, key);
        if(elem == NULL)
          printf("\nNo element with this key\n");
        else{
          printf("\nElement with this key:  ");
          out_node(elem);
          printf("\n");
        }
      }
    }
    else if(check == 5){
      Node* elem = find_max(tree->parent);
      if(elem == NULL)
        printf("\nTree is empty\n");
      else{
        printf("\nThe biggest element is:  ");
        out_node(elem);
        printf("\n");
      }
    }
    else if(check == 6){
      printf("\n\n\n\n\n");
      format_output(tree->parent, 0);
      printf("\n\n\n");
    }
    else if(check == 7){
      char* name = readline("\nEnter name of file:  ");
      FILE* file = fopen(name, "rb");
      if(file == NULL)
        printf("\nFile open error\n");
      else{
        freeTree(tree->parent);
        free(tree);
        tree = create_tree();
        load_from_file(tree, file);
        fclose(file);
      }
      free(name);
    }
    else if(check == 8){
      char* name = readline("\nEnter name of file:  ");
      FILE* file = fopen(name, "w+b");
      fseek(file, 0, SEEK_SET);
      write_to_file(tree->parent, file);
      fclose(file);
      free(name);
      printf("\nTree recorded\n");
    }
    else if(check == 9){
      treeTolist(tree, tree->parent);
    }
    else if(check == 10)
      printList(tree);
  }
  freeTree(tree->parent);
  free(tree);
  printf("\nFinished!\n");
  return 0;
}
