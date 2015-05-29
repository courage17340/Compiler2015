	.data
__s0:
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.text
main:
	addu $sp, $sp, -36
	sw $ra, 12($sp)
	la $t0, 16($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 16($sp)
	sw $t1, 0($t0)
	lw $t0, 20($sp)
	sw $t0, 4($sp)
	la $t0, 24($sp)
	li $t1, 13
	sw $t1, 0($t0)
	lw $t0, 24($sp)
	sw $t0, 8($sp)
	jal _printf
	la $t0, 28($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 32($sp)
	lw $t1, 28($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
__end__main:
	lw $ra, 12($sp)
	addu $sp, $sp, 36
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
