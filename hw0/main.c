#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    struct node* next;
    char c;
    int count;
} node;

node* cons(char); //constructor

int main()
{
    node** pos = (node**)malloc(sizeof(node*)*128);
    for(int i = 0; i < 128; i++){
        pos[i] = NULL;
    }
    node* cur = NULL;
    node* root = cons('\0');
    cur = root;
    
    char in;
    FILE* fp;
    fp = fopen("main.c", "r");
    
    while(1){
        if((in = fgetc(fp)) == EOF){
            break;
        }
        if(pos[in] == NULL){
            cur->next = cons(in);
            pos[in] = cur->next;
            cur = cur->next;
        }else{
            pos[in]->count++;
        }
    }
    
    fclose(fp);
    
    cur = root->next;//output
    while(cur != NULL){
        if(cur->c == '\n'){
            printf("\'\\n\' : %d\n", cur->count);
        }else if(cur->c == ' '){
            printf("\' \' : %d\n", cur->count);
        }else{
            printf("%c : %d\n", cur->c, cur->count);
        }
        cur = cur->next;
    }
    
    printf("enter char: ");//bonus(find node pointers from array "pos" directly, Time complexity O(1))
    in = getchar();
    if(pos[in] == NULL){
        printf("\nchar not found.\n");
    }else{
        if(pos[in]->c == '\n'){
            printf("\n\'\\n\' : %d\n", pos[in]->count);
        }else if(pos[in]->c == ' '){
            printf("\n\' \' : %d\n", pos[in]->count);
        }else{
            printf("\n%c : %d\n", pos[in]->c, pos[in]->count);
        }
    }
    
    cur = root;//free
    root = root->next;
    while(root != NULL){
        free(cur);
        cur = root;
        root = root->next;
    }
    free(cur);
    free(pos);
    return 0;
}

node* cons(char input){
    node* new = (node*)malloc(sizeof(node));
    new->c = input;
    new->count = 1;
    new->next = NULL;
    return new;
}
