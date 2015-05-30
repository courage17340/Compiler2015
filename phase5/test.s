	.data
__s0:
	.byte 37
	.byte 46
	.byte 51
	.byte 100
	.byte 32
	.byte 58
	.byte 32
	.byte 37
	.byte 115
	.byte 0
	.byte 0
	.byte 0
	.text
_getline1:
	addu $sp, $sp, -72
	sw $ra, 4($sp)
	jal _getchar
	la $t0, 16($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 16($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 12($sp)
	lw $t1, 20($sp)
	sw $t1, 0($t0)
label1:
	lw $t0, 12($sp)
	li $t1, 10
	sne $t2, $t0, $t1
	sw $t2, 24($sp)
	lw $t0, 24($sp)
	beq $t0, 0, label2
	la $t0, 28($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 72($sp)
	lw $t1, 28($sp)
	addu $t1, $t0, $t1
	sw $t1, 32($sp)
	lw $t0, 32($sp)
	lw $t1, 12($sp)
	sb $t1, 0($t0)
	lw $t0, 72($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 36($sp)
	la $t0, 72($sp)
	lw $t1, 36($sp)
	sw $t1, 0($t0)
	jal _getchar
	la $t0, 40($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 44($sp)
	lw $t1, 40($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 12($sp)
	lw $t1, 44($sp)
	sw $t1, 0($t0)
	j label1
label2:
	lw $t0, 12($sp)
	li $t1, 10
	seq $t2, $t0, $t1
	sw $t2, 48($sp)
	lw $t0, 48($sp)
	bne $t0, 0, label3
	j label4
label3:
	la $t0, 52($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 72($sp)
	lw $t1, 52($sp)
	addu $t1, $t0, $t1
	sw $t1, 56($sp)
	lw $t0, 56($sp)
	li $t1, 10
	sb $t1, 0($t0)
	lw $t0, 72($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 60($sp)
	la $t0, 72($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
label4:
	la $t0, 64($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 72($sp)
	lw $t1, 64($sp)
	addu $t1, $t0, $t1
	sw $t1, 68($sp)
	lw $t0, 68($sp)
	li $t1, 0
	sb $t1, 0($t0)
__end__getline1:
	lw $ra, 4($sp)
	addu $sp, $sp, 72
	j $ra
_isdecdigit:
	addu $sp, $sp, -16
	sw $ra, 0($sp)
	lb $t0, 20($sp)
	li $t1, 48
	sge $t2, $t0, $t1
	sw $t2, 4($sp)
	lw $t0, 4($sp)
	beq $t0, 0, label5
	lb $t0, 20($sp)
	li $t1, 57
	sle $t2, $t0, $t1
	sw $t2, 12($sp)
	la $t0, 8($sp)
	lw $t1, 12($sp)
	sne $t1, $t1, 0
	sw $t1, 0($t0)
	j label6
label5:
	la $t0, 8($sp)
	li $t1, 0
	sw $t1, 0($t0)
label6:
	lw $v0, 8($sp)
	sw $v0, 16($sp)
	j __end__isdecdigit
__end__isdecdigit:
	lw $ra, 0($sp)
	addu $sp, $sp, 16
	j $ra
_getint:
	addu $sp, $sp, -96
	sw $ra, 8($sp)
label7:
	jal _getchar
	la $t0, 32($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 36($sp)
	lw $t1, 32($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 36($sp)
	sb $t1, 0($t0)
	la $t0, 28($sp)
	lb $t1, 20($sp)
	sw $t1, 0($t0)
	la $t0, 40($sp)
	lw $t1, 28($sp)
	sw $t1, 0($t0)
	lw $t0, 40($sp)
	sw $t0, 4($sp)
	jal _isdecdigit
	la $t0, 44($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 48($sp)
	lw $t1, 44($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 48($sp)
	seq $t0, $t0, 0
	sw $t0, 52($sp)
	lw $t0, 52($sp)
	beq $t0, 0, label8
	j label7
	j label7
label8:
	lb $t0, 20($sp)
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, 56($sp)
	la $t0, 24($sp)
	lw $t1, 56($sp)
	sw $t1, 0($t0)
label9:
	jal _getchar
	la $t0, 64($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 68($sp)
	lw $t1, 64($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 68($sp)
	sb $t1, 0($t0)
	la $t0, 60($sp)
	lb $t1, 20($sp)
	sw $t1, 0($t0)
	la $t0, 72($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
	lw $t0, 72($sp)
	sw $t0, 4($sp)
	jal _isdecdigit
	la $t0, 76($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 80($sp)
	lw $t1, 76($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 80($sp)
	beq $t0, 0, label10
	lw $t0, 24($sp)
	li $t1, 10
	mul $t2, $t0, $t1
	sw $t2, 84($sp)
	lw $t0, 84($sp)
	lb $t1, 20($sp)
	addu $t2, $t0, $t1
	sw $t2, 88($sp)
	lw $t0, 88($sp)
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, 92($sp)
	la $t0, 24($sp)
	lw $t1, 92($sp)
	sw $t1, 0($t0)
	j label9
label10:
	lw $v0, 24($sp)
	sw $v0, 96($sp)
	j __end__getint
__end__getint:
	lw $ra, 8($sp)
	addu $sp, $sp, 96
	j $ra
main:
	addu $sp, $sp, -116
	sw $ra, 16($sp)
	la $t0, 36($sp)
	li $t1, 0
	sw $t1, 0($t0)
	jal _getint
	la $t0, 40($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 44($sp)
	lw $t1, 40($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 32($sp)
	lw $t1, 44($sp)
	sw $t1, 0($t0)
label11:
	lw $t0, 36($sp)
	lw $t1, 32($sp)
	slt $t2, $t0, $t1
	sw $t2, 48($sp)
	lw $t0, 48($sp)
	beq $t0, 0, label12
	li $t0, 1
	li $t1, 505
	mul $t2, $t0, $t1
	sw $t2, 60($sp)
	la $t0, 56($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
	la $t0, 64($sp)
	lw $t1, 56($sp)
	sw $t1, 0($t0)
	lw $t0, 64($sp)
	sw $t0, 4($sp)
	jal _malloc
	la $t0, 68($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 72($sp)
	lw $t1, 68($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 52($sp)
	lw $t1, 72($sp)
	sw $t1, 0($t0)
	la $t0, 76($sp)
	lw $t1, 52($sp)
	sw $t1, 0($t0)
	la $t0, 80($sp)
	lw $t1, 76($sp)
	sw $t1, 0($t0)
	lw $t0, 80($sp)
	sw $t0, 0($sp)
	jal _getline1
	la $t0, 88($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	la $t0, 84($sp)
	lw $t1, 88($sp)
	sw $t1, 0($t0)
	lw $t0, 36($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 96($sp)
	la $t0, 36($sp)
	lw $t1, 96($sp)
	sw $t1, 0($t0)
	la $t0, 92($sp)
	lw $t1, 36($sp)
	sw $t1, 0($t0)
	la $t0, 100($sp)
	lw $t1, 52($sp)
	sw $t1, 0($t0)
	la $t0, 104($sp)
	lw $t1, 84($sp)
	sw $t1, 0($t0)
	lw $t0, 104($sp)
	sw $t0, 4($sp)
	la $t0, 108($sp)
	lw $t1, 92($sp)
	sw $t1, 0($t0)
	lw $t0, 108($sp)
	sw $t0, 8($sp)
	la $t0, 112($sp)
	lw $t1, 100($sp)
	sw $t1, 0($t0)
	lw $t0, 112($sp)
	sw $t0, 12($sp)
	jal _printf
	j label11
label12:
	li $v0, 0
	sw $v0, 116($sp)
	j __end__main
__end__main:
	lw $ra, 16($sp)
	addu $sp, $sp, 116
	li $v0, 10
	syscall
_printf:
	la $a1, 4($sp)
	lw $a2, 4($sp)
	j _printf_loop
_printf_end:
	j $ra
_printf_loop:
	lb $a0, 0($a2)
	beq $a0, 0, _printf_end
	addu $a2, $a2, 1
	beq $a0, '%', _printf_fmt
	li $v0, 11
	syscall
	j _printf_loop
_printf_fmt:
	lb $a0, 0($a2)
	addu $a2, $a2, 1
	beq $a0, 'd', _printf_int
	beq $a0, 's', _printf_str
	beq $a0, 'c', _printf_char
	beq $a0, '0', _printf_width
	beq $a0, '.', _printf_width
_printf_int:
	addu $a1, $a1, 4
	lw $a0, 0($a1)
	li $v0, 1
	syscall
	j _printf_loop
_printf_str:
	addu $a1, $a1, 4
	lw $a0, 0($a1)
	li $v0, 4
	syscall
	j _printf_loop
_printf_char:
	addu $a1, $a1, 4
	lb $a0, 0($a1)
	li $v0, 11
	syscall
	j _printf_loop
_printf_width:
	addu $a1, $a1, 4
	lb $t0, 0($a2)
	subu $t0, $t0, '0'
	addu $a2, $a2, 2
	lw $t1, 0($a1)
	li $t2, 1
	blt $t0, 2, _printf_width_end
_label_width_1:
	subu $t0, $t0, 1
	mul $t2, $t2, 10
	bgt $t0, 1, _label_width_1
	li $a0, 0
	li $v0, 1
_label_width_2:
	bge $t1, $t2, _printf_width_end
	syscall
	div $t2, $t2, 10
	j _label_width_2
_printf_width_end:	lw $a0, 0($a1)
	li $v0, 1
	syscall
	j _printf_loop
_malloc:
	li $v0, 9
	lw $a0, 4($sp)
	syscall
	sw $v0, 0($sp)
	j $ra
_getchar:
	li $v0, 12
	syscall
	sw $v0, 0($sp)
	j $ra
