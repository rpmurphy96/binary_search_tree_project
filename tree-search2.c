 /*

  The required function prototypes and several variable names for this project were provided by Donald Yeung.

 */

 /*

   This program is used to test the functionality of the abstract data type binary search tree included in 'bst.c'.
   Code adapted from an example developed by Donald Yeung.

 */

 /*

  This program creates a binary search tree (BST) with a large number
  of random values.  Then, it prompts the user for values, and looks
  them up in the BST.  It includes the print_data() function which
  performs a recursive traversal of the BST to print its values.

 */

#include <stdio.h>
#include <stdlib.h>

#define NUM_VALUES 10000
#define TRUE 1
#define FALSE 0


void create_data(Pbst_t bst);
int compare(void *key1, void *key2);


int main()
{
    int value, i;
    int num_of_tries = 0;

    Pbst_t my_bst;

    my_bst = new_bst(&compare);



    create_data(my_bst);

    // Continually prompt the user for a value, and search for it in the list
    while (TRUE) {
        printf("Enter a number to find:  ");
        scanf("%d", &value);
        if (find_bst(my_bst, &value, &num_of_tries) != NULL){
            printf("Found the number %d after %d tries\n", value, num_of_tries);
        }
        else printf("Could not find the number %d in the list\n", value);

    }

    // this program never returns
}

// Insert randomly generated numbers into the linked list
void create_data(Pbst_t bst) //Q: Should the parameter be Pbst_t bst or Pbst_t *bst?
{
    int i;
    int *key, *data;
    int num_items, height;

    for (i = 0; i < NUM_VALUES; i++) {
        key = (int *)malloc(sizeof(int));
        data = (int *)malloc(sizeof(int));
        *key = *data = rand() % NUM_VALUES;
        insert_bst(bst, key, data);
    }

    stat_bst(bst, &num_items, &height);
    printf("Number of Nodes in the BST: %d, Height of the BST: %d\n", num_items, height);

}

int compare(void *key1, void *key2){
    int *newkey1 = key1;
    int *newkey2 = key2;
    if (*newkey1 < *newkey2){
        return -1;
    } else if (*newkey1 == *newkey2){
        return 0;
    } else if (*newkey1 > *newkey2)
        return 1;

    return 1;
}




