#pragma once
/**
 * \brief проверка на високостность года
 * \param[in] year проверяемый год
 * \return возвращает истинну, если год високостный
 */
bool is_leap_year(int year);
/**
 * \brief проверка даты на правильность
 * \param[in] day проверяемый день
 * \param[in] month проверяемый месяц
 * \param[in] year проверяемый год
 * \return возврщает истину, если строка правильная
 */
bool check_date_is_correct(int day, int month, int year);
/**
 * \brief провека времени на корректность
 * \param[in] hours переменная часы
 * \param[in] min переменная минуты
 * \return возврщает истинну, если стока корректна
 */
bool check_time_is_correct(int hours, int min);
/**
 * \brief проверка на выделение памяти ф-цией malloc
 * \param[in] p_tmpp проверяемая переменная
 */
void malloc_check(char* p_tmpp);
/**
 * \brief ввод строки до разделителя
 * \param[in] delim переменная обозначает, до какого сивола нужно читать
 * \return возвращает указатель на введенную строку
 */
char* input_string_to_delim(char delim);
/**
* \brief функция для ввода даты
* \return возвращает массив введенных значений
 */
int* make_date_time();
/**
 * \brief обработка некорректного значения
 */
void incorrect_value();
/**
 * \brief функция получает часовой полис
 * \return возвращает переменную типа инт, содержащую часовой пояс, введенный пользователем
 */
int input_timezone();
/**
 * \brief функция возвращает дату, полученную от пользователя
 * \return дата пользователя
 */
struct Date_Time input_current_date_time();
/**
 * \brief ввод переврл структуры в строку
 * \param[in] temp принимаемая информация
 * \param[in] buff буффер
 */
void convert_into_the_string(struct Date_Time temp,char* buff);