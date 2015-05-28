	.data
__1:	.space 4
__3:	.space 4
__4:	.space 4
__5:	.space 4
	.text
main:
	addu $sp, $sp, -12
	sw $ra, 8($sp)
	li $t0, 3
	negu $t0, $t0
	sw $t0, __3
	lw $t0, __3
	li $t1, 2
	rem $t2, $t0, $t1
	sw $t2, __4
	lw $t0, __4
	sw $t0, 4($sp)
	jal _printf
	la $t0, __5
	la $t1, 0($sp)
	sw $t1, 0($t0)
__end__main:
	lw $ra, 8($sp)
	addu $sp, $sp, 12
	li $v0, 10
	syscall
_printf:
	li $v0, 1
	lw $a0, 4($sp)
	syscall
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
