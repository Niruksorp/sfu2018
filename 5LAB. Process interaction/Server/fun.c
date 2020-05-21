#include "define.h"

///Массив дней в месяцах
const int g_days_in_month[] = { TEMP_ELEMENT, JANUARY, FEBRUARY, MARCH, APRIL,
                                MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

///Перечисление месяцов в году
enum e_month
{
    Jan = FIRST_MO,
    Feb,
    March,
    Aplil,
    May,
    June,
    July,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};
///Перечисление полей структуры
enum date_and_time
{
    Day,
    Month,
    Year,
    Hours,
    Minutes
};

bool is_leap_year(int year)
{
    return year % CHECK_LEEP_YEAR == 0;
}

struct Date_Time make_new_date(struct Date_Time current_date)
{
    struct Date_Time result_date;
    result_date.timezone = current_date.timezone;
    current_date.timezone = UTC8_KJA;
    result_date.minutes = current_date.minutes;
    result_date.hours = current_date.hours
                        + result_date.timezone
                        - current_date.timezone;
    if (result_date.hours < MIN_HOURS) //переход на предыдущий день
    {
        result_date.hours += NEW_DAY;
        result_date.minutes = current_date.minutes;
        result_date.day = current_date.day - PREV;
        if (result_date.day == GO_TO_NEXT) //переход на предыдущий месяц
        {
            result_date.month = current_date.month - PREV;
            if (result_date.month == GO_TO_NEXT) //переход на предыдущий год
            {
                result_date.year = current_date.year - PREV;
                if (result_date.year < GO_TO_NEXT)
                {
                    result_date.year += MAX_YEAR;
                }
                result_date.day = g_days_in_month[Dec];
                result_date.month = Dec;
            }
            else
            {
                result_date.year = current_date.year;
                result_date.day = g_days_in_month[result_date.month];
                if (result_date.month == Feb
                    && is_leap_year(current_date.year))
                {
                    result_date.day++;
                }
            }
        }
        else
        {
            result_date.year = current_date.year;
            result_date.day = result_date.day;
            result_date.month = current_date.month;
        }
    }
    else if (result_date.hours > MAX_HOURS || result_date.hours == MIN_HOURS) //переход на следующий день
    {
        result_date.hours %= NEW_DAY;
        result_date.day = current_date.day + NEXT;
        if (current_date.month == Feb
            && result_date.day > g_days_in_month[Feb] + NEXT) //переход на следующий месяц, если год високосный
        {
            result_date.month = March;
            result_date.day = NEXT;
        }
        else if (result_date.day > g_days_in_month[current_date.month]) //переход на след месяц для невисокосного года
        {
            result_date.month = current_date.month + NEXT;
            if (result_date.month > Dec) //переход на следующий год
            {
                result_date.year = current_date.year + NEXT;
                if (result_date.year > PREV_MAX_YEAR)
                {
                    result_date.year %= MAX_YEAR;
                }
                result_date.month = Jan;
                result_date.day = NEXT;
            }
            else
            {
                result_date.day = NEXT;
            }
        }
        else
        {
            result_date.day = current_date.day + NEXT;
            result_date.year = current_date.year;
            result_date.month = current_date.month;
        }
    }
    else
    {
        result_date.year = current_date.year;
        result_date.month = current_date.month;
        result_date.day = current_date.day;
    }
    return result_date;
}

void print_info(struct Date_Time temp)
{
    printf("Result of program working: \n");
    if (temp.day < HELP_FOR_PRINT) printf("0%d.", temp.day);
    else printf("%d.", temp.day);
    if (temp.month < HELP_FOR_PRINT) printf("0%d.", temp.month);
    else printf("%d.", temp.month);
    if (temp.year < HELP_FOR_PRINT) printf("0%d ", temp.year);
    else printf("%d ", temp.year);
    if (temp.hours < HELP_FOR_PRINT) printf("0%d.", temp.hours);
    else printf("%d.", temp.hours);
    if (temp.minutes < HELP_FOR_PRINT)  printf("0%d \n", temp.minutes);
    else  printf("%d \n", temp.minutes);	
}

struct Date_Time parser(char* temp)
{
    struct Date_Time temper;
    char * pch = strtok(temp,DELIMETR);
    temper.day = atoi(pch);
    pch = strtok(NULL,DELIMETR);
    temper.month = atoi(pch);
    pch = strtok(NULL, DELIMETR);
    temper.year = atoi(pch);
    pch = strtok(NULL, DELIMETR);
    temper.hours = atoi(pch);
    pch = strtok(NULL, DELIMETR);
    temper.minutes = atoi(pch);
    pch = strtok(NULL, DELIMETR);
    temper.timezone = atoi(pch);

    return temper;
}
