#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <malloc.h>

#define SHOOTER_TIME 5
#define CHARGING_TIME 15
#define FIRST 0
#define SECOND 1
#define QUANTITY_GUNS 2

struct gun 
{
    pthread_mutex_t quit_gun;
    bool is_free;
};

void* Shoter(void* timeUnit);

void* Changer(void* timeUnit);

void mallocCheck(void* pPointer);

float keyboard_input();
