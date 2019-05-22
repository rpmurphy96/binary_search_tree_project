//
// Created by Ryan Murphy on 5/8/19.
//

/*

 The required function prototypes and several variable names for this project were provided by Donald Yeung.

*/

#ifndef BST_C_BST_H
#define BST_C_BST_H

#endif //BST_C_BST_H

typedef struct node {
    void *data;
    void *key;
    struct node *left;
    struct node *right;
} node, *Pnode;

typedef struct bst_ {

    Pnode root;
    int size;
    int depth;
    //This compare function is defined by the user within the program that will utilize our ADT (bst.c)
    //The function should return a negative int if key1<key2, 0 is key1=key2, and positive int if key1>key2
    int (*cmp_func)(void *, void *);
    void **sorted_data;
    Pnode *sorted_nodes;
    int sort_order;
} bst_t, *Pbst_t;


Pbst_t new_bst(int (*cmp_func)(void *, void *));
void free_bst(Pbst_t bst);
void insert_bst(Pbst_t bst, void *key, void *data);
void *find_bst(Pbst_t bst, void *key, int *depth);
void stat_bst(Pbst_t bst, int *num_items, int *height);
void *start_bst_walk(Pbst_t bst);
void *next_bst_walk(Pbst_t bst);
void sort_nodes(Pbst_t bst, Pnode cur);


