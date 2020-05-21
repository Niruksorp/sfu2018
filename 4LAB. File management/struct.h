#pragma once

#include "define.h"
/**
 *\brief Структура, описывающая зоопарк
 *\Поля: Название зоопарка, количество животных, количество редких животных
 **/
struct Zoo
{
    char name[LENGTH];
    int quantity;
    int quantityRareAnimals;
};
/**
 *\brief Структура, описывающая узел
 *\Поля: хранит указатель на следующий элемент и экз структуры зоопарк
 **/
struct Node
{
    struct Node* next;
    struct Zoo* zoopark;
};