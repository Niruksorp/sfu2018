#include "define.h"
#include "fun.h"
///Массив дней в месяце
const int g_days_in_month[] = { TEMP_ELEMENT, JANUARY, FEBRUARY, MARCH, APRIL,
                                MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
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
    return year % LEEP_YEAR == YEAR_IS_LEEP;
}

bool check_date_is_correct(int day, int month, int year)
{
    if (year < MIN_YEAR || year > MAX_YEAR) return false;
    if ((month < MIN_MOUNTH) || (month > MAX_MOUNTH))
        return false;
    if (day < MIN_DAY)
        return false;
    if ((day > g_days_in_month[month]) && !(is_leap_year(year)))
        return false;
    if (month == FEB)
        if (is_leap_year(year))
            if (day > g_days_in_month[month] + LEEP_YEAR_MOUNTH)
                return false;
    return true;
}

bool check_time_is_correct(int hours, int min)
{
    if ((hours < MIN_HOURS) || (hours > MAX_HOURS) || (min < MIN_MINNUT) || (min > MAX_MINUTS)) return false;
    return true;
}

void malloc_check(char* p_tmpp)
{
    if (p_tmpp == NULL)
    {
        printf("Malloc did not allocate memory\n");
        exit(MALLOC_ERROR);
    }
}

char* input_string_to_delim(char delim)
{
    char* p_input_string = NULL;
    char symb = '\0';
    int lenght = 0;
    scanf("%c", &symb);
    while (symb != delim) 
    {
        if (symb < '0' || symb > '9')
        {
            free(p_input_string);
            return NULL;
        }
        char* p_tmp_string = NULL;
        p_tmp_string = (char*)malloc(sizeof(char) * (lenght + SIZE_FOR_STR));
        malloc_check(p_tmp_string);
        int i;
        for (i = 0; i < lenght; i++)
        {
            p_tmp_string[i] = p_input_string[i];
        }
        p_tmp_string[lenght++] = symb;
        p_tmp_string[lenght] = '\0';
        free(p_input_string);
        p_input_string = p_tmp_string;
        scanf("%c", &symb);
    }
    return p_input_string;
}

int* make_date_time()
{
    printf("Enter the current date in the format:DD.MM.YY: \n");
    int* input_date = (int*)malloc (sizeof(int) * SIZE_FOR_START_MALLOC);
    malloc_check((char*)input_date);
    char* strToSmth = input_string_to_delim(DELIMM);
    if (strToSmth == NULL)
    {
        return NULL;
    }
    input_date[FIRST_ARG] = atoi(strToSmth);
    free(strToSmth);
    strToSmth = input_string_to_delim(DELIMM);
    if (strToSmth == NULL) return NULL;
    input_date[SECOND_ARG] = atoi(strToSmth);
    free(strToSmth);
    strToSmth = input_string_to_delim(DELIMM_NEW);
    if (strToSmth == NULL) return NULL;
    input_date[THIRD_ARG] = atoi(strToSmth);
    free(strToSmth);
	
    printf("Enter the current time in the format: HH.MM: \n");
    strToSmth = input_string_to_delim(DELIMM);
    if (strToSmth == NULL) return NULL;
    input_date[FOURTH_ARG] = atoi(strToSmth);
    free(strToSmth);
    strToSmth = input_string_to_delim(DELIMM_NEW);
    if (strToSmth == NULL) return NULL;
    input_date[FIFTH_ARG] = atoi(strToSmth);
    free(strToSmth);

    return input_date;
}

void incorrect_value()
{
    while (getchar() != DELIMM_NEW);
    printf("The value entered is incorrect. Try it again\n");
}

int input_timezone() 
{
    bool flagCorrInp = false;
    int timezone = UTC8_KJA;
    while (!flagCorrInp)
    {
        printf("Enter time zone UTC: ");
        char sign = '\0';
        scanf("%c", &sign);
        if (sign != '-' && sign != '+' && sign != '0')
        {
            incorrect_value();
            continue;
        }
        if (sign == '0') timezone = UTC0_GMT;
        else
        {
            char* string_timezone = input_string_to_delim('\n');
            if (string_timezone == NULL)
            {
                incorrect_value();
                continue;
            }
            timezone = sign == '-' ? (-1) * atoi(string_timezone) 
                        : atoi(string_timezone);
        }
        flagCorrInp = (timezone >= UTC_MIN && timezone <= UTC_MAX);
    }
    return timezone;
}

struct Date_Time input_current_date_time()
{
    bool flagCorrInp = false;
    int* date_time = NULL;
    while (!flagCorrInp)
    {
        date_time = make_date_time();
        if (date_time == NULL)
        {
            incorrect_value();
            continue;
        }
        flagCorrInp = (check_date_is_correct(date_time[Day], 
            date_time[Month], 
            date_time[Year])
            && check_time_is_correct(date_time[Hours], 
            date_time[Minutes]));
        if (!flagCorrInp) printf("Incorrect date entered\n");
    }
    struct Date_Time current_date;
    current_date.year = date_time[Year];
    current_date.month = date_time[Month];
    current_date.day = date_time[Day];
    current_date.hours = date_time[Hours];
    current_date.minutes = date_time[Minutes];
    current_date.timezone = UTC8_KJA;
    return current_date;
}

void convert_into_the_string(struct Date_Time temp,char* buff)
{
    char tochka[SIZE_OF_DELIM_SIM] = DELIM;
    char day[SIZE_TEMP_ARRAY];
    char month[SIZE_TEMP_ARRAY];
    char year[SIZE_TEMP_ARRAY];
    char hours[SIZE_TEMP_ARRAY];
    char minutes[SIZE_TEMP_ARRAY];
    char timezone[SIZE_TEMP_ARRAY];

    sprintf(day, "%d", temp.day);
    sprintf(month, "%d", temp.month);
    sprintf(year, "%d", temp.year);
    sprintf(hours, "%d", temp.hours);
    sprintf(minutes, "%d", temp.minutes);
    sprintf(timezone, "%d", temp.timezone);

    strcat(buff, day);
    strcat(buff, tochka);
    strcat(buff, month);
    strcat(buff, tochka);
    strcat(buff, year);
    strcat(buff, tochka);
    strcat(buff, hours);
    strcat(buff, tochka);
    strcat(buff, minutes);
    strcat(buff, tochka);
    strcat(buff, timezone);
}