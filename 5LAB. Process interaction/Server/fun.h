#pragma once

/**
 * \brief проверка года на високостность
 * \param[in] year, год, проверяемый на високостность
 * \return возвращает истину, если год високостный
 */

bool is_leap_year(int year);
/**
 * \brief функция высчитывает новую дату
 * \param[in] current_date переменная, в которой находится введенная пользователем дата
 * \return возвращает переменную типа Date_Time, в которой хранится интересующее пользователя время
 */

struct Date_Time make_new_date(struct Date_Time current_date);
/**
 * \brief функция для печати информации
 * \param[in] temp, печатаемый элемент
 */

void print_info(struct Date_Time temp);
/**
 * \brief функция для перевода строки
 * \param[in] temp - указатель на строку с информацией
 * \return возвращает полученную информацию в переменной тип Date_Time
 */
struct Date_Time parser(char* temp);
