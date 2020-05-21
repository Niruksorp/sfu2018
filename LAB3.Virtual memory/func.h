#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*! \brief  Чтение строки с клавиатуры.
 *
 *  \return  Указатель на сттроку со считанной информацией.
 *
 */
char* input_string();

/*! \brief  Считывание с клавиатуры целого числа.
 *
 *  \return  Целое число.
 *
 */
int keyboard_input_int();

/*! \brief  Функция, которая печатает меню. */
void print_menu();

/*! \brief  Проверка памяти, выделенной ф-цией malloc.
 *
 *  \param   Указатель на выделенную память.
 */
void malloc_check(void* p_pointer);

#endif // FUNCTIONS_H