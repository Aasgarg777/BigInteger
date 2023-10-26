#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node *next;
} Node;

struct BigInteger
{
  Node *head;
  long int Len;
  char sign;
};

Node *insert_at_begin(Node *Head_node, int value);
void insert_at_end(struct BigInteger *number, int elem);
long int Len(Node *Head_node);
void print_Linked_list(Node *connect);
void display(struct BigInteger b);
struct BigInteger initialize(char *p);
Node *Reverse_LL(Node *Head_node);
int Compare_nodes(struct BigInteger n1, struct BigInteger n2);
struct BigInteger add(struct BigInteger n1, struct BigInteger n2);
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2);
struct BigInteger mul(struct BigInteger n1, struct BigInteger n2);
struct BigInteger div1(struct BigInteger n1, struct BigInteger n2);
struct BigInteger mod(struct BigInteger n1, struct BigInteger n2);
void Free_LL(struct BigInteger *number);

#endif