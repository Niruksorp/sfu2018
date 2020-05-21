#include "func.h"
#include "def.h"
#include <stdlib.h>
#include <stdio.h>

void malloc_check(void* p_pointer)
{
    if (p_pointer == NULL)
    {
        perror("Ошибка");
        exit(ERROR_STATUS);
    }
}

char* input_string()
{
    char* p_input_string = NULL;
    char symb = '\0';
    int lenght = 0;
    do
    {
        scanf("%c", &symb);
        char* p_temp_string = (char*)realloc(p_input_string, sizeof(char) * (lenght + 1));
        if (symb == '\n') p_temp_string[lenght++] = '\0';
        else p_temp_string[lenght++] = symb;
        p_input_string = p_temp_string;
    } while (symb != '\n');
    return p_input_string;
}

int keyboard_input_int()
{
    char end_of_string = '\0';
    int min_value = MIN;
    int max_value = MAX;
    int data = MIN;
    while (scanf("%d%c", &data, &end_of_string) != CORRECT_SCANF_READING
           || end_of_string != '\n'
           || data < min_value
           || (data > max_value && max_value != MIN))
    {
        if (end_of_string != '\n')
            while (getchar() != '\n');
        if (max_value != MIN)
            printf("Incorrect. Enter only numbers from %d to %d\n",
                   min_value, max_value);
        else printf("Incorrect. Enter only numbers large than %d\n", min_value);
    }
    return data;
}

void print_menu()
{
    printf("\n1 - Добавить новый зоопарк.\n");
    printf("2 - Редактировать уже имеющуюся структуру.\n");
    printf("3 - Вывод всех зоопарков сразу.\n");
    printf("4 - Удалить структуру из списка. \n");
    printf("5 - Вывести одну структуру. \n");
    printf("6 - Сортировка по количеству редких животных. \n");
    printf("7 - Сортировка по проценту редких животных. \n");
    printf("8 - Выход.\n");
}