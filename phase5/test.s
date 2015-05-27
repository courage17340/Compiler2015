	.data
__4:	.space 4
__5:	.space 4
__6:	.space 4
__7:	.space 4
__9:	.space 4
__10:	.space 4
__11:	.space 4
__12:	.space 4
__13:	.space 4
__14:	.space 4
__15:	.space 4
__16:	.space 4
	.text
gcd:
	addu $sp, $sp, -16
	sw $ra, 12($sp)
	lw $t0, 20($sp)
	lw $t1, 24($sp)
	rem $t2, $t0, $t1
	sw $t2, __4
	lw $t0, __4
	li $t1, 0
	seq $t2, $t0, $t1
	sw $t2, __5
	lw $t0, __5
	bne $t0, 0, label1
	lw $t0, 20($sp)
	lw $t1, 24($sp)
	rem $t2, $t0, $t1
	sw $t2, __6
	lw $t0, 24($sp)
	sw $t0, 4($sp)
	lw $t0, __6
	sw $t0, 8($sp)
	jal gcd
	la $t0, __7
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $v0, __7
	lw $v0, 0($v0)
	sw $v0, 16($sp)
	j __end__gcd
	j label2
label1:
	lw $v0, 24($sp)
	sw $v0, 16($sp)
	j __end__gcd
label2:
__end__gcd:
	lw $ra, 12($sp)
	addu $sp, $sp, 16
	j $ra
main:
	addu $sp, $sp, -16
	sw $ra, 12($sp)
	li $t0, 10
	sw $t0, 4($sp)
	li $t0, 1
	sw $t0, 8($sp)
	jal gcd
	la $t0, __9
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __9
	lw $t0, 0($t0)
	sw $t0, 4($sp)
	jal printf
	la $t0, __10
	la $t1, 0($sp)
	sw $t1, 0($t0)
	li $t0, 50
	sw $t0, 4($sp)
	li $t0, 35
	sw $t0, 8($sp)
	jal gcd
	la $t0, __11
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __11
	lw $t0, 0($t0)
	sw $t0, 4($sp)
	jal printf
	la $t0, __12
	la $t1, 0($sp)
	sw $t1, 0($t0)
	li $t0, 34986
	sw $t0, 4($sp)
	li $t0, 3087
	sw $t0, 8($sp)
	jal gcd
	la $t0, __13
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __13
	lw $t0, 0($t0)
	sw $t0, 4($sp)
	jal printf
	la $t0, __14
	la $t1, 0($sp)
	sw $t1, 0($t0)
	li $t0, 2907
	sw $t0, 4($sp)
	li $t0, 1539
	sw $t0, 8($sp)
	jal gcd
	la $t0, __15
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __15
	lw $t0, 0($t0)
	sw $t0, 4($sp)
	jal printf
	la $t0, __16
	la $t1, 0($sp)
	sw $t1, 0($t0)
	li $v0, 0
	sw $v0, 16($sp)
	j __end__main
__end__main:
	lw $ra, 12($sp)
	addu $sp, $sp, 16
	li $v0, 10
	syscall
printf:
	li $v0, 1
	lw $a0, 4($sp)
	syscall
	j $ra
malloc:
	lw $v0, 4($sp)
	syscall
	sw $v0, 0($sp)
	j $ra
getchar:
	li $v0, 12
	syscall
	sw $v0, 0($sp)
	j $ra
