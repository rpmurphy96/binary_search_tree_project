//
// Created by Ryan Murphy on 5/8/19.
//

/*

 The required function prototypes and several variable names for this project were provided by Donald Yeung.

*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Pbst_t new_bst(int (*cmp_func)(void *, void *)){
    Pbst_t my_bst = (Pbst_t) malloc(sizeof(bst_t));
    my_bst->root = NULL;
    my_bst->size = 0;
    my_bst->depth = 0;
    my_bst->cmp_func = cmp_func;
    my_bst->sort_order = 0;
    return my_bst;
}

void free_bst(Pbst_t bst) {
    int i = 0;

    //Free our sorted arrays (So our arrays are definitely up to date)
    if(bst->sorted_nodes)
        free(bst->sorted_nodes);
    if (bst->sorted_data)
        free(bst->sorted_data);

    //Malloc space for our sorted arrays
    bst->sorted_nodes = (Pnode*) malloc(sizeof(Pnode)*bst->size);
    bst->sorted_data = (void**) malloc(sizeof(void*)*bst->size);

    //Generate our sorted arrays again
    sort_nodes(bst, bst->root);

    //Now free all our keys and data
    while (i < bst->size) {
        free(bst->sorted_nodes[i]->key);
        free(bst->sorted_data[i]);
        free(bst->sorted_nodes[i]);
        i++;
    }

    //Free our sorted arrays (we must free everything on the heap we used in our bst)
    if(bst->sorted_nodes)
        free(bst->sorted_nodes);
    if (bst->sorted_data)
        free(bst->sorted_data);
}


void insert_bst(Pbst_t bst, void *key, void *data){
    int comp;
    int height = 1;
    Pnode cur_node;
    Pnode new_node = (Pnode) malloc(sizeof(node));

    //Put our data into our new node
    new_node->key = key;
    new_node->data = data;
    new_node->left = new_node->right = NULL;

    //Special case: If our bst is empty
    if (bst->root == NULL){
        bst->root = new_node;
        bst->size++;
        bst->depth = height;
        return;
    }

    //If our bst is not empty, start with our cur at the top of our tree (root node)
    cur_node = bst->root;

    //Traverse the tree to find the correct place the node belongs at
    while(1){
        height++;
        //run the compare function
        comp = (*(bst->cmp_func))(new_node->key, cur_node->key); //Q: IS THIS CORRECT?

        //If we already have it in the tree
        if (comp == 0){
            //note: we have to free our newly malloc'ed space since we already have it in the tree
            free(new_node);
            return;
        }

        //If the first key is less than second key
        if (comp == -1) {
            if (cur_node->left == NULL){ //means we're going to the left and there's no more tree there
                cur_node->left = new_node; //insert new node here
                bst->size++;
                if (height > bst->depth)
                    bst->depth = height;
                return;
            }
            else {
                cur_node = cur_node->left;
            }
        }





        //If the first key is greater than second key
        if (comp == 1) {
            if (cur_node->right == NULL){ //means we're going to the right and there's no more tree there
                cur_node->right = new_node; //insert new node here
                bst->size++;
                if (height > bst->depth)
                    bst->depth = height;
                return;
            }
            else {
                cur_node = cur_node->right;
            }
        }
    }
}

void *find_bst(Pbst_t bst, void *key, int *depth){
    int comp;

    Pnode cur_node;
    if (bst->root == NULL){
        return NULL;
    }
    cur_node = bst->root;

    int deep = 0;
    while(1){
        deep++;
        //run the compare function
        comp = (*(bst->cmp_func))(key, cur_node->key);
        if (comp == 0) { //meaning we found the node
            *depth = deep;
            return cur_node->data;
        }
        if (comp == -1){ //first key (entered key) is less than second key (cur_node key)
            if (cur_node->left == NULL)
                return NULL;
            cur_node = cur_node->left;
            deep++;
        }
        if (comp == 1){ //first key (entered key) is greater than second key (cur_node key)
            if (cur_node->right == NULL)
                return NULL;
            cur_node = cur_node->right;
            deep++;
        }
    }
}

void stat_bst(Pbst_t bst, int *num_items, int *height){
    *height = bst->depth;
    *num_items = bst->size;
}


void *start_bst_walk(Pbst_t bst){
    bst->sort_order = 0;
    //Malloc space for our sorted arrays
    bst->sorted_nodes = (Pnode*) malloc(sizeof(Pnode)*bst->size);
    bst->sorted_data = (void**) malloc(sizeof(void*)*bst->size);

    sort_nodes(bst, bst->root);
    bst->sort_order = 0;
    return bst->sorted_data[bst->sort_order++];
}

// Could make this function private if this ADT was implemented for use by another party
void sort_nodes(Pbst_t bst, Pnode cur){

    if (cur->left != NULL)
        sort_nodes(bst, cur->left);

    bst->sorted_data[bst->sort_order] = cur->data;
    bst->sorted_nodes[bst->sort_order++] = cur;

    if (cur->right)
        sort_nodes(bst, cur->right);
}

//Traverse our BST and return the data found in the next node in accordance with the user-defined compare function
void *next_bst_walk(Pbst_t bst){
    if (bst->sort_order >= bst->size){
        return NULL;
    }
    return bst->sorted_data[bst->sort_order++];
}


























