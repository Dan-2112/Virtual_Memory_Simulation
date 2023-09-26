#include "functions.c"

int main() {
  int counter = 0;
  struct list myList;
  initialiseList(&myList, &counter);
  printList(&myList, &counter);
  char sPush[maxInput + 1];
  char sPull[maxInput + 1];
  int lenPush = getInput(sPush);
  int lenPull = getInput(sPull);
  int i = 0;
  int j = 0;
  while ((i + j) < (lenPush + lenPull)) {
    if (i < lenPush) {
      pushInt(&myList, &counter, sPush[i] - '0');
      i++;
      printList(&myList, &counter);
    }
    if (j < lenPull) {
      pullInt(&myList, &counter, sPull[j] - '0');
      j++;
      printList(&myList, &counter);
    }
  }
  printList(&myList, &counter);
  clearList(&myList, &counter);
  printList(&myList, &counter);
}