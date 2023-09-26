#include "functions.c"

int main() {
  int counter = 0;
  struct list myList;
  initialiseList(&myList, &counter);
  printList(&myList, &counter);
  int N = 6;
  int i = 0;
  while (i < N) {
    pushInt(&myList, &counter, i % 9);
    printList(&myList, &counter);
    pullInt(&myList, &counter, 0);
    printList(&myList, &counter);
    i++;
  }
  clearList(&myList, &counter);
  printList(&myList, &counter);
}