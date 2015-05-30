	.data
__s0:
	.byte 37
	.byte 100
	.byte 32
	.byte 0
	.text
main:
	addu $sp, $sp, -36
	sw $ra, 12($sp)
	la $t0, 28($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	la $t0, 24($sp)
	lw $t1, 28($sp)
	sw $t1, 0($t0)
	la $t0, 32($sp)
	lw $t1, 20($sp)
	sw $t1, 0($t0)
	lw $t0, 24($sp)
	sw $t0, 4($sp)
	lw $t0, 32($sp)
	sw $t0, 8($sp)
	jal _printf
__end__main:
	lw $ra, 12($sp)
	addu $sp, $sp, 36
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
