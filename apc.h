#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SUCCESS		1
#define FAILURE		0

#define SAME		0
#define OPERAND1	1
#define OPERAND2	2

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
}node;

void addition(node *tail1, node *tail2, node **headR, node **tailR);
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);
void division(node *head1,node *tail1, node *head2,node* tail2, node **headR, node **tailR);

int validate(char* s);
void create_list(char *opr, node **head, node **tail);

int insert_first(node **head, node **tail, int data);
void insert_last(node **head, node **tail, int data);
void print_list(node *head);

int compare_lists(node *head1, node *head2);
void remove_prezeros(node **head);



#endif
