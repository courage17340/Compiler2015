	.data
__1:	.space 4
__2:	.space 4
__s0:
	.byte 97
	.byte 98
	.byte 99
	.byte 100
	.byte 101
	.byte 102
	.byte 0
	.byte 0
__s1:
	.byte 97
	.byte 98
	.byte 99
	.byte 101
	.byte 100
	.byte 102
	.byte 0
	.byte 0
__s2:
	.byte 37
	.byte 100
	.byte 58
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 99
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.text
main:
	addu $sp, $sp, -96
	sw $ra, 20($sp)
	la $t0, 28($sp)
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 32($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	la $t0, __1
	lw $t1, 32($sp)
	sw $t1, 0($t0)
	la $t0, 36($sp)
	la $t1, __s1
	sw $t1, 0($t0)
	la $t0, __2
	lw $t1, 36($sp)
	sw $t1, 0($t0)
	j label2
label1:
	la $t0, 40($sp)
	lw $t1, 28($sp)
	sw $t1, 0($t0)
	lw $t0, 28($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 44($sp)
	la $t0, 28($sp)
	lw $t1, 44($sp)
	sw $t1, 0($t0)
label2:
	lw $t0, 28($sp)
	li $t1, 6
	slt $t2, $t0, $t1
	sw $t2, 48($sp)
	lw $t0, 48($sp)
	beq $t0, 0, label3
	lw $t0, 28($sp)
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 52($sp)
	lw $t0, __1
	lw $t1, 52($sp)
	addu $t1, $t0, $t1
	sw $t1, 56($sp)
	lw $t0, 28($sp)
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 60($sp)
	lw $t0, __2
	lw $t1, 60($sp)
	addu $t1, $t0, $t1
	sw $t1, 64($sp)
	lw $t0, 56($sp)
	lb $t0, 0($t0)
	lw $t1, 64($sp)
	lb $t1, 0($t1)
	sne $t2, $t0, $t1
	sw $t2, 68($sp)
	lw $t0, 68($sp)
	bne $t0, 0, label4
	j label5
label4:
	la $t0, 72($sp)
	la $t1, __s2
	sw $t1, 0($t0)
	lw $t0, 28($sp)
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 76($sp)
	lw $t0, __1
	lw $t1, 76($sp)
	addu $t1, $t0, $t1
	sw $t1, 80($sp)
	lw $t0, 28($sp)
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 84($sp)
	lw $t0, __2
	lw $t1, 84($sp)
	addu $t1, $t0, $t1
	sw $t1, 88($sp)
	lw $t0, 72($sp)
	sw $t0, 4($sp)
	lw $t0, 28($sp)
	sw $t0, 8($sp)
	lw $t0, 80($sp)
	lb $t0, 0($t0)
	sb $t0, 12($sp)
	lw $t0, 88($sp)
	lb $t0, 0($t0)
	sb $t0, 16($sp)
	jal _printf
	la $t0, 92($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	j label3
label5:
	j label1
label3:
__end__main:
	lw $ra, 20($sp)
	addu $sp, $sp, 96
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
	addu $a2, $a2, 2
	lw $a3, 0($a1)
	bgt $a3, 999, _printf_width_end
	li $v0, 1
	li $a0, 0
	syscall
	bgt $a3, 99, _printf_width_end
	li $v0, 1
	li $a0, 0
	syscall
	bgt $a3, 9, _printf_width_end
	li $v0, 1
	li $a0, 0
	syscall
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
