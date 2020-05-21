#ifndef STRUCT_INTERFACE_H
#define STRUCT_INTERFACE_H

#include "struct.h"

/*! \brief  Копирование структуры.
 *
 *  \param   Указатель на копируемую струтуру.
 *
 *  \return  Указатель на новый элемент, являющийся копией входного.
 *
 */
struct Zoo* copy_zoo(struct Zoo* p_old);

/*! \brief  Сортировка спиака по кол-ву редких животных.
 *
 *  \param   Указатель на начало сортируемого  списка.
 *
 *  \return  Указатель на начало уже отсортированного списка.
 *
 */
struct Node* sort(struct Node* p_root);
/*! \brief  Создвание нового листа.
 *
 *  \param   Указатель на элемент зопарк.
 *
 *  \return  Указатель на созданный лист.
 *
 */
struct Node* create_new_node(struct Zoo* p_tmp);

/*! \brief  Удаление структуры.
 *
 *  \param   Указатель на элемент Node.
 *
 *  \param   Номер удаляемой структуры.
 *
 *  \return  Указатель. Может изменятьс начало.
 *
 */
struct Node* delete_zoopark(struct Node* p_head, int num);

/*! \brief  Копирование списка.
 *
 *  \param   Указатель на начало копируемого списка.
 *
 *  \return  Возвращает указатель на начало нового, скопированного списка.
 *
 */
struct Node* copy_str(struct Node* p_old);

/*! \brief  Сортировка спиака по доле редких животных.
 *
 *  \param   Указатель на начало сортируемого  списка.
 *
 *  \return  Указатель на начало уже отсортированного списка.
 *
 */
struct Node* sort_for_second(struct Node* p_root);

/*! \brief  Удаление списка.
 *
 *  \param   Указатель на начало списка.
 *
 */
void delete_list(struct Node* p_head);

/*! \brief  Вывод одного экземпляра списка.
 *
 *  \param   Указатель на выводимый элемент.
 *
 */
void print_one_str(struct Node* p_tmp);

/*! \brief  Вывод всех элементов списка.
 *
 *  \param   Указатель на начало списка.
 *
 */
void print_all(struct Node* p_head);

/*! \brief  Вывод всех элементов очереди. П
 *
 *  \param   Указатель на начало списка.
 *
 */
void print_for_second_req(struct Node* p_head);

/*! \brief  Вывод одного экземпляра списка для второго запроса.
 *
 *  \param   Указатель на выводимый элемент.
 *
 */
void print_one_str_second_req(struct Node* p_tmp);

#endif // STRUCT_INTERFACE_H