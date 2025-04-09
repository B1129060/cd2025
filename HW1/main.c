#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    char value[6];
    char token[20];
    int count;
} node;

node* cons(); //constructor
node* conN() { return NULL; };


int main()
{
    node** pos = (node**)malloc(sizeof(node*) * 128);

    for (int i = 0; i < 128; i++) {
        pos[i] = NULL;
    }
    //record the data of all the token
    pos['i'] = cons();
    strcpy(pos['i']->value, "if");
    strcpy(pos['i']->token, "IF_TOKEN");
    pos['i']->count = 2;

    pos['i']->next = cons();
    strcpy(pos['i']->next->value, "int");
    strcpy(pos['i']->next->token, "TYPE_TOKEN");
    pos['i']->next->count = 1;

    pos['m'] = cons();
    strcpy(pos['m']->value, "main");
    strcpy(pos['m']->token, "MAIN_TOKEN");
    pos['m']->count = 1;

    pos['e'] = cons();
    strcpy(pos['e']->value, "else");
    strcpy(pos['e']->token, "ELSE_TOKEN");
    pos['e']->count = 1;

    pos['w'] = cons();
    strcpy(pos['w']->value, "while");
    strcpy(pos['w']->token, "WHILE_TOKEN");
    pos['m']->count = 1;

    pos['('] = cons();
    strcpy(pos['(']->token, "LEFTPAREN_TOKEN");
    pos['(']->count = 0;

    pos[')'] = cons();
    strcpy(pos[')']->token, "RIGHTPAREN_TOKEN");
    pos[')']->count = 0;

    pos['{'] = cons();
    strcpy(pos['{']->token, "LEFTBRACE_TOKEN");
    pos['{']->count = 0;

    pos['}'] = cons();
    strcpy(pos['}']->token, "RIGHTBRACE_TOKEN");
    pos['}']->count = 0;

    pos[';'] = cons();
    strcpy(pos[';']->token, "SEMICOLON_TOKEN");
    pos[';']->count = 0;

    pos['+'] = cons();
    strcpy(pos['+']->token, "PLUS_TOKEN");
    pos['+']->count = 0;

    pos['-'] = cons();
    strcpy(pos['-']->token, "MINUS_TOKEN");
    pos['-']->count = 0;

    pos['='] = cons();
    strcpy(pos['=']->value, "==");
    strcpy(pos['=']->token, "EQUAL_TOKEN");
    pos['=']->count = 2;

    pos['=']->next = cons();
    strcpy(pos['=']->next->token, "ASSIGN_TOKEN");
    pos['=']->next->count = 0;

    pos['>'] = cons();
    strcpy(pos['>']->value, ">=");
    strcpy(pos['>']->token, "GREATEREQUAL_TOKEN");
    pos['>']->count = 2;

    pos['>']->next = cons();
    strcpy(pos['>']->next->token, "GREATER_TOKEN");
    pos['>']->next->count = 0;

    pos['<'] = cons();
    strcpy(pos['<']->value, "<=");
    strcpy(pos['<']->token, "LESSEQUAL_TOKEN");
    pos['<']->count = 2;

    pos['<']->next = cons();
    strcpy(pos['<']->next->token, "LESS_TOKEN");
    pos['<']->next->count = 0;

    int in;
    int next;
    char tmp[20];
    int n = 0;
    node* cur = NULL;
    FILE* fp;
    fp = fopen("test.txt", "r");

    while (1) {
        if ((in = fgetc(fp)) == EOF) {
            break;
        }
        memset(tmp, 0, 20);
        n = 0;
        if (in == ' ' || in == '\n' || in == '\r' || in == '\t' || in == '\0') {
            continue;
        }
        else if (in == '_' || (in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z')) {
            tmp[n++] = in;
            next = fgetc(fp);
            if (pos[in]) {
                while (next == '_' || (next >= 'a' && in <= 'z') || (next >= 'A' && in <= 'Z') || (next >= '0' && in <= '9')) {
                    tmp[n++] = next;
                    next = fgetc(fp);
                }
                cur = pos[in];
                while (cur != NULL) {
                    if (strcmp(tmp, cur->value) == 0) {
                        ungetc(next, fp);
                        printf("%s: %s\n", tmp, cur->token);
                        n = -1;
                        break;
                    }
                    cur = cur->next;
                }
                if (n != -1) {
                    ungetc(next, fp);
                    printf("%s: ID_TOKEN\n", tmp);
                }
            }
            else {
                in = fgetc(fp);
                while (in == '_' || (in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z') || (in >= '0' && in <= '9')) {
                    tmp[n++] = in;
                    in = fgetc(fp);
                }
                ungetc(in, fp);
                printf("%s: ID_TOKEN\n", tmp);
            }
            
        }
        else if (in >= '0' && in <= '9') {
            tmp[n++] = in;
            in = fgetc(fp);
            while (in >= '0' && in <= '9') {
                tmp[n++] = in;
                in = fgetc(fp);
            }
            ungetc(in, fp);
            printf("%s: LITERAL_TOKEN\n", tmp);
        }
        else if (pos[in]) {
            if (pos[in]->count != 0) {
                tmp[n++] = in;
                while (n < strlen(pos[in]->value)) {
                    next = fgetc(fp);
                    if (next == pos[in]->value[n]) {
                        tmp[n++] = next;
                        continue;
                    }
                    else {
                        ungetc(next, fp);
                        n--;
                        while (n > 0) {
                            ungetc(tmp[n], fp);
                        }
                        n = -1;
                        break;
                    }
                }
                if (n != -1) {
                    printf("%s: %s\n", tmp, pos[in]->token);
                }
                else {
                    printf("%c: %s\n", tmp[0], pos[in]->next->token);
                }
            }
            else {
                printf("%c: %s\n", in, pos[in]->token);
            }
        }
        else {
            printf("undefined character->%c(%d)\n", in, in);
        }
    }

    fclose(fp);

    for (int i = 0; i < 128; i++) {
        if (pos[i] != NULL) {
            if (pos[i]->next != NULL) {
                free(pos[i]->next);
            }
            free(pos[i]);
        }
    }
    if (pos != NULL) {
        free(pos);
    }
    return 0;
}

node* cons() {
    node* new = (node*)malloc(sizeof(node));
    if (new == NULL) {
        printf("error\n");
        return NULL;
    }
    memset(new->value, 0, 6);
    memset(new->token, 0, 20);
    new->count = 0;
    new->next = NULL;
    return new;
}
