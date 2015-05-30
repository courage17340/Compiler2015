	.data
__s0:
	.byte 37
	.byte 99
	.byte 32
	.byte 45
	.byte 62
	.byte 32
	.byte 37
	.byte 99
	.byte 10
	.byte 0
	.byte 0
	.byte 0
__s1:
	.byte 37
	.byte 99
	.byte 32
	.byte 45
	.byte 62
	.byte 32
	.byte 37
	.byte 99
	.byte 10
	.byte 0
	.byte 0
	.byte 0
	.text
_hanoi:
	addu $sp, $sp, -156
	sw $ra, 20($sp)
	lw $t0, 172($sp)
	li $t1, 1
	sgt $t2, $t0, $t1
	sw $t2, 24($sp)
	lw $t0, 24($sp)
	bne $t0, 0, label1
	la $t0, 32($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	la $t0, 28($sp)
	lw $t1, 32($sp)
	sw $t1, 0($t0)
	la $t0, 36($sp)
	lb $t1, 160($sp)
	sw $t1, 0($t0)
	la $t0, 40($sp)
	lb $t1, 168($sp)
	sw $t1, 0($t0)
	la $t0, 44($sp)
	lw $t1, 28($sp)
	sw $t1, 0($t0)
	lw $t0, 44($sp)
	sw $t0, 4($sp)
	la $t0, 48($sp)
	lw $t1, 36($sp)
	sw $t1, 0($t0)
	lw $t0, 48($sp)
	sw $t0, 8($sp)
	la $t0, 52($sp)
	lw $t1, 40($sp)
	sw $t1, 0($t0)
	lw $t0, 52($sp)
	sw $t0, 12($sp)
	jal _printf
	j label2
label1:
	la $t0, 56($sp)
	lb $t1, 160($sp)
	sw $t1, 0($t0)
	la $t0, 60($sp)
	lb $t1, 168($sp)
	sw $t1, 0($t0)
	la $t0, 64($sp)
	lb $t1, 164($sp)
	sw $t1, 0($t0)
	lw $t0, 172($sp)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 72($sp)
	la $t0, 68($sp)
	lw $t1, 72($sp)
	sw $t1, 0($t0)
	la $t0, 76($sp)
	lw $t1, 56($sp)
	sw $t1, 0($t0)
	lw $t0, 76($sp)
	sw $t0, 4($sp)
	la $t0, 80($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
	lw $t0, 80($sp)
	sw $t0, 8($sp)
	la $t0, 84($sp)
	lw $t1, 64($sp)
	sw $t1, 0($t0)
	lw $t0, 84($sp)
	sw $t0, 12($sp)
	la $t0, 88($sp)
	lw $t1, 68($sp)
	sw $t1, 0($t0)
	lw $t0, 88($sp)
	sw $t0, 16($sp)
	jal _hanoi
	la $t0, 96($sp)
	la $t1, __s1
	sw $t1, 0($t0)
	la $t0, 92($sp)
	lw $t1, 96($sp)
	sw $t1, 0($t0)
	la $t0, 100($sp)
	lb $t1, 160($sp)
	sw $t1, 0($t0)
	la $t0, 104($sp)
	lb $t1, 168($sp)
	sw $t1, 0($t0)
	la $t0, 108($sp)
	lw $t1, 92($sp)
	sw $t1, 0($t0)
	lw $t0, 108($sp)
	sw $t0, 4($sp)
	la $t0, 112($sp)
	lw $t1, 100($sp)
	sw $t1, 0($t0)
	lw $t0, 112($sp)
	sw $t0, 8($sp)
	la $t0, 116($sp)
	lw $t1, 104($sp)
	sw $t1, 0($t0)
	lw $t0, 116($sp)
	sw $t0, 12($sp)
	jal _printf
	la $t0, 120($sp)
	lb $t1, 164($sp)
	sw $t1, 0($t0)
	la $t0, 124($sp)
	lb $t1, 160($sp)
	sw $t1, 0($t0)
	la $t0, 128($sp)
	lb $t1, 168($sp)
	sw $t1, 0($t0)
	lw $t0, 172($sp)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 136($sp)
	la $t0, 132($sp)
	lw $t1, 136($sp)
	sw $t1, 0($t0)
	la $t0, 140($sp)
	lw $t1, 120($sp)
	sw $t1, 0($t0)
	lw $t0, 140($sp)
	sw $t0, 4($sp)
	la $t0, 144($sp)
	lw $t1, 124($sp)
	sw $t1, 0($t0)
	lw $t0, 144($sp)
	sw $t0, 8($sp)
	la $t0, 148($sp)
	lw $t1, 128($sp)
	sw $t1, 0($t0)
	lw $t0, 148($sp)
	sw $t0, 12($sp)
	la $t0, 152($sp)
	lw $t1, 132($sp)
	sw $t1, 0($t0)
	lw $t0, 152($sp)
	sw $t0, 16($sp)
	jal _hanoi
label2:
__end__hanoi:
	lw $ra, 20($sp)
	addu $sp, $sp, 156
	j $ra
main:
	addu $sp, $sp, -100
	sw $ra, 20($sp)
	jal _getchar
	la $t0, 32($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 36($sp)
	lw $t1, 32($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 36($sp)
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, 40($sp)
	li $t0, 10
	lw $t1, 40($sp)
	mul $t2, $t0, $t1
	sw $t2, 44($sp)
	jal _getchar
	la $t0, 48($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 52($sp)
	lw $t1, 48($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 44($sp)
	lw $t1, 52($sp)
	addu $t2, $t0, $t1
	sw $t2, 56($sp)
	lw $t0, 56($sp)
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, 60($sp)
	la $t0, 28($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
	lw $t0, 28($sp)
	li $t1, 0
	sgt $t2, $t0, $t1
	sw $t2, 64($sp)
	lw $t0, 64($sp)
	bne $t0, 0, label3
	j label4
label3:
	la $t0, 68($sp)
	li $t1, 97
	sw $t1, 0($t0)
	la $t0, 72($sp)
	li $t1, 98
	sw $t1, 0($t0)
	la $t0, 76($sp)
	li $t1, 99
	sw $t1, 0($t0)
	la $t0, 80($sp)
	lw $t1, 28($sp)
	sw $t1, 0($t0)
	la $t0, 84($sp)
	lw $t1, 68($sp)
	sw $t1, 0($t0)
	lw $t0, 84($sp)
	sw $t0, 4($sp)
	la $t0, 88($sp)
	lw $t1, 72($sp)
	sw $t1, 0($t0)
	lw $t0, 88($sp)
	sw $t0, 8($sp)
	la $t0, 92($sp)
	lw $t1, 76($sp)
	sw $t1, 0($t0)
	lw $t0, 92($sp)
	sw $t0, 12($sp)
	la $t0, 96($sp)
	lw $t1, 80($sp)
	sw $t1, 0($t0)
	lw $t0, 96($sp)
	sw $t0, 16($sp)
	jal _hanoi
label4:
	li $v0, 0
	sw $v0, 100($sp)
	j __end__main
__end__main:
	lw $ra, 20($sp)
	addu $sp, $sp, 100
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
_printf_char:
	addu $a1, $a1, 4
	lb $a0, 0($a1)
	li $v0, 11
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
