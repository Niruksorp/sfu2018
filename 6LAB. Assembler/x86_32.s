.data
#Надписи для printf
test_format:
	.string "Testing\n"

start_format:
	.string "Input array:\n\n"
end_format:
	.string "After task:\n\n"

enter_line_format:
	.string "Enter line %d\n"  
scanf_format:
	.string "%d"			# Надпись для ввода элемента
enter_size_format:
	.string "Enter array size:\n" 
printf_format:
	.string "Enter array elem\n"		
init_end_format:
	.string "Array initialized\n"
check_init_format:
	.string "Bytes count: %d\n Bytes count per string: %d\n Elements count: %d\n Elements count per string: %d\n\n\n"
print_array_format:
	.string "%d  " #Формат вывода одного элемента
next_line_format:
	.string "\n" 	#Формат для переноса строки
.equ ELEM_SIZE, 4	#Константа. Размер одного элемента в байтах
enter_number_format:
	.string "Enter line number:\n"
#Области памяти
LINE_SIZE_BYTES:
	.long 4, 0	#Область памяти для хранения количества байт в строке
ARRAY_SIZE_BYTES:
	.long 4, 0	#Область памяти для хранения количества байт в массиве
TOTAL_COUNT:
	.long 4, 0	#Область памяти для хранения количества элементов в массиве
array_size:
	.space 4, 0	#Область памяти для хранения размерности массива

array_elem:
	.space 4, 0	#Область памяти для считывания элеманта массива
OFFSET:
	.space 4, 0	#Область памяти для смещения

.text
#Функция инициализации массива
init_array:
	pushl %ebp
	movl %esp, %ebp 	 #сохранение указателя на стек

	pushl $enter_size_format #передача формата строки в вызываемую ф-цию printf
	call printf 		 
	addl $4, %esp 		 #выравнивание стека 
	
	pushl $array_size	 #передаем адресс для ввода
	pushl $scanf_format      #передача формата
	call scanf		 
	addl $8, %esp		 #выравнивание стека
	
	movl $ELEM_SIZE, %eax    #запись размера 1 элемента в регистр eax
	mull array_size		 #умножение количества элементов строки на размер одного элемента (кол-во эл-тов * size)
	movl %eax, LINE_SIZE_BYTES #сохранение получившегося значения в область памяти LINE_SIZE_BYTES
	mull array_size		 #умножение размера строки в байтах на количество строк
	movl %eax, ARRAY_SIZE_BYTES #сохранение полученного значения в область памяти ARRAY_SIZE_BYTES
	movl array_size, %eax	#Перемещение размерности массива в eax
	mull array_size		
	movl %eax, TOTAL_COUNT	#запись результата в область памяти TOTAL_COUNT

	pushl array_size	#Передача параметров в функцию printf через стек
	pushl TOTAL_COUNT
	pushl LINE_SIZE_BYTES
	pushl ARRAY_SIZE_BYTES
	pushl $check_init_format
	call printf		
	addl $12, %esp 		#выравнивание стека

	pushl ARRAY_SIZE_BYTES #передача параметра для функции malloc
	call malloc		
	addl $4, %esp		#выравнивание стека
	movl %eax, %esi		#сохранение выделенной памяти в регистре esi
	
	cmpl $0, array_size	#проверка размерности 
	je end_init
	jng end_init
	movl $0, %edi		# в регистре edi - счетчик введеных строк
enter_line:
	movl $0, %ebx 		# в регистре ebx - счетчик введеных элементов строки
	cmpl array_size, %edi	#проверяем, не дости ли счетчик нужного значения
	je end_init		#если достиг, выходим из функции
	incl %edi		
	pushl %edi		
	pushl $enter_line_format
	call printf		
	decl %edi
	addl $8, %esp		#выравнивание стека
enter_element:
	pushl $printf_format	#передача параметров в функцию
	call printf		
	addl $4, %esp		#выравнивание стека

	pushl $array_elem	#передача параметров в функцию
	pushl $scanf_format
	call scanf		
	addl $8, %esp		#выравнивание стека
	movl LINE_SIZE_BYTES, %eax	#определяем необходимое смещение для вставки элемента
	mull %edi
	movl %eax, %ecx
	movl $ELEM_SIZE, %eax
	mull %ebx
	addl %eax, %ecx
	movl array_elem, %eax
	movl %eax, (%esi, %ecx)		#сохраняем элемент по полученному смещению
	incl %ebx		#увеличиваем счетчик элементов
	cmpl %ebx, array_size	#проверяем, не достиг ли счетчик нужного значения, и если достиг переходим на ввод следующей строки
	jne enter_element
	incl %edi		#увеличиваем счетчик строк
	jmp enter_line
end_init:
	pushl $init_end_format	#передача параметров в функцию
	call printf		
	addl $4, %esp		#выравнивание стека
	movl %ebp, %esp		#возвращение сохраненного указателя стека
	popl %ebp		#возвращение регистра ebx
	ret 			#выход из функции
	
#Функция инициализации массива

#Функция для вывода массива
print_array:
	pushl %ebp		#сохранения регистра ebp на стеке
	movl %esp, %ebp		#сохранение указателя на стек
	movl $0, %ebx		#обнуление счетчика ebx
	movl array_size, %edi	#запись размерности массива в edi
rep:
	pushl (%esi, %ebx, ELEM_SIZE)	#передача параметра функции используя смещения
	pushl $print_array_format	
	call printf			#вызов функции
	addl $8, %esp			#выравнивание стека
	addl $1, %ebx			#увеличение счетчика
	cmpl %ebx, %edi			#сравниваем счетчик, если достиг размерности, переводим на следующую строку
	je next_line			
cont:		
	cmpl %ebx, TOTAL_COUNT		#сравниваем счетчик с количеством элементов в массива, если равен, то выход из функции
	je end_print			
	jng end_print			
	jmp rep				
next_line:
	addl array_size, %edi		
	pushl $next_line_format		#перевод на новую строку
	call printf			
	addl $4, %esp			
	jmp cont			
	
end_print:
	movl %ebp, %esp			#возвращение сохраненного значения
	popl %ebp			#возвращение регистра ebp
	ret				#выход из функции

#Функция для вывода массива

#Функция для работы с массивом
array_handler:
	pushl %ebp
	movl %esp, %ebp
	
	pushl $enter_number_format
	call printf
	addl $4, %esp

	pushl $array_elem 
	pushl $scanf_format
	call scanf
	addl $8, %esp

	pushl %esi

	movl array_elem, %ebx
	decl %ebx
	movl LINE_SIZE_BYTES, %eax
	mull %ebx
	addl %eax, %esi

	movl array_elem, %ebx
	decl %ebx
	movl (%esi, %ebx, ELEM_SIZE), %ebx
  
	movl $0, %eax
	movl array_size, %edi
adding:
	cmpl %eax, %edi
	je end_handle
	movl (%esi, %eax, ELEM_SIZE), %ecx
	addl %ebx, %ecx
	movl %ecx, (%esi, %eax, ELEM_SIZE)
	incl %eax
	jmp adding
		
end_handle:
	popl %esi
	movl %ebp, %esp
	popl %ebp
	ret



.globl main
#Главная функция
main:
	call init_array		#вызов функции инициализации массива
	movl $0, %eax		#сохранения в регистр eax 0
	cmpl %eax, array_size	#сравнение размерности с 0, если равен - выход из программы
	je end
	jng end

	pushl $start_format
	call printf
	addl $4, %esp
	call print_array

	call array_handler	#вызов функции обработки массива

	pushl $end_format	#передача параметров функции
	call printf		#вызов функции printf
	addl $4, %esp		#выравнивание стека
	call print_array	#вызов функции вывода массива

	pushl %esi		#передача параметра в функцию free
	call free		#освобождение памяти
	addl $4, %esp		#выравнивание стека
end:		
	ret			#выход из программы
#Главная функция