#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct ter_char_node ter_char_node_t;

struct ter_char_node{
    char key;
    int weight;
    int end_of_flag;
    ter_char_node_t *left, *equal, *right;
};

int read_and_insert_nodes(const char file_name[]);
ter_char_node_t* insert(ter_char_node_t* pNode, char* word, int weight);
void find_and_traverse(ter_char_node_t* pNode, char* prefix);
void traverse(ter_char_node_t* pNode, char* buffer, int depth);
void print_hello();

ter_char_node_t* insert(ter_char_node_t* pNode, char* word, int weight){
/* insert functions to insert a node into a trenary search
   tree.'word' is the comparitor with ASCII that is case
   sensitive. Insertion sequence depends on the int 'weight'of
   the given node in decreasing order, with the largest weight
   inserted first. returns the node* root of the trenary tree.
*/
    ter_char_node_t* root_node = pNode;

    assert(isalpha(*word));

    if (pNode == NULL){ //assign the node if it is empty
        ter_char_node_t* new_node =
        (ter_char_node_t*)malloc(sizeof(ter_char_node_t));
        new_node->key = *word;
        new_node->end_of_flag = FALSE;
        new_node->left = new_node->equal = new_node->right = NULL;
    }
    if(*word < pNode->key){// if the word is 'smaller'
        pNode->left = insert(pNode->left, word, weight);
    }
    else if(*word == pNode->key){ // if word is 'equal'
        if(*(word+1) == '\0'){ //if the word has ended, put flag and weight
            pNode->end_of_flag = TRUE;
            pNode->weight = weight;
        }
        else{ //if there are more keys, insert down the 'equal' branch
            pNode->equal = insert(pNode->equal, word+1, weight);
        }
    }
    else{// if word is 'bigger'
        pNode->right = insert(pNode->right, word, weight);
    }
    return root_node;
}

void find_and_traverse(ter_char_node_t* pNode, char* prefix){
/* find node in the tree that represents the prefix, if prefix is found
   the pNode will point there if we reached the '\0' symbol, if the prefix
   does not exist, then pNode should be null.
*/

    char buffer[250];

    while(*prefix != '\0' && pNode != NULL){

    // traverse tree to find first prefix, then traverse again to look for
    // rest of the keys until it reaches end of search word.

        if (*prefix < pNode->key){
            pNode = pNode->left;
            continue;
        }
        if (*prefix > pNode->key){
            pNode = pNode->right;
            continue;
        }
        if (*prefix == pNode->key){
            pNode = pNode->equal;
            prefix++;
            continue;
        }
    }
    // pNode now points at the end of the search word, now search for candidate
    // autocomplete keys

    if(pNode){
    //  Include the prefix itself as a candidate if the prefix is a key.
        if(pNode->end_of_flag == TRUE){
            buffer[strlen(prefix)+1] = '\0';
            printf("%s\n", buffer);
        }
        traverse(pNode, buffer, strlen(prefix));
    }
}

void traverse(ter_char_node_t* pNode, char* buffer, int depth){

    if(!pNode){
        return;
    }
    traverse(pNode->left, buffer, depth);

    buffer[depth] = pNode->key;

    if(pNode->end_of_flag == TRUE){
        buffer[depth+1] = '/0';
        printf("%s\n", buffer);
    }

    traverse(pNode->equal, buffer, depth+1);
    traverse(pNode->right, buffer, depth+1);
}

int read_and_insert_nodes(const char file_name[]){
    FILE* ptr_file;
    char string_repo[250];
    char* tok_ptr;
    int weight;

    ptr_file = fopen(file_name, "r");

    if(!ptr_file){
        return 0;
    }

    while(fgets(string_repo, 250, ptr_file) != NULL){
        tok_ptr = strtok(string_repo, ";");
        weight = atoi(tok_ptr);
        tok_ptr = strtok(NULL, "\n");
    }

    fclose(ptr_file);
    return 0;
}

void print_hello_world(){
    printf("Hello World!\n");
}
