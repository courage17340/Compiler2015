	.data
__1:	.space 4
__2:	.space 8
__s0:
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.byte 0
__s1:
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.byte 0
__s2:
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.byte 0
__s3:
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.byte 0
	.text
_is_digit:
	addu $sp, $sp, -12
	sw $ra, 0($sp)
	lb $t0, 16($sp)
	blt $t0, 48, label1
	lb $t0, 16($sp)
	sle $t2, $t0, 57
	sw $t2, 8($sp)
	lw $t1, 8($sp)
	sne $t1, $t1, 0
	sw $t1, 4($sp)
	j label2
label1:
	li $t1, 0
	sw $t1, 4($sp)
label2:
	lw $v0, 4($sp)
	sw $v0, 12($sp)
	j __end__is_digit
__end__is_digit:
	lw $ra, 0($sp)
	addu $sp, $sp, 12
	j $ra
_get_d:
	addu $sp, $sp, -84
	sw $ra, 8($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 24($sp)
	lw $t1, 24($sp)
	lw $t1, 0($t1)
	sw $t1, 28($sp)
	lw $t1, 28($sp)
	sb $t1, 20($sp)
	li $t1, 0
	sw $t1, 32($sp)
label3:
	lb $t0, 20($sp)
	sb $t0, 4($sp)
	jal _is_digit
	la $t1, 0($sp)
	sw $t1, 36($sp)
	lw $t1, 36($sp)
	lw $t1, 0($t1)
	sw $t1, 40($sp)
	lw $t0, 40($sp)
	seq $t0, $t0, 0
	sw $t0, 44($sp)
	lw $t0, 44($sp)
	beq $t0, 0, label4
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 48($sp)
	lw $t1, 48($sp)
	lw $t1, 0($t1)
	sw $t1, 52($sp)
	lw $t1, 52($sp)
	sb $t1, 20($sp)
	j label3
label4:
label5:
	lb $t0, 20($sp)
	sb $t0, 4($sp)
	jal _is_digit
	la $t1, 0($sp)
	sw $t1, 56($sp)
	lw $t1, 56($sp)
	lw $t1, 0($t1)
	sw $t1, 60($sp)
	lw $t0, 60($sp)
	beq $t0, 0, label6
	lw $t0, 32($sp)
	mul $t2, $t0, 10
	sw $t2, 64($sp)
	lw $t0, 64($sp)
	lb $t1, 20($sp)
	addu $t2, $t0, $t1
	sw $t2, 68($sp)
	lw $t0, 68($sp)
	subu $t2, $t0, 48
	sw $t2, 72($sp)
	lw $t1, 72($sp)
	sw $t1, 32($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 76($sp)
	lw $t1, 76($sp)
	lw $t1, 0($t1)
	sw $t1, 80($sp)
	lw $t1, 80($sp)
	sb $t1, 20($sp)
	j label5
label6:
	lw $v0, 32($sp)
	sw $v0, 84($sp)
	j __end__get_d
__end__get_d:
	lw $ra, 8($sp)
	addu $sp, $sp, 84
	j $ra
main:
	addu $sp, $sp, -124
	sw $ra, 16($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 32($sp)
	lw $t1, 32($sp)
	lw $t1, 0($t1)
	sw $t1, 36($sp)
	lw $t1, 36($sp)
	sb $t1, 28($sp)
	jal _get_d
	la $t1, 0($sp)
	sw $t1, 44($sp)
	lw $t1, 44($sp)
	lw $t1, 0($t1)
	sw $t1, 48($sp)
	lw $t1, 48($sp)
	sw $t1, 40($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 52($sp)
	lw $t0, 52($sp)
	lb $t1, 28($sp)
	sb $t1, 0($t0)
	la $t1, __s0
	sw $t1, 56($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 60($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 64($sp)
	lw $t0, 56($sp)
	sw $t0, 4($sp)
	lw $t0, 60($sp)
	lb $t0, 0($t0)
	sb $t0, 8($sp)
	lw $t0, 64($sp)
	lw $t0, 0($t0)
	sw $t0, 12($sp)
	jal _printf
	la $t0, __2
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 68($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 72($sp)
	lw $t0, 68($sp)
	lw $t1, 72($sp)
	lb $t1, 0($t1)
	sb $t1, 0($t0)
	la $t1, __s1
	sw $t1, 76($sp)
	la $t0, __2
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 80($sp)
	la $t0, __2
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, 84($sp)
	lw $t0, 76($sp)
	sw $t0, 4($sp)
	lw $t0, 80($sp)
	lb $t0, 0($t0)
	sb $t0, 8($sp)
	lw $t0, 84($sp)
	lw $t0, 0($t0)
	sw $t0, 12($sp)
	jal _printf
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 88($sp)
	lw $t0, 88($sp)
	lw $t1, 40($sp)
	sw $t1, 0($t0)
	la $t1, __s2
	sw $t1, 92($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 96($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 100($sp)
	lw $t0, 92($sp)
	sw $t0, 4($sp)
	lw $t0, 96($sp)
	lb $t0, 0($t0)
	sb $t0, 8($sp)
	lw $t0, 100($sp)
	lw $t0, 0($t0)
	sw $t0, 12($sp)
	jal _printf
	la $t0, __2
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, 104($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 108($sp)
	lw $t0, 104($sp)
	lw $t1, 108($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t1, __s3
	sw $t1, 112($sp)
	la $t0, __2
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 116($sp)
	la $t0, __2
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, 120($sp)
	lw $t0, 112($sp)
	sw $t0, 4($sp)
	lw $t0, 116($sp)
	lb $t0, 0($t0)
	sb $t0, 8($sp)
	lw $t0, 120($sp)
	lw $t0, 0($t0)
	sw $t0, 12($sp)
	jal _printf
	li $v0, 0
	sw $v0, 124($sp)
	j __end__main
__end__main:
	lw $ra, 16($sp)
	addu $sp, $sp, 124
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
