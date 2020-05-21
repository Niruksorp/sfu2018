#include <stdio.h>
#include "stdlib.h"
#include "fcntl.h"
#include "string.h"

#include "files.h"

/*! \brief главная функция программы
 *  \return 0 при успешном завершении
 */
int main(int argc, char* argv[])
{
    char fileName[] = "fileZoo.bin";
    char secondFileName[] = "secondFileZoo.bin";
    char addElements[] = "add";
    char delElements[] = "del";
    char output[] = "output";
    char help[] = "help";
    char modify[] = "modify";
    char firstReq[] = "firstReq";
    char secondReq[] = "secondReq";

    int fileDiscriptor = -1;
    int count = 0;
    int result = 0;

    count = numOnFile(fileName);
    if (argc < SECOND_ARGUMENT)
    {
    	printf(INPUT_ERROR_STRING);
    }
    else if ((!strcmp(argv[FIRST_ARGUMENT], help)) || (!strcmp(argv[FIRST_ARGUMENT], output)) ||
        (!strcmp(argv[FIRST_ARGUMENT], addElements)) || (!strcmp(argv[FIRST_ARGUMENT], delElements)) ||
        (!strcmp(argv[FIRST_ARGUMENT], firstReq)) || (!strcmp(argv[FIRST_ARGUMENT], secondReq)) ||
        (!strcmp(argv[FIRST_ARGUMENT], modify)))
    {
        if (!strcmp(argv[FIRST_ARGUMENT], help))
        {
            if (argc != SECOND_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                printf("1. Добавить элемент: add [Название зоопарка] [Количество животных] ");
                printf("[Количество Редких животных] \n");
                printf("2. Удалить элемент: del [Номер удаляемого элемента] \n");
                printf("3. Редактировать элемент: modify [Номер элемента] [name / quan / quar rare / all] \n");
                printf("   - Если [name / quantity / quantityRareAnimals], то затем еще одно поле [Новое значение] \n");
                printf("   - Если [all], то затем еще три поля [Новое значение] [Новое значение] ");
                printf("[Новое значение] \n");
                printf("4. Вывод всех элементов на экран: output \n");
                printf("5. Сортировка по количеству содержащихся в зоопарке редких животных: firstReq \n");
                printf("6. Сортировка по доле редких животных в зоопарке: secondReq \n");
                printf("7. Список команд: help \n");
            }
        }
        else if (!strcmp(argv[FIRST_ARGUMENT], output))
        {
            if (argc != SECOND_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                if (count != EMPTY_FILE)
                {
                    fileDiscriptor = open(fileName, O_RDONLY);
                    if (fileDiscriptor == DESCRIPTOR)
                    {
                        return FILE_ERROR;
                    }

                    struct Zoo data;
                    for (int i = 0; i < count; i++)
                    {
                        ssize_t reading = readingOne(fileDiscriptor, &data, sizeof (data));
                        if (reading == READ_ERROR)
                        {
                            return READ_ERROR;
                        }
                        printf("Структура №%d. Название зоопарка: %s. Кол-во животных: %d."
                               "Кол-во редких животных: %d.\n",
                                i + 1, data.name, data.quantity, data.quantityRareAnimals);
                    }
                }
                else
                {
                    printf(CLEAR_FILE_STRING);
                }
            }
        }

        else if (!strcmp(argv[FIRST_ARGUMENT], addElements))
        {
            if (argc != FIFTH_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                result = addElement(argc, argv, fileName);
                if (result == SUCCESS)
                {
                    printf("Данные успешно записаны в файл.\n");
                }
            }
        }

        else if (!strcmp(argv[FIRST_ARGUMENT], delElements))
        {
            if (argc != THIRD_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                if (count == EMPTY_FILE)
                {
                    printf(CLEAR_FILE_STRING);
                }
                else if (atoi(argv[SECOND_ARGUMENT]) > count)
                {
                    printf("Ошибка. 2-ой параметр больше, чем количество записей в файле.\n");
                }
                else
                {
                    result = delElement(argv, count, secondFileName, fileName);
                    printf("Элемент успешно удалён.\n");
                }
            }
        }

        else if (!strcmp(argv[FIRST_ARGUMENT], secondReq))
        {
            if (argc != SECOND_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                struct Node* pHead = createListOfFile(argc, argv, fileName, count);
                struct Node* pTemployt;
                if (pHead == NULL) printf("Список пуст");
                else
                {
                    pTemployt = sort(pHead);
                    printAll(pTemployt);
                    deleteList(pHead);
                }
            }
        }

        else if (!strcmp(argv[FIRST_ARGUMENT], firstReq))
        {
            if (argc != SECOND_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                if (count == EMPTY_FILE)
                {
                    printf(CLEAR_FILE_STRING);
                }
                else
                {
                    struct Node* pHead = createListOfFile(argc, argv, fileName,count);
                    struct Node* pTemployt;
                    if (pHead == NULL) printf("Список пуст");
                    else
                    {
                        pTemployt = sortForSecond(pHead);
                        printForSecondReq(pTemployt);
                        deleteList(pHead);
                    }
                }
            }
        }

        else if (!strcmp(argv[FIRST_ARGUMENT], modify))
        {
            struct Zoo data;
            if (argc != SEVENTH_ARGUMENT && argc != FIFTH_ARGUMENT)
            {
                printf(INPUT_ERROR_STRING);
            }
            else
            {
                if (count == EMPTY_FILE)
                {
                    printf(CLEAR_FILE_STRING);
                }
                else if (atoi(argv[SECOND_ARGUMENT]) > count)
                {
                    printf("Ошибка! 2-ой параметр больше, чем количество записей.\n");
                }
                else
                {
                    result = modifyElement(argc, argv, count, fileName);
                    if (result == SUCCESS)
                    {
                        printf("Элемент успешно отредактирован.\n");
                    }
                }
            }
        }
    }
    else
    {
        printf("Неверная команда для ввода параметров. Пропишите help для получения помощи.\n");
    }

    if (result == FILE_ERROR)
    {
        printf("Ошибка открытия файла.\n");
    }

    else if (result == MALLOC_ERROR)
    {
        printf("Malloc error.\n");
    }

    else if (result == INPUT_ERROR)
    {
        printf("Ошибка ввода параметров.\n");
    }

    else if (result == WRITE_ERROR)
    {
        printf("Ошибка записи.\n");
    }

    else if (result == READ_ERROR)
    {
        printf("Ошибка чтения.\n");
    }

    return END_OF_PROGRAMM;
}
