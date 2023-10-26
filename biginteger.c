#include "BigInteger.h"

#include <stdio.h>
#include <stdlib.h>

Node *insert_at_begin(Node *head, int value)
{
  Node *ptr = (Node *)malloc(sizeof(Node));
  if (!ptr)
  {
    printf("memory allocation failed!");
    exit(1);
  }
  ptr->data = value;
  ptr->next = head;
  return ptr;
}

void insert_at_begin_at_end(struct BigInteger *num, int element)
{
  Node *ptr = (Node *)malloc(sizeof(Node));
  if (ptr == NULL)
  {
    printf("memory allocation failed\n");
    return;
  }
  ptr->data = element;
  ptr->next = NULL;
  num->Len += 1;
  if (num->head == NULL)
  {
    num->head = ptr;
    return;
  }
  Node *itreation = num->head;
  while (itreation->next != NULL)
  {
    itreation = itreation->next;
  }
  itreation->next = ptr;
}

long int Len(Node *head)
{
  long int count = 0;
  while (head)
  {
    head = head->next;
    count++;
  }
  return count;
}

void displayLL(Node *connect)
{
  if (!connect)
    return;
  displayLL(connect->next);
  printf("%d", connect->data);
}

void display(struct BigInteger b)
{
  if (b.head == NULL)
  {
    printf("0");
    return;
  }
  if (b.sign == '-')
    printf("-");
  displayLL(b.head);
}

struct BigInteger initialize(char *s)
{
  struct BigInteger b;
  b.head = NULL;
  if (s[0] == '-')
    b.sign = '-';
  else
    b.sign = '+';
  int i;
  if (b.sign == '-')
    i = 1;
  else
    i = 0;
  for (i; s[i] != '\0'; i++)
  {
    b.head = insert_at_begin(b.head, s[i] - '0');
  }
  b.Len = Len(b.head);
  return b;
}

Node *Reverse_LL(Node *head)
{
  Node *prev = NULL, *Front = NULL, *current = head;
  while (current != NULL)
  {
    Front = current->next;
    current->next = prev;
    prev = current;
    current = Front;
  }
  return prev;
}

int Compare_nodes(struct BigInteger Number_1, struct BigInteger Number_2)
{
  if (Number_2.Len > Number_1.Len)
  {
    return -1;
  }
  else if (Number_2.Len == Number_1.Len)
  {
    int r_value = 0;
    Number_1.head = Reverse_LL(Number_1.head);
    Number_2.head = Reverse_LL(Number_2.head);
    Node *Head_1 = Number_1.head, *Head_2 = Number_2.head;
    while (Head_1 != NULL && Head_2 != NULL)
    {
      if (Head_2->data > Head_1->data)
      {
        r_value = -1;
        break;
      }
      else if (Head_1->data > Head_2->data)
      {
        r_value = 1;
        break;
      }
      Head_1 = Head_1->next;
      Head_2 = Head_2->next;
    }
    Number_1.head = Reverse_LL(Number_1.head);
    Number_2.head = Reverse_LL(Number_2.head);
    return r_value;
  }
  return 1;
}

struct BigInteger add(struct BigInteger Number_1, struct BigInteger Number_2)
{
  struct BigInteger Number_3;
  Number_3.head = NULL;
  Number_3.sign = '+';
  Number_3.Len = 0;

  if (Number_1.sign == '-' && Number_2.sign == '-')
  {
    Number_3.sign = '-';
  }
  else if (Number_1.sign == '-')
  {
    Number_1.sign = '+';
    Number_3 = sub(Number_2, Number_1);
    Number_1.sign = '-';
    return Number_3;
  }
  else if (Number_2.sign == '-')
  {
    Number_2.sign = '+';
    Number_3 = sub(Number_1, Number_2);
    Number_2.sign = '-';
    return Number_3;
  }

  Node *m1 = Number_1.head, *m2 = Number_2.head;
  int ADD, CARRY = 0;

  while (m1 != NULL || m2 != NULL || CARRY != 0)
  {
    int p1 = (m1 != NULL) ? m1->data : 0;
    int p2 = (m2 != NULL) ? m2->data : 0;

    ADD = p1 + p2 + CARRY;
    CARRY = ADD / 10;
    insert_at_begin_at_end(&Number_3, ADD % 10);

    if (m1 != NULL)
      m1 = m1->next;
    if (m2 != NULL)
      m2 = m2->next;
  }
  Number_3.Len = Len(Number_3.head);
  return Number_3;
}

struct BigInteger sub(struct BigInteger Number_1, struct BigInteger Number_2)
{
  struct BigInteger Number_3;
  Number_3.head = NULL;
  Number_3.sign = '+';
  Number_3.Len = 0;

  if (Number_1.sign == '-' && Number_2.sign == '+')
  {
    Number_1.sign = '+';
    Number_3 = add(Number_1, Number_2);
    Number_1.sign = '-';
    Number_3.sign = '-';
    return Number_3;
  }
  else if (Number_1.sign == '+' && Number_2.sign == '-')
  {
    Number_2.sign = '+';
    Number_3 = add(Number_1, Number_2);
    Number_2.sign = '-';
    return Number_3;
  }
  else if (Number_1.sign == '-' && Number_2.sign == '-')
  {
    Number_2.sign = '+';
    Number_1.sign = '+';
    Number_3 = sub(Number_2, Number_1);
    Number_2.sign = '-';
    Number_1.sign = '-';
    return Number_3;
  }
  else if (Compare_nodes(Number_1, Number_2) == -1)
  {
    struct BigInteger ptr = Number_1;
    Number_1 = Number_2;
    Number_2 = ptr;
  }

  Node *m1 = Number_1.head, *m2 = Number_2.head;
  int DIFF, BORR = 0;

  while (m1 != NULL || m2 != NULL)
  {
    int p1 = (m1 != NULL) ? m1->data : 0;
    int p2 = (m2 != NULL) ? m2->data : 0;

    DIFF = p1 - p2 - BORR;

    if (DIFF < 0)
    {
      DIFF += 10;
      BORR = 1;
    }
    else
    {
      BORR = 0;
    }

    insert_at_begin_at_end(&Number_3, DIFF);

    if (m1 != NULL)
      m1 = m1->next;
    if (m2 != NULL)
      m2 = m2->next;
  }
  Number_3.head = Reverse_LL(Number_3.head);
  while (Number_3.head != NULL && Number_3.head->data == 0)
  {
    Node *ptr = Number_3.head;
    Number_3.head = Number_3.head->next;
    free(ptr);
  }
  Number_3.head = Reverse_LL(Number_3.head);
  Number_3.Len = Len(Number_3.head);
  return Number_3;
}

struct BigInteger mul(struct BigInteger Number_1, struct BigInteger Number_2)
{
  Node *Num_1 = Number_1.head, *Num_2 = Number_2.head;
  struct BigInteger Number_3 = initialize("");
  Number_3.Len = 0;
  if (Num_1 == NULL || Num_2 == NULL)
  {
    return Number_3;
  }
  struct BigInteger mid, result = initialize("");
  int CARRY = 0, Prod = 0, mbtowc = 0;
  while (Num_2 != NULL)
  {
    Num_1 = Number_1.head;
    CARRY = 0;
    mid = initialize("");
    for (int n = 0; n < mbtowc; n++)
    {
      insert_at_begin_at_end(&mid, 0);
    }
    while (Num_1 != NULL)
    {
      Prod = (Num_1->data) * (Num_2->data) + CARRY;
      insert_at_begin_at_end(&mid, Prod % 10);
      CARRY = Prod / 10;
      Num_1 = Num_1->next;
    }

    if (CARRY > 0)
    {
      insert_at_begin_at_end(&mid, CARRY);
    }

    result = add(mid, result);
    Node *current = mid.head;
    while (current != NULL)
    {
      Node *ptr = current;
      current = current->next;
      free(ptr);
    }

    Num_2 = Num_2->next;
    mbtowc++;
  }
  if (Number_1.sign != Number_2.sign)
  {
    result.sign = '-';
  }
  return result;
}

struct BigInteger div1(struct BigInteger Number_1, struct BigInteger Number_2)
{
  struct BigInteger Number_3 = initialize("0");
  Number_3.Len = 0;
  Number_3.sign = '+';
  int flag = 0;
  char sig = '+';
  if (Number_2.Len == 1 && Number_2.head->data == 0)
  {
    printf("Error!");
    return Number_3;
  }
  if (Number_1.sign != Number_2.sign)
    sig = '-';
  char t1 = Number_1.sign;
  char t2 = Number_2.sign;
  Number_1.sign = '+';
  Number_2.sign = '+';
  struct BigInteger ptr = add(Number_2, initialize("0"));
  while (Compare_nodes(Number_1, ptr) >= 0)
  {
    ptr = add(ptr, Number_2);
    Number_3 = add(Number_3, initialize("1"));
    flag = 1;
  }
  struct BigInteger zero = initialize("0");
  if (flag)
    Number_3.sign = sig;
  Number_1.sign = t1;
  Number_2.sign = t2;
  return Number_3;
}

struct BigInteger mod(struct BigInteger Number_1, struct BigInteger Number_2)
{
  struct BigInteger Number_3 = initialize("0");
  Number_3.Len = 0;
  Number_3.sign = '+';
  char sig = '+';
  int flag = 0;
  if (Number_2.Len == 1 && Number_2.head->data == 0)
  {
    printf("Error!");
    return Number_3;
  }
  if (Number_1.sign != Number_2.sign)
    sig = '-';
  char t1 = Number_1.sign;
  char t2 = Number_2.sign;
  Number_1.sign = '+';
  Number_2.sign = '+';
  struct BigInteger ptr = add(Number_2, initialize("0"));
  while (Compare_nodes(Number_1, ptr) >= 0)
  {
    ptr = add(ptr, Number_2);
    Number_3 = add(Number_3, initialize("1"));
  }
  struct BigInteger ptr2 = sub(ptr, Number_2);
  struct BigInteger modu = sub(Number_1, ptr2);
  Number_1.sign = t1;
  Number_2.sign = t2;
  return modu;
}