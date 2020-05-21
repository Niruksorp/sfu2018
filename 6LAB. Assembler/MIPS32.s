	.data
start_format: .asciiz "Input array:\n\n" 				#Функции для printf
end_format: .asciiz "After task:\n\n"	
enter_line_format: .asciiz "Enter line " 
scanf_format:	.asciiz "%d"			
enter_size_format:	.asciiz "Enter array size:\n"	
printf_format:	.asciiz "Enter array elem:\n"		
init_end_format: .asciiz "Array initialized\n"		
check_all_bytes: .asciiz "Bytes count: "			
check_bytes_line: .asciiz "Bytes count per string: "
check_elem_count: .asciiz "Elements count: "		
check_line_count: .asciiz "Elements count per string: " 
next_elem_format: .asciiz "  "	
next_line_format: .asciiz "\n"	
enter_number_format: .asciiz "Enter line number\n"
error_format_for_zero_size: .asciiz "Error. Invalid value\n"
ELEM_SIZE: .word 4										#данные и резервируемая память
LINE_SIZE_BYTES: .word 0	
ARRAY_SIZE_BYTES: .word 0	
TOTAL_COUNT: .word 0		
ARRAY_SIZE: .word 0			
ARRAY_ELEM: .word 0			
OFFSET: .word 0				


	.text
init_array:												#Функция инициализации массива
	li $v0, 4											
	la $a0, enter_size_format							
	syscall												
	
	li $v0, 5											#Чтение размера
	syscall
	blt $v0, 1, exit_prog 

	sw $v0, ARRAY_SIZE 									
	lw $t0, ELEM_SIZE
	lw $t1, ARRAY_SIZE
	mul $t2, $t0, $t1
	sw $t2, LINE_SIZE_BYTES
	mul $t3, $t2, $t1
	sw $t3, ARRAY_SIZE_BYTES
	lw $t0, ARRAY_SIZE
	lw $t1, ARRAY_SIZE
	mul $t2, $t0, $t1
	sw $t2, TOTAL_COUNT
	
	li $v0, 4											#Вывод р-та
	la $a0, check_all_bytes
	syscall
	li $v0, 1
	lw $a0, ARRAY_SIZE_BYTES
	syscall
	li $v0, 4
	la $a0, next_line_format
	syscall
	
	li $v0, 4
	la $a0, check_bytes_line
	syscall
	li $v0, 1
	lw $a0, LINE_SIZE_BYTES
	syscall
	li $v0, 4
	la $a0, next_line_format
	syscall
	
	li $v0, 4
	la $a0, check_elem_count
	syscall
	li $v0, 1
	lw $a0, TOTAL_COUNT
	syscall
	li $v0, 4
	la $a0, next_line_format
	syscall
	
	li $v0, 4
	la $a0, check_line_count
	syscall
	li $v0, 1
	lw $a0, ARRAY_SIZE
	syscall
	li $v0, 4
	la $a0, next_line_format
	syscall
	
	li $v0, 9											#9 - работа с памятью
	lw $a0, ARRAY_SIZE_BYTES							
	syscall												
	move $s7, $v0										#Сохраняем массив в s7
	
	li $t0, 0 											#t0 - counter
	lw $t1, ARRAY_SIZE									#сохранение размера массива в t1
	beq $t0, $t1, end_init								#comparing size with 0, if eq, goto end_format
	li $t0, 0
	li $t7, 0											#Сохранить 0 в s7
	lw $t2, ARRAY_SIZE									#разммер массива в t2
	move $s6, $s7										#сохраняем указатель на массив
enter_line:
	li $t1, 0											#Элемент счетчик
	beq $t0, $t2, end_init								#Сравнение счетчика
	
	addi $t3, $t0, 1									#Чтениие входного формата
	li $v0, 4			
	la $a0, enter_line_format
	syscall
	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 4
	la $a0, next_line_format
	syscall
enter_element:
	li $v0, 4											
	la $a0, printf_format
	syscall
	
	li $v0, 5											#Чтение эл-та
	syscall
	
	add $s7, $s7, $t7									#Смещение к указателю
	sw $v0, 0($s7)										#Сохранение эл-та
	lw $t7, ELEM_SIZE

		
	addi $t1, $t1, 1									#Увеличение счетчика
	bne $t1, $t2, enter_element							#Сопоставление счетчика и кол-ва строк
	addi $t0, $t0, 1
	j enter_line
	
	
end_init:
	move $s7, $s6										
	li $v0, 4											#Вывод конечного формата
	la $a0, init_end_format
	syscall
	jr $ra												#Возврат из функции
	
	
	
print_array:
	li $t0, 0											#t0 - счетчик
	lw $t1, ARRAY_SIZE   								
	li $t7, 0											
	move $s6, $s7										#Сохранение указателя на массив 
rep:
	add $s7, $s7, $t7									#Добавляем смещение к  array_handler
	lw $t7, ELEM_SIZE									#loading offset
	li $v0, 1											
	lw $a0, 0($s7)
	syscall
	
	li $v0, 4											#печ=чаит некст элемента
	la $a0, next_elem_format
	syscall
	addi $t0, $t0, 1
	beq $t0, $t1, next_line								
cont:
	lw $t4, TOTAL_COUNT									
	beq $t0, $t4, end_print								#Если все напечатаны
	j rep
next_line:
	lw $t4, ARRAY_SIZE									#печать в формате следующей строки
	add $t1, $t1, $t4
	li $v0, 4
	la $a0, next_line_format
	syscall
	j cont
	
end_print:
	move $s7, $s6										#Восстановление указателя на массив
	jr $ra												#Выход из функции
	

array_handler:
	
	li $v0, 4
	la $a0, enter_number_format
	syscall
	
	li $v0, 5
	syscall
	lw $t0, ARRAY_SIZE
	add $t0,$t0, 1
	blt $v0, 1, end_handle 
	bge $v0, $t0, end_handle 

	move $s6, $s7
	
	move $t0, $v0
	li $t5, 1
	sub $t0, $t0, $t5
	lw $t1, LINE_SIZE_BYTES
	mul $t1, $t0, $t1
	add $s6, $s6, $t1
	
	move $s5, $s6
	
	lw $t2, ELEM_SIZE
	mul $t2, $t2, $t0
	add $s5, $s5, $t2
	lw $t9, 0($s5)
	
	move $s5, $s6
	li $t0, 0
	lw $t1, ARRAY_SIZE
	lw $t2, ELEM_SIZE
adding:
	beq $t0, $t1, end_handle
	mul $t3, $t2, $t0
	add $s5, $s5, $t3
	lw $t8, 0($s5)
	add $t8, $t8, $t9
	sw $t8, 0($s5)
	addi $t0, $t0, 1
	move $s5, $s6
	j adding

end_handle:
	jr $ra

exit_prog:
	#li $v0, 4											
	#la $a0, error_format_for_zero_size
	#syscall
	li $v0, 10											#Выход из программы
	syscall

	.globl main
main:
	jal init_array										#Вызываем функцию для инициализации массива
	li $v0, 4
	la $a0, start_format								#Стартовый формат 
	syscall
	jal print_array										#Вызов печати массива
	
	jal array_handler									#Вызов редактирующей ф-ции
	
	li $v0, 4
	la $a0, end_format									#Конечный формат
	syscall
	jal print_array										#Вызов печати для результата
	li $v0, 10											#Выход из программы
	syscall
