#include "functions.c"

int main() {
  int counter = 0;
  struct list myList;
  initialiseList(&myList, &counter);
  printList(&myList, &counter);
  freeList(&myList, &counter);
  printList(&myList, &counter);
}