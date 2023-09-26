#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#define BLOCKSIZE 1
#define maxInput 5*1

//PART 1 --------------------------------------------------------------------

//This is the node struct where i is an int stored in the node with next
//and previous pointers.
struct node {
  int i;
  struct node *next;
  struct node *prev;
};

//This is the list struct with pointers for head, tail, left and right
//along with length which is nodes in free space. 
struct list {
	struct node *head;
	struct node *tail;
	struct node *right;
	struct node *left;
	int length;
};

//Allocator is used for assigning dynamic memory allocation for pointer.
void *allocator(int size, int *counter) {

        int *thisPtr = (int*)malloc(sizeof(size));
        if (thisPtr != NULL) {
            ++*counter;
        }
        
        return thisPtr;
}

//deAllocator frees the memory allocation for a pointer.
void deAllocator(void *p, int *counter) {

    if (p != NULL) {
        free(p);
        --*counter;
    }
}

//Points pList left to same node as pList head and that pList right
//points to pList tail. Also if list is empty, deAllocates head and tail.
void freeList(struct list *pList, int *counter) {
    
    if (!pList->length && pList->head == pList->left && pList->tail == pList->right) { 
        deAllocator(pList->head, counter);
        deAllocator(pList->tail, counter);
        if (!*counter) {
            
            pList->head = NULL;
            pList->left = NULL;
            pList->tail = NULL;
            pList->right = NULL;
            pList->length = -1;
        }
    }
}

//Calls allocator to allocate head and tail and initalise members of list.
void initialiseList(struct list *pList, int *counter) {
    
    pList->head = allocator(sizeof(struct node), counter);
    pList->tail = allocator(sizeof(struct node), counter);
    pList->left = pList->head;
    pList->right = pList->tail;
    pList->head->prev = NULL;
    pList->tail->next = NULL;
    pList->length = 0;
    pList->head->i = 0;
    pList->tail->i = 0;
    pList->head->next = pList->tail;
    pList->tail->prev = pList->head;
}

//Prints out the current list to user.
void printList(struct list *pList, int *counter) {
    struct node *cur  = pList->head;
    while (cur) {
        printf(" | %d | ", cur->i);
        cur = cur->next;
    }
    if (!(pList->head) || !(pList->tail) || *counter == 0)
        printf(" ||");
    printf("\ncounter = %d\n", *counter);
}

//PART 2 --------------------------------------------------------------------

//This will allocate new struct nodes and link the node to existing ones.
void allocateBlock(struct list *pList, int *counter, int nNodes) {
    
    for (int i = 0; i < nNodes; i++) {
        struct node* thisNode = allocator(sizeof(struct node), counter);
        
        thisNode->next = pList->left->next;
        thisNode->prev = pList->left;
        pList->left->next->prev = thisNode;
        pList->left->next = thisNode;
        
        pList->length += 1;
        thisNode->i = -1;
    }
}

//Frees currently allocated blocks from middle using deAllocator.
void deAllocateBlock(struct list *pList, int *counter, int nNodes) {
    int n = (pList->length) - nNodes;
    while ((pList->length) > n) {
        struct node *temp = pList->left->next;
	pList->left->next->next->prev = pList->left;
        pList->left->next = temp->next;
        deAllocator(temp, counter);
        (pList->length)--;
    }
}

//PART 3 --------------------------------------------------------------------

//Allocates block and pushes an int to the list depending on if it is
//odd or even.
void pushInt(struct list *pList, int *counter, int i) {
    
    if (!pList->length) {
        allocateBlock(pList, counter, BLOCKSIZE);
    }
    
    //Check if ODD
    if (i % 2 == 1) {
        if (pList->left->next->i == -1) {
            pList->left = pList->left->next;
            pList->left->i = i;
            pList->length-=1;
        }
    //Else is EVEN
    } else {
        if (pList->right->prev->i == -1) {
            pList->right = pList->right->prev;
            pList->right->i = i;
            pList->length-=1;
        }
    }
}

//Pulls an int from the list depending on if it is odd or even.
//Also changes node pointed by pList to previous node.
void pullInt(struct list *pList, int *counter, int i) {
    
    //Check if ODD
    if (i % 2 == 1) {
        if (pList->head != pList->left) {
            pList->left = pList->left->prev;
            pList->left->next->i = -1;
            pList->length+=1;
        }
    //Else is EVEN
    } else {
        if (pList->tail != pList->right) {
            pList->right = pList->right->next;
            pList->right->prev->i = -1;
            pList->length+=1;
        }
    }
}

//Clears the list by pulling from pList right and left until
//pList hits head and tail.
void clearList(struct list *pList, int *counter) {
    
    while (pList->right != pList->tail) {
        pullInt(pList, counter, 0);
    }
    while (pList->left != pList->head) {
        pullInt(pList, counter, 1);
    }
    deAllocateBlock(pList, counter, pList->length);
    freeList(pList, counter);
}

//PART 4 --------------------------------------------------------------------

//Takes inputs from the user and parses to getInput, first input pushes to
//the list and the second input pulls from the list.
int getInput(char *s) {
    char c = '\0';
    int i = 0;
    
    while (c != '\n' && i < maxInput) {
        c = getchar();
        if (c >= '0' && c <= '9') {
            s[i] = c;
            i++;
        }
    }
    if (i == maxInput) {
        while (c != '\n') {
           c = getchar();
        }
    }
    return i;
}