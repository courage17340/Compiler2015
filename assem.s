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
	addu $sp, $sp, -16
	sw $ra, 0($sp)
	lb $t0, 20($sp)
	li $t1, 48
	sge $t2, $t0, $t1
	sw $t2, 4($sp)
	lw $t0, 4($sp)
	beq $t0, 0, label1
	lb $t0, 20($sp)
	li $t1, 57
	sle $t2, $t0, $t1
	sw $t2, 12($sp)
	la $t0, 8($sp)
	lw $t1, 12($sp)
	sne $t1, $t1, 0
	sw $t1, 0($t0)
	j label2
label1:
	la $t0, 8($sp)
	li $t1, 0
	sw $t1, 0($t0)
label2:
	lw $v0, 8($sp)
	sw $v0, 16($sp)
	j __end__is_digit
__end__is_digit:
	lw $ra, 0($sp)
	addu $sp, $sp, 16
	j $ra
_get_d:
	addu $sp, $sp, -92
	sw $ra, 8($sp)
	jal _getchar
	la $t0, 24($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 28($sp)
	lw $t1, 24($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 28($sp)
	sb $t1, 0($t0)
	la $t0, 32($sp)
	li $t1, 0
	sw $t1, 0($t0)
label3:
	la $t0, 36($sp)
	lb $t1, 20($sp)
	sw $t1, 0($t0)
	lw $t0, 36($sp)
	sw $t0, 4($sp)
	jal _is_digit
	la $t0, 40($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 44($sp)
	lw $t1, 40($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 44($sp)
	seq $t0, $t0, 0
	sw $t0, 48($sp)
	lw $t0, 48($sp)
	beq $t0, 0, label4
	jal _getchar
	la $t0, 52($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 56($sp)
	lw $t1, 52($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 56($sp)
	sb $t1, 0($t0)
	j label3
label4:
label5:
	la $t0, 60($sp)
	lb $t1, 20($sp)
	sw $t1, 0($t0)
	lw $t0, 60($sp)
	sw $t0, 4($sp)
	jal _is_digit
	la $t0, 64($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 68($sp)
	lw $t1, 64($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 68($sp)
	beq $t0, 0, label6
	lw $t0, 32($sp)
	li $t1, 10
	mul $t2, $t0, $t1
	sw $t2, 72($sp)
	lw $t0, 72($sp)
	lb $t1, 20($sp)
	addu $t2, $t0, $t1
	sw $t2, 76($sp)
	lw $t0, 76($sp)
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, 80($sp)
	la $t0, 32($sp)
	lw $t1, 80($sp)
	sw $t1, 0($t0)
	jal _getchar
	la $t0, 84($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 88($sp)
	lw $t1, 84($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 20($sp)
	lw $t1, 88($sp)
	sb $t1, 0($t0)
	j label5
label6:
	lw $v0, 32($sp)
	sw $v0, 92($sp)
	j __end__get_d
__end__get_d:
	lw $ra, 8($sp)
	addu $sp, $sp, 92
	j $ra
main:
	addu $sp, $sp, -172
	sw $ra, 16($sp)
	jal _getchar
	la $t0, 32($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 36($sp)
	lw $t1, 32($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 28($sp)
	lw $t1, 36($sp)
	sb $t1, 0($t0)
	jal _get_d
	la $t0, 44($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 48($sp)
	lw $t1, 44($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 40($sp)
	lw $t1, 48($sp)
	sw $t1, 0($t0)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 52($sp)
	lw $t0, 52($sp)
	lb $t1, 28($sp)
	sb $t1, 0($t0)
	la $t0, 60($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	la $t0, 56($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 68($sp)
	la $t0, 64($sp)
	lw $t1, 68($sp)
	lb $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 76($sp)
	la $t0, 72($sp)
	lw $t1, 76($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 56($sp)
	sw $t0, 4($sp)
	lw $t0, 64($sp)
	sw $t0, 8($sp)
	lw $t0, 72($sp)
	sw $t0, 12($sp)
	jal _printf
	la $t0, __2
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 80($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 84($sp)
	lw $t0, 80($sp)
	lw $t1, 84($sp)
	lb $t1, 0($t1)
	sb $t1, 0($t0)
	la $t0, 92($sp)
	la $t1, __s1
	sw $t1, 0($t0)
	la $t0, 88($sp)
	lw $t1, 92($sp)
	sw $t1, 0($t0)
	la $t0, __2
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 100($sp)
	la $t0, 96($sp)
	lw $t1, 100($sp)
	lb $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, __2
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, 108($sp)
	la $t0, 104($sp)
	lw $t1, 108($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 88($sp)
	sw $t0, 4($sp)
	lw $t0, 96($sp)
	sw $t0, 8($sp)
	lw $t0, 104($sp)
	sw $t0, 12($sp)
	jal _printf
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 112($sp)
	lw $t0, 112($sp)
	lw $t1, 40($sp)
	sw $t1, 0($t0)
	la $t0, 120($sp)
	la $t1, __s2
	sw $t1, 0($t0)
	la $t0, 116($sp)
	lw $t1, 120($sp)
	sw $t1, 0($t0)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 128($sp)
	la $t0, 124($sp)
	lw $t1, 128($sp)
	lb $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 136($sp)
	la $t0, 132($sp)
	lw $t1, 136($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 116($sp)
	sw $t0, 4($sp)
	lw $t0, 124($sp)
	sw $t0, 8($sp)
	lw $t0, 132($sp)
	sw $t0, 12($sp)
	jal _printf
	la $t0, __2
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, 140($sp)
	la $t0, __1
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 144($sp)
	lw $t0, 140($sp)
	lw $t1, 144($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 152($sp)
	la $t1, __s3
	sw $t1, 0($t0)
	la $t0, 148($sp)
	lw $t1, 152($sp)
	sw $t1, 0($t0)
	la $t0, __2
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 160($sp)
	la $t0, 156($sp)
	lw $t1, 160($sp)
	lb $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, __2
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, 168($sp)
	la $t0, 164($sp)
	lw $t1, 168($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 148($sp)
	sw $t0, 4($sp)
	lw $t0, 156($sp)
	sw $t0, 8($sp)
	lw $t0, 164($sp)
	sw $t0, 12($sp)
	jal _printf
	li $v0, 0
	sw $v0, 172($sp)
	j __end__main
__end__main:
	lw $ra, 16($sp)
	addu $sp, $sp, 172
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
