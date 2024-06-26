#include <stdio.h>
#include <stdlib.h>

int main() {
  int number;
  int new_byte;
  printf("Your num: ");
  scanf("%d", &number);
  printf("New byte: ");
  scanf("%d", &new_byte);
  int *ptr1;
  ptr1= &number;
  char * ptr2 = (char*)ptr1+2;

  printf("%d\n", *ptr2);
  *ptr2 = new_byte;
  printf("%d\n", *ptr2);
  printf("New num: %d\n", number);
}
