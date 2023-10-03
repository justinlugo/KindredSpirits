// Justin Lugo
// COP 3502 - Fall 2020

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

typedef struct linkedList
{
  int data;
  struct linkedList *next;
}linkedList;


// Head insertion.
linkedList *insertNode(linkedList *head, int data)
{
  linkedList *temp = malloc(sizeof(linkedList));
  temp->data = data;
  temp->next = head;
  return temp;
}

// Postorder Traversal
// 1) Traverse left subtree, then right subtree.
// 2) Then root node of subtree.
linkedList *postOrder(node *root, linkedList *head)
{
  if (root == NULL)
  {
    return head;
  }

  head = postOrder(root->left, head);
  head = postOrder(root->right, head);
  head = insertNode(head, root->data);
  return head;
}

// Preorder Traversal - 
// 1) Start at root node, traverse left subtree.
// 2) Traverse left subtree of subnode, then right subtree.
linkedList *preOrder(node *root, linkedList *head)
{
  if (root == NULL)
  {
    return head;
  }

  head = insertNode(head, root->data);
  head = preOrder(root->left, head);
  head = preOrder(root->right, head);
  return head;
}

// Compares two inserted lists to see if they are the same or not.
int compareTreeLists(linkedList *a, linkedList *b)
{
  linkedList *headA = malloc(sizeof(linkedList));
  linkedList *headB = malloc(sizeof(linkedList));

  if (a == NULL && b == NULL)
  {
    free(headA);
    free(headB);
    return 1;
  }

  if (a == NULL || b == NULL)
  {
    free(headA);
    free(headB);
    return 0;
  }

  headA = a;
  headB = b;

  // Iterate through the linked list to see if every node is the same.
  while(headA != NULL || headB != NULL)
  {
    if (headA->data != headB->data)
    {
      free(headA);
      free(headB);
      return 0;
    }
    headA = headA->next;
    headB = headB->next;
  }
  free(headA);
  free(headB);
  return 1;
}

// Checks to see if two inserted trees are reflections of one another.
int isReflection(node *a, node *b)
{
  // If both are NULL, its reflective.
  if (a == NULL && b == NULL)
  {
    return 1;
  }

  if (a == NULL || b == NULL)
  {
    return 0;
  }

  if (a->data == b->data)
  {
    if (isReflection(a->left, b->right) && isReflection(a->right, b->left))
    {
      return 1;
    }
  }

  return 0;
}

// Creates a tree that is a reflection of the inserted tree at root.
node *makeReflection(node *root)
{
  node *newRoot;
  if (root == NULL)
  {
    return NULL;
  }

  newRoot = malloc(sizeof(node));
  newRoot->data = root->data;
  newRoot->left = makeReflection(root->right);
  newRoot->right = makeReflection(root->left);

  // Return pointer to the root of the new tree.
  return newRoot;
}

// This function determines whether the trees passed into it are "kindred spirits", or that the
// preorder traversal of one tree corresponds to the postorder traversal of the other tree.
int kindredSpirits(node *a, node *b)
{
  int compareTreeAB, compareTreeBA;
  linkedList *headA = malloc(sizeof(linkedList));
  linkedList *headB = malloc(sizeof(linkedList));
  if (a == NULL && b == NULL)
  {
    return 1;
  }

  if (a == NULL || b == NULL)
  {
    return 0;
  }

  compareTreeAB = compareTreeLists(preOrder(a, headA), postOrder(b, headB));
  compareTreeBA = compareTreeLists(preOrder(b, headB), postOrder(a, headA));

  return (compareTreeAB || compareTreeBA);
}

double difficultyRating(void)
{
  return 5.0;
}

double hoursSpent(void)
{
  return 10.0;
}