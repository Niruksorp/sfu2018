#include "zagolovok.h"
    
    struct gun* first_gun;
    struct gun* second_gun; 
    struct gun* gGuns;
/**
 * \brief функция ввода пользователем временого промежутка
 * \param[in] pPointer результат, возвращаемый ф-цей malloc на равенство NULL
 */
void malloc_check(void* pPointer)
{
    if (pPointer == NULL)
    {
        perror("WARRNING");
        exit(1);
    }
}
/**
 * \brief функция ввода пользователем временого промежутка
 * \return возвращает переменную типа float
 */
float keyboard_input()
{
    printf("Enter the time interval (in seconds):");
    char endOfString = '\0';
    float data = 0;
    while (scanf("%f%c", &data, &endOfString) != 2 || endOfString != '\n') //if scanf
    {
        printf("\nIncorrect. Enter only a numer\n");
        while (getchar() != '\n');
    }
    return data;
}
/**
 * \brief функция, проверяющая, возможно ли ли задействовать поток, ответственный за перезарядку
 * \param[in] timeUnit введенный пользователем временной промежуток
 */
void* Changer(void* timeUnit)
{
    while (true)
    {
        for (int i = 0; i < QUANTITY_GUNS; i++)
        {
            if(gGuns[i].is_free == false 
               && pthread_mutex_trylock(&gGuns[i].quit_gun) != 0)
            {
                printf("Reload weapons %d\n", i + 1);
                fflush(stdout);
                sleep((int)(CHARGING_TIME* (*(float*)timeUnit)));
                gGuns[i].is_free = true;
                printf("Weapons %d is ready\n", i + 1);
                pthread_mutex_unlock(&gGuns[i].quit_gun);
            }
        }
    }
}
/**
 * \brief функция, проверяющая, возможно ли задействие потока, ответсвенного за стрельбу
 * \param[in] timeUnit введенный пользователем временной промежуток
 */
void* Shoter(void* timeUnit)
{
    while (true)
    {
        for (int i = 0; i < QUANTITY_GUNS; i++)
        {
            if (gGuns[i].is_free == true 
               && pthread_mutex_trylock(&gGuns[i].quit_gun)!=0)
            {
                printf("Shot preparation %d\n", i + 1);
                fflush(stdout);
                sleep((int)(SHOOTER_TIME*(*(float*)timeUnit)));
                gGuns[i].is_free = false;
                printf("*Buh*  %d\n", i + 1);
                pthread_mutex_unlock(&gGuns[i].quit_gun);
            }
        }
    }
}

int main()
{
    gGuns = malloc(sizeof(struct gun) * QUANTITY_GUNS);
    malloc_check(gGuns);
    first_gun = malloc(sizeof(struct gun*));
    malloc_check(first_gun);
    second_gun = malloc(sizeof(struct gun*));
    malloc_check(second_gun);

    first_gun->is_free = true;
    second_gun->is_free = true;

    gGuns[FIRST] = *first_gun;
    gGuns[SECOND] = *second_gun;

    pthread_mutex_init(&gGuns[FIRST].quit_gun, NULL);
    pthread_mutex_init(&gGuns[SECOND].quit_gun, NULL);

    float timeUnit = keyboard_input();
    
    pthread_t charging;
    pthread_create(&charging, NULL, Changer, &timeUnit); 

    pthread_t shooter;
    pthread_create(&shooter, NULL, Shoter, &timeUnit);

    pthread_join(charging, NULL); 
    pthread_join(shooter, NULL);

    return 0;  
}
