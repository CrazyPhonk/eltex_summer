#include <stdio.h>

int main() {
  int number, new_byte;

  // Ввод числа и нового значения байта
    scanf("%d", &number);
    printf("%p\n", &number);
    scanf("%d", &new_byte);

    // Проверка введенных значений
    if (number <= 0) {
        return 1; 
    }

    if (new_byte < 0 || new_byte > 255) {
        return 1;
    }

    // Изменение третьего байта через указатель
    unsigned char *byte_ptr = (unsigned char *)&number + 2; // +2 для третьего байта
    *byte_ptr = (unsigned char)new_byte;

  // Вывод результата

    return 0;
}
