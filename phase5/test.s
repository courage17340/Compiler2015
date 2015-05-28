	.data
__1:	.space 4
__3:	.space 4
__4:	.space 4
__5:	.space 4
__6:	.space 4
__7:	.space 4
__11:	.space 4
__12:	.space 4
__13:	.space 4
__14:	.space 4
__15:	.space 4
__16:	.space 4
__17:	.space 4
__18:	.space 4
__19:	.space 4
__24:	.space 4
__25:	.space 4
__26:	.space 4
__27:	.space 4
__28:	.space 4
__29:	.space 4
__30:	.space 4
__31:	.space 4
__33:	.space 4
__34:	.space 4
__35:	.space 4
__36:	.space 4
__37:	.space 4
__38:	.space 4
__39:	.space 4
__40:	.space 4
	.text
addSmall:
	addu $sp, $sp, -4
	sw $ra, 0($sp)
	la $t0, __3
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 4($sp)
	lw $t1, __3
	addu $t1, $t0, $t1
	sw $t1, __4
	la $t0, __5
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 4($sp)
	lw $t1, __5
	addu $t1, $t0, $t1
	sw $t1, __6
	lw $t0, __6
	lw $t0, 0($t0)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, __7
	lw $t0, __4
	lw $t1, __7
	sw $t1, 0($t0)
__end__addSmall:
	lw $ra, 0($sp)
	addu $sp, $sp, 4
	j $ra
addMiddle:
	addu $sp, $sp, -16
	sw $ra, 4($sp)
	la $t0, 8($sp)
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 12($sp)
	li $t1, 1
	sw $t1, 0($t0)
	j label2
label1:
	la $t0, __11
	lw $t1, 12($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 12($sp)
label2:
	lw $t0, 12($sp)
	li $t1, 10
	sle $t2, $t0, $t1
	sw $t2, __12
	lw $t0, __12
	beq $t0, 0, label3
	la $t0, 8($sp)
	sw $t0, __13
	lw $t0, __13
	sw $t0, 0($sp)
	jal addSmall
	lw $t0, 8($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, __14
	la $t0, 8($sp)
	lw $t1, __14
	sw $t1, 0($t0)
	j label1
label3:
	la $t0, __15
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 16($sp)
	lw $t1, __15
	addu $t1, $t0, $t1
	sw $t1, __16
	la $t0, __17
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 16($sp)
	lw $t1, __17
	addu $t1, $t0, $t1
	sw $t1, __18
	lw $t0, __18
	lw $t0, 0($t0)
	lw $t1, 8($sp)
	addu $t2, $t0, $t1
	sw $t2, __19
	lw $t0, __16
	lw $t1, __19
	sw $t1, 0($t0)
__end__addMiddle:
	lw $ra, 4($sp)
	addu $sp, $sp, 16
	j $ra
main:
	addu $sp, $sp, -28
	sw $ra, 8($sp)
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
	la $t0, 20($sp)
	lw $t1, __29
	sw $t1, 0($t0)
	la $t0, __1
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 12($sp)
	li $t1, 1
	sw $t1, 0($t0)
	j label5
label4:
	la $t0, __30
	lw $t1, 12($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 12($sp)
label5:
	lw $t0, 12($sp)
	lw $t1, 20($sp)
	sle $t2, $t0, $t1
	sw $t2, __31
	lw $t0, __31
	beq $t0, 0, label6
	la $t0, 24($sp)
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 24($sp)
	sw $t0, __33
	lw $t0, __33
	sw $t0, 0($sp)
	jal addMiddle
	la $t0, __34
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 16($sp)
	lw $t1, __34
	addu $t1, $t0, $t1
	sw $t1, __35
	la $t0, __36
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 16($sp)
	lw $t1, __36
	addu $t1, $t0, $t1
	sw $t1, __37
	lw $t0, __37
	lw $t0, 0($t0)
	lw $t1, 24($sp)
	addu $t2, $t0, $t1
	sw $t2, __38
	lw $t0, __35
	lw $t1, __38
	sw $t1, 0($t0)
	lw $t0, __1
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, __39
	la $t0, __1
	lw $t1, __39
	sw $t1, 0($t0)
	lw $t0, __1
	sw $t0, 4($sp)
	jal printf
	la $t0, __40
	la $t1, 0($sp)
	sw $t1, 0($t0)
	j label4
label6:
__end__main:
	lw $ra, 8($sp)
	addu $sp, $sp, 28
	li $v0, 10
	syscall
printf:
	li $v0, 1
	lw $a0, 4($sp)
	syscall
	j $ra
malloc:
	li $v0, 9
	lw $a0, 4($sp)
	syscall
	sw $v0, 0($sp)
	j $ra
getchar:
	li $v0, 12
	syscall
	sw $v0, 0($sp)
	j $ra
