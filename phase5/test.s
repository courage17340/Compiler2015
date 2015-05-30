	.data
__s0:
	.byte 109
	.byte 111
	.byte 118
	.byte 101
	.byte 32
	.byte 37
	.byte 99
	.byte 32
	.byte 45
	.byte 45
	.byte 62
	.byte 32
	.byte 37
	.byte 99
	.byte 10
	.byte 0
__s1:
	.byte 109
	.byte 111
	.byte 118
	.byte 101
	.byte 32
	.byte 37
	.byte 99
	.byte 32
	.byte 45
	.byte 45
	.byte 62
	.byte 32
	.byte 37
	.byte 99
	.byte 10
	.byte 0
__s2:
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.text
_cd:
	addu $sp, $sp, -60
	sw $ra, 24($sp)
	lw $t0, 64($sp)
	beq $t0, 1, label1
	lw $t0, 64($sp)
	subu $t2, $t0, 1
	sw $t2, 28($sp)
	lw $t0, 28($sp)
	sw $t0, 4($sp)
	lb $t0, 68($sp)
	sb $t0, 8($sp)
	lb $t0, 76($sp)
	sb $t0, 12($sp)
	lb $t0, 72($sp)
	sb $t0, 16($sp)
	lw $t0, 80($sp)
	sw $t0, 20($sp)
	jal _cd
	la $t1, 0($sp)
	sw $t1, 32($sp)
	lw $t1, 32($sp)
	lw $t1, 0($t1)
	sw $t1, 36($sp)
	lw $t1, 36($sp)
	sw $t1, 80($sp)
	la $t1, __s0
	sw $t1, 40($sp)
	lw $t0, 40($sp)
	sw $t0, 4($sp)
	lb $t0, 68($sp)
	sb $t0, 8($sp)
	lb $t0, 76($sp)
	sb $t0, 12($sp)
	jal _printf
	lw $t0, 64($sp)
	subu $t2, $t0, 1
	sw $t2, 44($sp)
	lw $t0, 44($sp)
	sw $t0, 4($sp)
	lb $t0, 72($sp)
	sb $t0, 8($sp)
	lb $t0, 68($sp)
	sb $t0, 12($sp)
	lb $t0, 76($sp)
	sb $t0, 16($sp)
	lw $t0, 80($sp)
	sw $t0, 20($sp)
	jal _cd
	la $t1, 0($sp)
	sw $t1, 48($sp)
	lw $t1, 48($sp)
	lw $t1, 0($t1)
	sw $t1, 52($sp)
	lw $t1, 52($sp)
	sw $t1, 80($sp)
	lw $t0, 80($sp)
	addu $t0, $t0, 1
	sw $t0, 80($sp)
	j label2
label1:
	la $t1, __s1
	sw $t1, 56($sp)
	lw $t0, 56($sp)
	sw $t0, 4($sp)
	lb $t0, 68($sp)
	sb $t0, 8($sp)
	lb $t0, 76($sp)
	sb $t0, 12($sp)
	jal _printf
	lw $t0, 80($sp)
	addu $t0, $t0, 1
	sw $t0, 80($sp)
label2:
	lw $v0, 80($sp)
	sw $v0, 60($sp)
	j __end__cd
__end__cd:
	lw $ra, 24($sp)
	addu $sp, $sp, 60
	j $ra
main:
	addu $sp, $sp, -112
	sw $ra, 24($sp)
	li $t1, 65
	sb $t1, 48($sp)
	li $t1, 66
	sb $t1, 52($sp)
	li $t1, 67
	sb $t1, 56($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 64($sp)
	lw $t1, 64($sp)
	lw $t1, 0($t1)
	sw $t1, 68($sp)
	lw $t0, 68($sp)
	subu $t2, $t0, 48
	sw $t2, 72($sp)
	li $t0, 10
	lw $t1, 72($sp)
	mul $t2, $t0, $t1
	sw $t2, 76($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 80($sp)
	lw $t1, 80($sp)
	lw $t1, 0($t1)
	sw $t1, 84($sp)
	lw $t0, 76($sp)
	lw $t1, 84($sp)
	addu $t2, $t0, $t1
	sw $t2, 88($sp)
	lw $t0, 88($sp)
	subu $t2, $t0, 48
	sw $t2, 92($sp)
	lw $t1, 92($sp)
	sw $t1, 60($sp)
	lw $t0, 60($sp)
	sw $t0, 4($sp)
	lb $t0, 48($sp)
	sb $t0, 8($sp)
	lb $t0, 52($sp)
	sb $t0, 12($sp)
	lb $t0, 56($sp)
	sb $t0, 16($sp)
	li $t0, 0
	sw $t0, 20($sp)
	jal _cd
	la $t1, 0($sp)
	sw $t1, 100($sp)
	lw $t1, 100($sp)
	lw $t1, 0($t1)
	sw $t1, 104($sp)
	lw $t1, 104($sp)
	sw $t1, 96($sp)
	la $t1, __s2
	sw $t1, 108($sp)
	lw $t0, 108($sp)
	sw $t0, 4($sp)
	lw $t0, 96($sp)
	sw $t0, 8($sp)
	jal _printf
	li $v0, 0
	sw $v0, 112($sp)
	j __end__main
__end__main:
	lw $ra, 24($sp)
	addu $sp, $sp, 112
	li $v0, 10
	syscall
_printf:
	la $a1, 4($sp)
	lw $a2, 4($sp)
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
	beq $a0, 'c', _printf_char
	beq $a0, 'd', _printf_int
_printf_char:
	addu $a1, $a1, 4
	lb $a0, 0($a1)
	li $v0, 11
	syscall
	j _printf_loop
_printf_int:
	addu $a1, $a1, 4
	lw $a0, 0($a1)
	li $v0, 1
	syscall
	j _printf_loop
_printf_end:
	j $ra
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
