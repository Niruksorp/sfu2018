#include "def.h"
#include "struct.h"
#include "structInterface.h"
#include "func.h"
#include "struct.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/** \brief Main function
*
* \details Меню.
*
* \return Возвращает 0, если завершено корректно.
*/
int main()
{
    struct Node* p_head = NULL;
    struct Node* p_tail = NULL;
    struct Node* p_temployt;
    struct Node* p_tmp;
    struct Zoo* p_temp;
    int counter = 0;
    int selected;
    int menu;
    do
    {
        print_menu();
        menu = keyboard_input_int();
        switch(menu)
        {
        case CREATE_NEW:
             p_temp = (struct Zoo*) malloc(sizeof(struct Zoo));
             malloc_check(p_temp);
             bool flag_input_corrected = false;
             while (flag_input_corrected!=true)
             {
                    printf("Введите название зоопарка:");
                    p_temp->name = input_string();
                    printf("Введите кол-во зверей в зоопарке:");
                    p_temp->quantity = keyboard_input_int();
                    printf("Введите кол-во редких зверей в зоопарке:");
                    p_temp->quantity_rare_animals = keyboard_input_int();
                    if (p_temp->quantity >= p_temp->quantity_rare_animals)
                        flag_input_corrected = true;
                    else
                    printf("Введены некорректные значения. Повторите ввод.\n");
             }
                struct Node* new_list = create_new_node(p_temp);
            if (p_head == NULL)
            {
                p_head = new_list;
                p_tail = p_head;
                counter++;
                break;
            }
            p_tail->next = new_list;
            p_tail = p_tail->next;
            counter++;
            break;

        case EDIT_EXISTING:
            if(counter == 0)
            {
                printf(LIST_CLEAR_STR);
                break;
            }
            printf("Введите номер редактируемой структуры:");
            selected = keyboard_input_int();
            if (selected > counter)
            {
                printf(NO_STRUCTURE_EXISTS);
            }
            p_tmp = p_head;
            for (int i = START; i < selected; ++i)
                p_tmp = p_tmp->next;

            char* tmp_name = (char*)malloc(sizeof(p_tmp->zoopark->name));
            malloc_check(tmp_name);
            strcpy(tmp_name, p_tmp->zoopark->name);

            printf("Введите новое имя, или нажмите Enter, чтобы оставить без изменений:\n");
            fgets(p_tmp->zoopark->name,BUFF, stdin);
            fflush(stdin);
            if (p_tmp->zoopark->name[0] == '\n')
                strcpy(p_tmp->zoopark->name, tmp_name);
            free(tmp_name);
            bool flag_quantity_correct = false;
            int temp_quantity, temp_quantity_rare;
            while(flag_quantity_correct != true)
            {
                printf("Введите нужное кол-во животных:\n");
                temp_quantity = keyboard_input_int();
                printf("Введите нужное кол-во редких животных:\n");
                temp_quantity_rare = keyboard_input_int();
                if (temp_quantity_rare<=temp_quantity) flag_quantity_correct = true;
            }

            p_tmp->zoopark->quantity = temp_quantity;

            p_tmp->zoopark->quantity_rare_animals = temp_quantity_rare;

            break;

        case PRINT_ALL:
            print_all(p_head);
            break;

        case DELETE_STRUCT:
            if(counter == 0)
            {
                printf(LIST_CLEAR_STR);
                break;
            }
            printf("Введите номер удаляемой структуры:");
            int number = keyboard_input_int();
            if (number > counter)
            {
                printf(NO_STRUCTURE_EXISTS);
                break;
            }
            p_head = delete_zoopark(p_head,number);
            counter--;
            break;

        case WITHDRAW_ONE:
            if (counter == CLEAR_LIST)
            {
                printf(LIST_CLEAR_STR);
                break;
            }
            printf("Введите номер выводимой структуры:");
            int col = keyboard_input_int();
            if (col > counter)
            {
                printf(NO_STRUCTURE_EXISTS);
                break;
            }
            struct Node* tmp = p_head;
            for (int i = 1; i < col; i++)
                tmp = tmp->next;
            print_one_str(tmp);
            break;

        case FIRST_REQUEST:
            if(counter == CLEAR_LIST)
            {
                printf(LIST_CLEAR_STR);
                break;
            }
            p_temployt = sort(copy_struct(p_head));
            print_all(p_temployt);
            delete_list(p_temployt);
            break;

        case SECOND_REQUEST:
            if(counter == CLEAR_LIST)
            {
                printf(LIST_CLEAR_STR);
                break;
            }
            p_temployt = sort_for_second(copy_struct(p_head));
            print_for_second_req(p_temployt);
            delete_list(p_temployt);
            break;

        case EXIT:
            if (p_head == NULL)
                break;
            delete_list(p_head);
            break;

        default:
            printf("Несуществующий пункт меню");
            break;
        }
    } while (menu != EXIT);
    return CORRECT_COMPLETION;
}
