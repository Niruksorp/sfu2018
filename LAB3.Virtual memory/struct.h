#ifndef STRUCT_H
#define STRUCT_H

struct Zoo
{
    char* name;
    int quantity;
    int quantity_rare_animals;
};

struct Node
{
    struct Node* next;
    struct Zoo* zoopark;
};

#endif