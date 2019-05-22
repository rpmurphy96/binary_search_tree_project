/*

  The required function prototypes and several variable names for this project were provided by Donald Yeung.

*/

/*
   This program is used to test the functionality of the abstract data type binary search tree included in 'bst.c'.
   Code adapted from an example developed by Donald Yeung (adapted from an example originally
   developed by Gang Qu).
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"

#define WORD_SIZE 40

#define TRUE 1


void lower_case_word(char *);
void dump_dictionary(Pbst_t bst);
int compare(void *key1, void *key2);

typedef struct data_{
    char word[WORD_SIZE];
    int freq;
} data_t, *Pdata_t;


int main(void)
{
    Pbst_t my_bst;
    Pdata_t my_data;
    my_bst = new_bst(&compare);

    char c, word[WORD_SIZE], *temp_word;
    int char_index = 0, num_words = 0, depth = 0, i;


    printf("Parsing input ...\n");
    // Read in characters until end is reached

    while ((c = getchar()) != EOF) {
        if ((c == ' ') || (c == ',') || (c == '.') || (c == '!') || (c == '"') ||
            (c == ':') || (c == '\n')) {
            // End of a word is reached
            if (char_index) {
                // Word is not empty
                word[char_index] = '\0';
                lower_case_word(word);
                if (!find_bst(my_bst, word, &depth)) { // If the word isn't in the tree yet, put it in there
                    my_data = (Pdata_t) malloc(sizeof(data_t));
                    temp_word = (char *) malloc(sizeof(char)*(char_index+1));
                    strcpy(temp_word, word);
                    strcpy(my_data->word, word);
                    my_data->freq = 1;
                    insert_bst(my_bst, temp_word, my_data);
                    num_words++;
                }
                else { //If the word is already in the tree, increment it's frequency counter
                    my_data = (Pdata_t) find_bst(my_bst, word, &depth); //Do i need to cast this to a (Pdata_t)?
                    my_data->freq++;
                }
                char_index = 0;
            }
        } else {
            // Continue assembling a word
            word[char_index++] = c;
        }
    }

    dump_dictionary(my_bst);

   //free_bst(my_bst); This function could be utilized if the BST was used in a larger scale operation that would need
   //to dynamically allocate heap space (to avoid memory leaks)
}

void lower_case_word(char *w)
{
    int i = 0;

    while (w[i] != '\0') {
        w[i] = tolower(w[i]);
        i++;
    }
}

void dump_dictionary(Pbst_t bst){
    int i, num_items, height;
    stat_bst(bst, &num_items, &height);
    printf("Number of unique words:  %d\nHeight:  %d\n", num_items, height);

    Pdata_t my_data;

    my_data = (Pdata_t) start_bst_walk(bst);
    printf("%s:  %d\n", my_data->word, my_data->freq);

    for (i = 1; i < num_items; i++){
        my_data = (Pdata_t) next_bst_walk(bst);
        printf("%s:  %d\n", my_data->word, my_data->freq);
    }
}

int compare(void *key1, void *key2){
    char *newkey1 = key1;
    char *newkey2 = key2;
    if (strcmp(newkey1, newkey2) < 0){
        return -1;
    } else if (strcmp(newkey1, newkey2) == 0){
        return 0;
    } else if (strcmp(newkey1, newkey2) > 0)
        return 1;

    return 1;
}


