#include <stdio.h>
#include "stdlib.h"
#include "fcntl.h"
#include "string.h"
#include <unistd.h>
#include "files.h"

/*! \brief функция для  нахождения количества записей в файле
 *
 *  \param fileName имя файла
 *  \return статус завершения функции
 */
int numOnFile(char fileName[])
{
    int fileDiscriptor = open(fileName, O_RDONLY);
    if (fileDiscriptor == DESCRIPTOR)
    {
        return FILE_ERROR;
    }
    int end = lseek(fileDiscriptor, CURRENT_POSITION, SEEK_END);
    int size = sizeof(struct Zoo);
    int count = end / size;
    close(fileDiscriptor);

    return count;
}

/*! \brief функция чтения
 *  \param fileDiscriptor дискриптор файла
 *  \param databuf буфер
 *  \param length размер одной структуры
 *  \return статус завершения функции
 */
int readingOne(int fileDiscriptor, void* databuf, int length)
{
    ssize_t leftToRead = length;
    int empty = 0;
    while (leftToRead > empty)
    {
        ssize_t reading = read(fileDiscriptor, databuf, length);
        if (reading == DESCRIPTOR)
        {
            return READ_ERROR;
        }
        else
        {
            leftToRead -= reading;
        }
    }

    return SUCCESS;
}

/*! \brief функция записи
 *  \param fileDiscriptor дискриптор файла
 *  \param data структура данных
 *  \return статус завершения функции
 */
int writingOne(int fileDiscriptor, struct Zoo data)
{
    int count = sizeof (data);
    ssize_t leftToWrite = count;
    int empty = 0;
    while (leftToWrite > empty)
    {
        ssize_t writing = write(fileDiscriptor, &data, count);
        if (writing == DESCRIPTOR)
        {
            return WRITE_ERROR;
        }
        else
        {
            leftToWrite -= writing;
        }
    }

    return count;
}

/*! \brief функция записи данных в файл
 *  \param argc счетчик аргументов
 *  \param argv массив аргументов
 *  \param fileName имя файла
 *  \return статус завершения функции
 */
int addElement(int argc, char* argv[], char fileName[])
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fileDiscriptor = open(fileName, O_CREAT |O_WRONLY, mode);
    if (fileDiscriptor == DESCRIPTOR)
    {
        return FILE_ERROR;
    }
    struct Zoo data = readingToRec(argc, argv);
    lseek(fileDiscriptor, CURRENT_POSITION, SEEK_END);
    ssize_t sizeWriting = writingOne(fileDiscriptor, data);
    if (sizeWriting == WRITE_ERROR)
    {
        return WRITE_ERROR;
    }
    close(fileDiscriptor);
    
    return SUCCESS;
}

/*! \brief функция удаления одной записи из файла
 *  \param argv массив аргументов
 *  \param count количество записей
 *  \param secondFileName имя вторичного файла
 *  \param fileName имя файла
 *  \return статус завершения функции
 */
int delElement(char* argv[], int count,char secondFileName[], char fileName[])
{
    int delEl = 0;
    int one = 1;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fileDiscriptor = open(fileName, O_RDONLY);
    if (fileDiscriptor == DESCRIPTOR)
    {
        return FILE_ERROR;
    }
    int secondFileDiscriptor = open(secondFileName, O_CREAT | O_RDWR, mode);
    if (secondFileDiscriptor == DESCRIPTOR)
    {
        return FILE_ERROR;
    }
    struct Zoo data;
    if (atoi(argv[SECOND_ARGUMENT]))
    {
        delEl = atoi(argv[SECOND_ARGUMENT]) - one;
    }
    else
    {
        return INPUT_ERROR;
    }
    for (int i = 0; i < count; ++i)
    {
        if (i == delEl)
        {
            lseek(fileDiscriptor, sizeof (struct Zoo),SEEK_CUR);
        }
        else
        {
            ssize_t reading = readingOne(fileDiscriptor, &data, sizeof (data));
            if (reading == READ_ERROR)
            {
                return READ_ERROR;
            }
            ssize_t writing = writingOne(secondFileDiscriptor, data);
            if (writing == WRITE_ERROR)
            {
                return WRITE_ERROR;
            }
        }
        
    }
    close(fileDiscriptor);
    close(secondFileDiscriptor);
    remove(fileName);
    rename(secondFileName, fileName);
    return SUCCESS; 
}

/*! \brief функция редактирования одной записи из файла
 *  \param argc счетчик аргументов
 *  \param argv массив аргументов
 *  \param count количество записей
 *  \param fileDiscriptor дискриптор файла
 *  \param filename имя файла
 *  \return статус завершения функции
 */
int modifyElement(int argc, char*argv[], int count, char fileName[])
{
    int modifyEl = 0;
    int one = 1;
    char name[] = "name";
    char quantity[] = "quantity";
    char quantityRare[] = "quantityRareAnimals";
    char allFields[] = "all";
    char zero[] = "0";
    if (atoi(argv[SECOND_ARGUMENT]))
    {
        modifyEl = atoi(argv[SECOND_ARGUMENT]) - one;
    }
    else
    {
        return INPUT_ERROR;
    }
    struct Zoo data;
    int fileDiscriptor = open(fileName, O_RDWR);
    lseek(fileDiscriptor, sizeof (struct Zoo) * modifyEl, SEEK_SET);
    ssize_t reading = readingOne(fileDiscriptor, &data, sizeof (data));
    if (reading == READ_ERROR)
    {
        return READ_ERROR;
    }
    if (!strcmp(argv[THIRD_ARGUMENT], name))
    {
       strcpy(data.name, argv[FOURTH_ARGUMENT]);
    }
    else if (!strcmp(argv[THIRD_ARGUMENT], quantity))
    {
        if (atoi(argv[FOURTH_ARGUMENT]) < data.quantityRareAnimals)
        {
            return INPUT_ERROR;
        }
        else if (atoi(argv[FOURTH_ARGUMENT]) > ZERO)
        {
            data.quantity = atoi(argv[FOURTH_ARGUMENT]);
        }
        else
        {
            return INPUT_ERROR;
        }
    }
    else if (!strcmp(argv[THIRD_ARGUMENT], quantityRare))
    {
        if (atoi(argv[FOURTH_ARGUMENT]) > data.quantity)
        {
            return INPUT_ERROR;
        }
        else if (atoi(argv[FOURTH_ARGUMENT]) > ZERO || strcmp(argv[FOURTH_ARGUMENT], zero) == ZERO)
        {
            data.quantityRareAnimals = atoi(argv[FOURTH_ARGUMENT]);
        }
        else
        {
            return INPUT_ERROR;
        }
    }
    else if (!strcmp(argv[THIRD_ARGUMENT], allFields))
    {
        strcpy(data.name, argv[FOURTH_ARGUMENT]);

        if (atoi(argv[FIFTH_ARGUMENT]) < (atoi(argv[SIXTH_ARGUMENT])))
        {
            return INPUT_ERROR;
        }
        else if (atoi(argv[FIFTH_ARGUMENT]) > ZERO)
        {
            data.quantity = atoi(argv[FIFTH_ARGUMENT]);
        }
        else
        {
            return INPUT_ERROR;
        }

        if (atoi(argv[SIXTH_ARGUMENT]) > ZERO || strcmp(argv[SIXTH_ARGUMENT], zero) == ZERO)
        {
            data.quantityRareAnimals = atoi(argv[SIXTH_ARGUMENT]);
        }
        else
        {
            return INPUT_ERROR;
        }
    }
    lseek(fileDiscriptor, sizeof (struct Zoo) * modifyEl, SEEK_SET);
    ssize_t writing = writingOne(fileDiscriptor, data);
    if (writing == WRITE_ERROR)
    {
        return WRITE_ERROR;
    }
    return SUCCESS;
}

/*! \brief функция чтения данных для полседующей записи в файл
 *  \param argc счетчик аргументов
 *  \param argv массив аргументов
 *  \return структура данных
 */
struct Zoo readingToRec(int argc, char* argv[])
{
    char zero[] = "0";
    struct Zoo data;
    strcpy(data.name, argv[SECOND_ARGUMENT]);
    if (atoi(argv[FOURTH_ARGUMENT]) > atoi(argv[THIRD_ARGUMENT]))
    {
        printf("Ошибка ввода! Редких животных не может быть больше обычных\n");
        exit(INPUT_ERROR);
    }

    if (atoi(argv[THIRD_ARGUMENT]) > ZERO)
    {
        data.quantity = atoi(argv[THIRD_ARGUMENT]);
    }
    else
    {
        printf("Ошибка ввода! 3 аргумент - целочисленное значение. Повторите ввод.\n");
        exit(INPUT_ERROR);
    }

    if (atoi(argv[FOURTH_ARGUMENT]) > ZERO || strcmp(argv[FOURTH_ARGUMENT], zero) == ZERO)
    {
        data.quantityRareAnimals = atoi(argv[FOURTH_ARGUMENT]);
    }
    else
    {
        printf("Ошибка ввода! 4 аргумент - целочисленное значение. Повторите ввод.\n");
        exit(INPUT_ERROR);
    }

    return data;
}
/*! \brief функция создание списка на осное файла
 *  \param argc счетчик аргументов
 *  \param argv массив аргументов
 *  \param filename название документа
 *  \param num количество записей
 *  \return голова списка
 */
struct Node* createListOfFile(int argc, char* argv[],char filename[], int num)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fileDiscriptor = open(filename, O_CREAT | O_RDONLY , mode);

    struct Node* head = NULL;
    struct Node* temp = NULL;

    int flag = 0;
    for (int i = 0; i < num; i++)
    {
        struct Node* p_new = (struct Node*)malloc(sizeof(struct Node));
        p_new->zoopark = (struct Zoo*)malloc(sizeof(struct Zoo));
        readingOne(fileDiscriptor,  p_new->zoopark, sizeof (struct Zoo));
        if ( p_new->zoopark->quantityRareAnimals == 0) break;
        if (flag == 0)
        {
            head = p_new;
            temp = head;
            flag++;
        }
        else temp->next = p_new;
        temp = p_new;
        p_new->next = NULL;
    }
    close(fileDiscriptor);
    return head;
}
/*! \brief функция сортировка по количеству редких животных
 *  \param pRoot голова не сортированного списка
 *  \return голова сортированного списка
*/
struct Node* sort(struct Node* pRoot)
{
    struct Node* newRoot = NULL;

    while (pRoot != NULL)
    {
        struct Node* pNode = pRoot;
        pRoot = pRoot->next;
        if (newRoot == NULL
            || pNode->zoopark->quantityRareAnimals > newRoot->zoopark->quantityRareAnimals
                )
        {
            pNode->next = newRoot;
            newRoot = pNode;
        }
        else
        {
            struct Node* current = newRoot;
            while (current->next != NULL
                   && !(pNode->zoopark->quantityRareAnimals
                        > current->next->zoopark->quantityRareAnimals
            )
                    )
            {
                current = current->next;
            }

            pNode->next = current->next;
            current->next = pNode;
        }
    }
    return newRoot;
}
/*! \brief функция вывода одной структуры
 *  \param pTmp указатель на выводимую структуру
*/
void printOneStr(struct Node* pTmp)
{
    printf("%s\n%d\n%d\n",pTmp->zoopark->name, pTmp->zoopark->quantity,pTmp->zoopark->quantityRareAnimals);
}
/*! \brief функция вывода, использует printOneStr
 *  \param pTmp указатель на голову выводимого списка
*/
void printAll(struct Node* pHead)
{
    struct Node* pTmp  = pHead;
    while (pTmp != NULL)
    {
        printOneStr(pTmp);
        pTmp = pTmp->next;
    }
}
/*! \brief функция вывода одной структуры для запроса 2
 *  \param pTmp указатель на выводимую структуру
*/
void printOneStrSecondReq(struct Node* pTmp)
{
    printf("%s\n%f\n",pTmp->zoopark->name,(float)pTmp->zoopark->quantityRareAnimals / pTmp->zoopark->quantity);
}
/*! \brief функция вывода, использует printOneStrSecondReq
 *  \param pTmp указатель на голову выводимого списка
*/
void printForSecondReq(struct Node* pHead)
{
    struct Node* pTmp  = pHead;
    while (pTmp != NULL)
    {
        printOneStrSecondReq(pTmp);
        pTmp = pTmp->next;
    }
}
/*! \brief функция сортировка по доле редких животных
 *  \param pRoot голова не сортированного списка
 *  \return голова сортированного списка
*/
struct Node* sortForSecond(struct Node* pRoot)
{
    struct Node* pNewRoot = NULL;

    while (pRoot != NULL)
    {
        struct Node* pNode = pRoot;
        pRoot = pRoot->next;
        if (pNewRoot == NULL
            || (((float)pNode->zoopark->quantityRareAnimals / pNode->zoopark->quantity)
                > ((float)pNewRoot->zoopark->quantityRareAnimals / pNewRoot->zoopark->quantity)
            )
                )
        {
            pNode->next = pNewRoot;
            pNewRoot = pNode;
        }
        else
        {
            struct Node* pCurrent = pNewRoot;
            while (pCurrent->next != NULL
                   && !(((float)pNode->zoopark->quantityRareAnimals / pNode->zoopark->quantity)
                        > ((float)pCurrent->next->zoopark->quantityRareAnimals
                           / pCurrent->zoopark->quantity
                        )
            )
                    )
            {
                pCurrent = pCurrent->next;
            }

            pNode->next = pCurrent->next;
            pCurrent->next = pNode;
        }
    }
    return pNewRoot;
}
/*! \brief функция удааления списка
 *  \param pHead голова удаляемоого списка
*/
void deleteList(struct Node* pHead)
{
    struct Node* pTemp = pHead;
    struct Node* p_temp_next = pTemp->next;
    while (pTemp != NULL)
    {
        free(pTemp->zoopark->name);
        free(pTemp->zoopark);
        free(pTemp);
        pTemp = p_temp_next;
        if (pTemp != NULL)
        {
            p_temp_next = pTemp->next;
        }
    }
}