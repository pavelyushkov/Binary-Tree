#ifndef MODEL_H
#define MODEL_H

void treeTolist(Tree* tree, Node* node);
void freeNode(Node* tmp);
void freeTree(Node* node);
unsigned int get_integer();
unsigned int get_key();
Item* get_item();
Node* find_max(Node* node);
Node* find_min(Node* parent);
void stitch(Tree* tree);
Node* find_by_key(Node* node, unsigned int key);
Tree* delete_element(Tree* tree, Node* tmp);
void delete_by_index(Node* tmp, unsigned int index);
void add_element(Tree* tree, Item* item);
Item* create_new_item();
void write_to_file(Node* node, FILE* file);
void load_from_file(Tree* tree, FILE* file);
Tree* create_tree();
int check_duplicate(Node* tmp);

#endif //MODEL_H
