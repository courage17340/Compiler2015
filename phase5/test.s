	.data
__7:	.space 4
__8:	.space 4
__9:	.space 4
__10:	.space 4
__11:	.space 4
__12:	.space 4
__13:	.space 4
__14:	.space 4
__15:	.space 4
__16:	.space 4
__17:	.space 4
__24:	.space 4
__25:	.space 4
__26:	.space 4
__27:	.space 4
__28:	.space 4
__29:	.space 4
__30:	.space 4
__31:	.space 4
	.text
cd:
	addu $sp, $sp, -28
	sw $ra, 24($sp)
	lw $t0, 32($sp)
	li $t1, 1
	seq $t2, $t0, $t1
	sw $t2, __7
	lw $t0, __7
	bne $t0, 0, label1
	lw $t0, 32($sp)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, __8
	lw $t0, __8
	sw $t0, 4($sp)
	lb $t0, 36($sp)
	sb $t0, 8($sp)
	lb $t0, 44($sp)
	sb $t0, 12($sp)
	lb $t0, 40($sp)
	sb $t0, 16($sp)
	lw $t0, 48($sp)
	sw $t0, 20($sp)
	jal cd
	la $t0, __9
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 48($sp)
	lw $t1, __9
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lb $t0, 36($sp)
	sb $t0, 4($sp)
	jal printf
	la $t0, __10
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lb $t0, 44($sp)
	sb $t0, 4($sp)
	jal printf
	la $t0, __11
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, 32($sp)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, __12
	lw $t0, __12
	sw $t0, 4($sp)
	lb $t0, 40($sp)
	sb $t0, 8($sp)
	lb $t0, 36($sp)
	sb $t0, 12($sp)
	lb $t0, 44($sp)
	sb $t0, 16($sp)
	lw $t0, 48($sp)
	sw $t0, 20($sp)
	jal cd
	la $t0, __13
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 48($sp)
	lw $t1, __13
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, __14
	lw $t1, 48($sp)
	sw $t1, 0($t0)
	lw $t0, 48($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 48($sp)
	j label2
label1:
	lb $t0, 36($sp)
	sb $t0, 4($sp)
	jal printf
	la $t0, __15
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lb $t0, 44($sp)
	sb $t0, 4($sp)
	jal printf
	la $t0, __16
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, __17
	lw $t1, 48($sp)
	sw $t1, 0($t0)
	lw $t0, 48($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 48($sp)
label2:
	lw $v0, 48($sp)
	sw $v0, 28($sp)
	j __end__cd
__end__cd:
	lw $ra, 24($sp)
	addu $sp, $sp, 28
	j $ra
main:
	addu $sp, $sp, -48
	sw $ra, 24($sp)
	la $t0, 28($sp)
	li $t1, 1
	sb $t1, 0($t0)
	la $t0, 32($sp)
	li $t1, 2
	sb $t1, 0($t0)
	la $t0, 36($sp)
	li $t1, 3
	sb $t1, 0($t0)
	jal getchar
	la $t0, __24
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __24
	lw $t0, 0($t0)
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, __25
	li $t0, 10
	lw $t1, __25
	mul $t2, $t0, $t1
	sw $t2, __26
	jal getchar
	la $t0, __27
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __26
	lw $t1, __27
	lw $t1, 0($t1)
	addu $t2, $t0, $t1
	sw $t2, __28
	lw $t0, __28
	li $t1, 48
	subu $t2, $t0, $t1
	sw $t2, __29
	la $t0, 40($sp)
	lw $t1, __29
	sw $t1, 0($t0)
	lw $t0, 40($sp)
	sw $t0, 4($sp)
	lb $t0, 28($sp)
	sb $t0, 8($sp)
	lb $t0, 32($sp)
	sb $t0, 12($sp)
	lb $t0, 36($sp)
	sb $t0, 16($sp)
	li $t0, 0
	sw $t0, 20($sp)
	jal cd
	la $t0, __30
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 44($sp)
	lw $t1, __30
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 44($sp)
	sw $t0, 4($sp)
	jal printf
	la $t0, __31
	la $t1, 0($sp)
	sw $t1, 0($t0)
	li $v0, 0
	sw $v0, 48($sp)
	j __end__main
__end__main:
	lw $ra, 24($sp)
	addu $sp, $sp, 48
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
