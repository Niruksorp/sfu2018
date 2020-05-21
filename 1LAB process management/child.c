#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#define UTC8_KJA 8
#define UTC0_GMT 0
#define UTC_MAX 14
#define UTC_MIN -12

void test_case();

const int g_days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //массив дней в году

///Перечисление месяцов в году
enum e_month
{
    Jan = 1,
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
///Структура, хранящая представление даты и времени
struct Date_Time
{
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    int timezone;
};
///Проверка года на високосность
bool is_leap_year(int year)
{
    return year % 4 == 0;
}
///Проверка соответствия даты 
bool check_date_is_correct(int day, int month, int year)
{
    if (year < 0 || year > 100) return false;
    if ((month < 1) || (month > 12))
        return false;
    if (day < 1)
        return false;
    if ((day > g_days_in_month[month]) && !(is_leap_year(year)))
        return false;
    if (month == 2)
        if (is_leap_year(year))
            if (day > g_days_in_month[month] + 1)
                return false;
    return true;
}

///Проверка соответсвия временным рамкам
bool check_time_is_correct(int hours, int min)
{
    if ((hours < 0) || (hours > 23) || (min < 0) || (min > 59)) return false;
    return true;
}

///Проверка корректности выделенной функцией malloc памяти
void malloc_check(char* p_tmpp)
{
    if (p_tmpp == NULL)
    {
        printf("Malloc не выделил память((((\n");
        exit(1);
    }
}

/**
 * \brief ввод строки до разделителя
 * \param[in] delim переменная обозначает, до какого сивола нужно читать
 * \return возвращает указатель на введенную строку
 */
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
        p_tmp_string = (char*)malloc(sizeof(char) * (lenght + 2));
        malloc_check(p_tmp_string);
        for (int i = 0; i < lenght; i++)
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
/*
* \brief функция для ввода даты
* \return возвращает массив введенных значений
 */
int* make_date_time()
{
    printf("Введите текущую дату в формате:ДД.ММ.ГГ: \n");
    int* input_date = (int*)malloc(sizeof(int) * 5);
    malloc_check((char*)input_date);
    char* strToSmth = input_string_to_delim('.');
    if (strToSmth == NULL)
    {
        return NULL;
    }
    input_date[0] = atoi(strToSmth);
    free(strToSmth);
    strToSmth = input_string_to_delim('.');
    if (strToSmth == NULL) return NULL;
    input_date[1] = atoi(strToSmth);
    free(strToSmth);
    strToSmth = input_string_to_delim('\n');
    if (strToSmth == NULL) return NULL;
    input_date[2] = atoi(strToSmth);
    free(strToSmth);
	
    printf("Введите текущее время в формате: HH.MM: \n");
    strToSmth = input_string_to_delim('.');
    if (strToSmth == NULL) return NULL;
    input_date[3] = atoi(strToSmth);
    free(strToSmth);
    strToSmth = input_string_to_delim('\n');
    if (strToSmth == NULL) return NULL;
    input_date[4] = atoi(strToSmth);
    free(strToSmth);

    return input_date;
}

/**
 * \brief функция высчитывает новую дату
 * \param[in] current_date переменная, в которой находится введенная пользователем дата
 * \param[in] timezone переменная, в которой хранится часовой пояс введенный пользователем
 * \return возвращает переменную типа Date_Time, в которой хранится интересующее пользователя время
 */
struct Date_Time make_new_date(struct Date_Time current_date, int timezone)
{
    struct Date_Time result_date;
    result_date.timezone = timezone;
    result_date.minutes = current_date.minutes;
    result_date.hours = current_date.hours
            + result_date.timezone 
                - current_date.timezone;
    if (result_date.hours < 0) //переход на предыдущий день
    {
        result_date.hours += 24;
        result_date.minutes = current_date.minutes;
        result_date.day = current_date.day - 1;
        if (result_date.day == 0) //переход на предыдущий месяц
        {
            result_date.month = current_date.month - 1;
            if (result_date.month == 0) //переход на предыдущий год
            {
                result_date.year = current_date.year - 1;
                if (result_date.year < 0) 
                {
                    result_date.year += 100;
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
    else if (result_date.hours > 23 || result_date.hours == 0) //переход на следующий день
    {
        result_date.hours %= 24;
        result_date.day = current_date.day + 1;
        if (current_date.month == Feb 
            && result_date.day > g_days_in_month[Feb] + 1) //переход на следующий месяц, если год високосный 
        {
            result_date.month = March;
            result_date.day = 1;
        }
        else if (result_date.day > g_days_in_month[current_date.month]) //переход на след месяц для невисокосного года
        {
            result_date.month = current_date.month + 1;
            if (result_date.month > Dec) //переход на следующий год
            {
                result_date.year = current_date.year + 1;
                if (result_date.year > 99)
                {
                    result_date.year %= 100;
                }
                result_date.month = Jan;
                result_date.day = 1;
            }
            else
            {
                result_date.day = 1;
            }
        }
        else
        {
            result_date.day = current_date.day + 1;
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
///Вывод сообщения о неккоректности ввода
void incorrect_value()
{
    while (getchar() != '\n');
    printf("Неккоректно введено значение. Попробуйте снова\n");
}
///Вывод даты
void print_info(struct Date_Time temp)
{
    if (temp.day < 10) printf("0%d.", temp.day);
    else printf("%d.", temp.day);
    if (temp.month < 10) printf("0%d.", temp.month);
    else printf("%d.", temp.month);
    if (temp.year < 10) printf("0%d ", temp.year);
    else printf("%d ", temp.year);
    if (temp.hours < 10) printf("0%d.", temp.hours);
    else printf("%d.", temp.hours);
    if (temp.minutes < 10)  printf("0%d", temp.minutes);
    else  printf("%d", temp.minutes);
}
/**
 * \brief функция получает часовой полис
 * \return возвращает переменную типа инт, содержащую часовой пояс, введенный пользователем
 */
int input_timezone() 
{
    bool flagCorrInp = false;
    int timezone = UTC8_KJA;
    while (!flagCorrInp)
    {
        printf("Введите часовой пояс UTC: ");
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
/**
 * \brief функция возвращает дату, полученную от пользователя
 * \return дата пользователя
 */
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
        if (!flagCorrInp) printf("Введена некорректная дата\n");
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

int main()
{
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("suite_for_1st_lab", NULL, NULL);
	
    CU_ADD_TEST(suite, test_case);
    struct Date_Time result_date = make_new_date(input_current_date_time(), 
        input_timezone());

    print_info(result_date);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
///Сопоставление дат
int is_date_equal(struct Date_Time first, struct Date_Time second)
{
    if (first.day == second.day
        && first.month == second.month
        && first.year == second.year
        && first.hours == second.hours)
        return  1;
    else return 0;
}
///test case
void test_case()
{
    struct Date_Time test_date;
    test_date.day = 1;
    test_date.month = 3;
    test_date.year = 00;
    test_date.hours = 1;
    test_date.minutes = 15;
    test_date.timezone = UTC8_KJA;
    struct Date_Time res_test_date = make_new_date(test_date, 0);
    test_date.day = 29;
    test_date.month = 2;
    test_date.year = 00;
    test_date.hours = 17;
    CU_ASSERT_EQUAL(is_date_equal(test_date, res_test_date), 1);

    test_date.day = 22;
    test_date.month = 2;
    test_date.year = 16;
    test_date.hours = 8;
    test_date.minutes = 15;
    test_date.timezone = UTC8_KJA;
    res_test_date = make_new_date(test_date, 5);
    test_date.day = 22;
    test_date.month = 2;
    test_date.year = 16;
    test_date.hours = 5;
    CU_ASSERT_EQUAL(is_date_equal(test_date, res_test_date), 1);

    test_date.day = 9;
    test_date.month = 5;
    test_date.year = 45;
    test_date.hours = 8;
    test_date.minutes = 15;
    test_date.timezone = UTC8_KJA;
    res_test_date = make_new_date(test_date, 5);
    test_date.day = 9;
    test_date.month = 5;
    test_date.year = 45;
    test_date.hours = 5;
    CU_ASSERT_EQUAL(is_date_equal(test_date, res_test_date), 1);
}
