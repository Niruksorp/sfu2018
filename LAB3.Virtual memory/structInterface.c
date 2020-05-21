#include "structInterface.h"
#include "def.h"
#include "func.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Zoo* copy_zoo(struct Zoo* p_old)
{
    struct Zoo* new_zoo;
    new_zoo = (struct Zoo*)malloc(sizeof(struct Zoo));
    new_zoo->quantity = p_old->quantity;
    new_zoo->quantity_rare_animals = p_old->quantity_rare_animals;
    new_zoo->name = (char*)malloc(sizeof(char));
    strcpy(new_zoo->name, p_old->name);
    return (new_zoo);
}

struct Node* sort(struct Node* p_root)
{
    struct Node* new_root = NULL;

    while (p_root != NULL)
    {
        struct Node* p_node = p_root;
        p_root = p_root->next;
        if (new_root == NULL
            || p_node->zoopark->quantity_rare_animals > new_root->zoopark->quantity_rare_animals
           )
        {
            p_node->next = new_root;
            new_root = p_node;
        }
        else
        {
            struct Node* current = new_root;
            while (current->next != NULL
                   && !(p_node->zoopark->quantity_rare_animals
                        > current->next->zoopark->quantity_rare_animals
                       )
                  )
            {
                current = current->next;
            }

            p_node->next = current->next;
            current->next = p_node;
        }
    }
    return new_root;
}

struct Node* create_new_node(struct Zoo* p_tmp)
{
    struct Node* p_new_node = (struct Node*)malloc(sizeof(struct Node));
    malloc_check(p_new_node);
    p_new_node->zoopark = p_tmp;
    p_new_node->next = NULL;
    return p_new_node;
}

struct Node* delete_zoopark(struct Node* p_head, int num)
{
    struct Node* p_temp = p_head;
    if(num == START)
    {
        if (p_head->next != NULL)
        {
            p_head = p_head->next;
            free(p_temp->zoopark->name);
            free(p_temp->zoopark);
            free(p_temp);
        }
        else
        {
            free(p_head->zoopark->name);
            free(p_head->zoopark);
            free(p_head);
            return NULL;
        }
    }
    else
    {
        for (int i = START; i < num; i++)
            p_temp = p_temp->next;
        struct Node* p_prev = p_head;
        for (int i = START ; i < (num - 1); i++)
            p_prev = p_prev->next;
        if (p_temp->next != NULL)
        {
            p_prev->next = p_temp->next;
        }
        else
        {
            p_prev->next = NULL;
        }
    }
    free(p_temp);
    return p_head;
}

struct Node* copy_struct(struct Node* p_old)
{
    struct Node* p_new_head;
    p_new_head = (struct Node*)malloc(sizeof(struct Node));
    malloc_check(p_new_head);
    struct Node* p_temp;
    p_temp = p_old;

    struct Node* p_new_tail;
    p_new_tail = p_new_head;

    int counter = COUNTER_INIT;
    while (p_temp != NULL)
    {
        if(p_temp->zoopark->quantity_rare_animals != CLEAR_LIST)
        {
            counter++;
            struct Node *new_copy_list;
            new_copy_list = (struct Node *) malloc(sizeof(struct Node));
            malloc_check(new_copy_list);
            new_copy_list->zoopark = copy_zoo(p_temp->zoopark);
            new_copy_list->next = NULL;

            if (counter == ONE_ELEMENT)
            {
                p_new_head = new_copy_list;
                p_new_tail = new_copy_list;
            }
            else
            {
                p_new_tail->next = new_copy_list;
                p_new_tail = new_copy_list;
            }
        }
        p_temp = p_temp->next;
    }
    return p_new_head;
}

struct Node* sort_for_second(struct Node* p_root)
{
    struct Node* p_new_root = NULL;

    while (p_root != NULL)
    {
        struct Node* p_node = p_root;
        p_root = p_root->next;
        if (p_new_root == NULL
            || (((float)p_node->zoopark->quantity_rare_animals / p_node->zoopark->quantity)
                > ((float)p_new_root->zoopark->quantity_rare_animals / p_new_root->zoopark->quantity)
               )
           )
        {
            p_node->next = p_new_root;
            p_new_root = p_node;
        }
        else
        {
            struct Node* p_current = p_new_root;
            while (p_current->next != NULL
                   && !(((float)p_node->zoopark->quantity_rare_animals / p_node->zoopark->quantity)
                        > ((float)p_current->next->zoopark->quantity_rare_animals
                           / p_current->zoopark->quantity
                          )
                       )
                  )
            {
                p_current = p_current->next;
            }

            p_node->next = p_current->next;
            p_current->next = p_node;
        }
    }
    return p_new_root;
}

void delete_list(struct Node* p_head)
{
    struct Node* p_temp = p_head;
    struct Node* p_temp_next = p_temp->next;
    while (p_temp != NULL)
    {
        free(p_temp->zoopark->name);
        free(p_temp->zoopark);
        free(p_temp);
        p_temp = p_temp_next;
        if (p_temp != NULL)
        {
            p_temp_next = p_temp->next;
        }
    }
}

void print_one_str(struct Node* p_tmp)
{
    printf("%s\n%d\n%d\n",p_tmp->zoopark->name, p_tmp->zoopark->quantity,p_tmp->zoopark->quantity_rare_animals);
}

void print_all(struct Node* p_head)
{
    struct Node* p_tmp  = p_head;
    while (p_tmp != NULL)
    {
        print_one_str(p_tmp);
        p_tmp = p_tmp->next;
    }
}

void print_one_str_second_req(struct Node* p_tmp)
{
    printf("%s\n%f\n",p_tmp->zoopark->name,(float)p_tmp->zoopark->quantity_rare_animals / p_tmp->zoopark->quantity);
}

void print_for_second_req(struct Node* p_head)
{
    struct Node* p_tmp  = p_head;
    while (p_tmp != NULL)
    {
        print_one_str_second_req(p_tmp);
        p_tmp = p_tmp->next;
    }
}