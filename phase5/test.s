	.data
__1:	.space 4
__2:	.space 400
__5:	.space 4
__6:	.space 4
__11:	.space 4
__12:	.space 4
__13:	.space 4
__14:	.space 4
__15:	.space 4
__16:	.space 4
__17:	.space 4
__18:	.space 4
__19:	.space 4
__20:	.space 4
__21:	.space 4
__22:	.space 4
__23:	.space 4
__24:	.space 4
__25:	.space 4
__26:	.space 4
__27:	.space 4
__28:	.space 4
__29:	.space 4
__30:	.space 4
__31:	.space 4
__32:	.space 4
__33:	.space 4
__34:	.space 4
__35:	.space 4
__36:	.space 4
__37:	.space 4
__38:	.space 4
__39:	.space 4
__40:	.space 4
__41:	.space 4
__42:	.space 4
__43:	.space 4
__44:	.space 4
__45:	.space 4
__46:	.space 4
__47:	.space 4
__48:	.space 4
__53:	.space 4
__54:	.space 4
__55:	.space 4
__56:	.space 4
__57:	.space 4
__58:	.space 4
__59:	.space 4
__60:	.space 4
__63:	.space 4
__64:	.space 4
__65:	.space 4
__66:	.space 4
__67:	.space 4
__68:	.space 4
__69:	.space 4
__70:	.space 4
__71:	.space 4
__72:	.space 4
__73:	.space 4
	.text
getHash:
	addu $sp, $sp, -4
	sw $ra, 0($sp)
	lw $t0, 8($sp)
	li $t1, 237
	mul $t2, $t0, $t1
	sw $t2, __5
	lw $t0, __5
	lw $t1, __1
	rem $t2, $t0, $t1
	sw $t2, __6
	lw $v0, __6
	sw $v0, 4($sp)
	j __end__getHash
__end__getHash:
	lw $ra, 0($sp)
	addu $sp, $sp, 4
	j $ra
put:
	addu $sp, $sp, -20
	sw $ra, 8($sp)
	lw $t0, 20($sp)
	sw $t0, 4($sp)
	jal getHash
	la $t0, __11
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 12($sp)
	lw $t1, __11
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __12
	la $t0, __14
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __14
	lw $t1, __12
	addu $t1, $t0, $t1
	sw $t1, __13
	lw $t0, __13
	lw $t0, 0($t0)
	li $t1, 0
	seq $t2, $t0, $t1
	sw $t2, __15
	lw $t0, __15
	bne $t0, 0, label1
	j label2
label1:
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __16
	la $t0, __18
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __18
	lw $t1, __16
	addu $t1, $t0, $t1
	sw $t1, __17
	li $t0, 12
	sw $t0, 4($sp)
	jal malloc
	la $t0, __20
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, __19
	lw $t1, __20
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, __17
	lw $t1, __19
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __22
	la $t0, __24
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __24
	lw $t1, __22
	addu $t1, $t0, $t1
	sw $t1, __23
	lw $t0, __23
	lw $t0, 0($t0)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, __21
	lw $t0, __21
	lw $t1, 20($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __26
	la $t0, __28
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __28
	lw $t1, __26
	addu $t1, $t0, $t1
	sw $t1, __27
	lw $t0, __27
	lw $t0, 0($t0)
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, __25
	lw $t0, __25
	lw $t1, 24($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __30
	la $t0, __32
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __32
	lw $t1, __30
	addu $t1, $t0, $t1
	sw $t1, __31
	lw $t0, __31
	lw $t0, 0($t0)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __29
	lw $t0, __29
	li $t1, 0
	sw $t1, 0($t0)
	j __end__put
label2:
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __33
	la $t0, __35
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __35
	lw $t1, __33
	addu $t1, $t0, $t1
	sw $t1, __34
	la $t0, 16($sp)
	lw $t1, __34
	lw $t1, 0($t1)
	sw $t1, 0($t0)
label3:
	lw $t0, 16($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, __36
	lw $t0, __36
	lw $t0, 0($t0)
	lw $t1, 20($sp)
	sne $t2, $t0, $t1
	sw $t2, __37
	lw $t0, __37
	beq $t0, 0, label4
	lw $t0, 16($sp)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __38
	lw $t0, __38
	lw $t0, 0($t0)
	li $t1, 0
	seq $t2, $t0, $t1
	sw $t2, __39
	lw $t0, __39
	bne $t0, 0, label5
	j label6
label5:
	lw $t0, 16($sp)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __40
	li $t0, 12
	sw $t0, 4($sp)
	jal malloc
	la $t0, __42
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, __41
	lw $t1, __42
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, __40
	lw $t1, __41
	sw $t1, 0($t0)
	lw $t0, 16($sp)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __44
	lw $t0, __44
	lw $t0, 0($t0)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, __43
	lw $t0, __43
	lw $t1, 20($sp)
	sw $t1, 0($t0)
	lw $t0, 16($sp)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __46
	lw $t0, __46
	lw $t0, 0($t0)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __45
	lw $t0, __45
	li $t1, 0
	sw $t1, 0($t0)
label6:
	lw $t0, 16($sp)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __47
	la $t0, 16($sp)
	lw $t1, __47
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label3
label4:
	lw $t0, 16($sp)
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, __48
	lw $t0, __48
	lw $t1, 24($sp)
	sw $t1, 0($t0)
__end__put:
	lw $ra, 8($sp)
	addu $sp, $sp, 20
	j $ra
get:
	addu $sp, $sp, -20
	sw $ra, 8($sp)
	lw $t0, 24($sp)
	sw $t0, 4($sp)
	jal getHash
	la $t0, __54
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __54
	lw $t0, 0($t0)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __53
	la $t0, __56
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __56
	lw $t1, __53
	addu $t1, $t0, $t1
	sw $t1, __55
	la $t0, 16($sp)
	lw $t1, __55
	lw $t1, 0($t1)
	sw $t1, 0($t0)
label7:
	lw $t0, 16($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, __57
	lw $t0, __57
	lw $t0, 0($t0)
	lw $t1, 24($sp)
	sne $t2, $t0, $t1
	sw $t2, __58
	lw $t0, __58
	beq $t0, 0, label8
	lw $t0, 16($sp)
	li $t1, 8
	addu $t1, $t0, $t1
	sw $t1, __59
	la $t0, 16($sp)
	lw $t1, __59
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label7
label8:
	lw $t0, 16($sp)
	li $t1, 4
	addu $t1, $t0, $t1
	sw $t1, __60
	lw $v0, __60
	lw $v0, 0($v0)
	sw $v0, 20($sp)
	j __end__get
__end__get:
	lw $ra, 8($sp)
	addu $sp, $sp, 20
	j $ra
main:
	addu $sp, $sp, -16
	sw $ra, 8($sp)
	la $t0, __1
	li $t1, 100
	sw $t1, 0($t0)
	la $t0, 12($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label10
label9:
	la $t0, __63
	lw $t1, 12($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 12($sp)
label10:
	lw $t0, 12($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, __64
	lw $t0, __64
	beq $t0, 0, label11
	lw $t0, 12($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, __65
	la $t0, __67
	la $t1, __2
	sw $t1, 0($t0)
	lw $t0, __67
	lw $t1, __65
	addu $t1, $t0, $t1
	sw $t1, __66
	lw $t0, __66
	li $t1, 0
	sw $t1, 0($t0)
	j label9
label11:
	la $t0, 12($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label13
label12:
	la $t0, __68
	lw $t1, 12($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 12($sp)
label13:
	lw $t0, 12($sp)
	li $t1, 1000
	slt $t2, $t0, $t1
	sw $t2, __69
	lw $t0, __69
	beq $t0, 0, label14
	lw $t0, 12($sp)
	sw $t0, 0($sp)
	lw $t0, 12($sp)
	sw $t0, 4($sp)
	jal put
	j label12
label14:
	la $t0, 12($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label16
label15:
	la $t0, __70
	lw $t1, 12($sp)
	sw $t1, 0($t0)
	lw $t0, 12($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 12($sp)
label16:
	lw $t0, 12($sp)
	li $t1, 1000
	slt $t2, $t0, $t1
	sw $t2, __71
	lw $t0, __71
	beq $t0, 0, label17
	lw $t0, 12($sp)
	sw $t0, 4($sp)
	jal get
	la $t0, __72
	la $t1, 0($sp)
	sw $t1, 0($t0)
	lw $t0, __72
	lw $t0, 0($t0)
	sw $t0, 4($sp)
	jal printf
	la $t0, __73
	la $t1, 0($sp)
	sw $t1, 0($t0)
	j label15
label17:
__end__main:
	lw $ra, 8($sp)
	addu $sp, $sp, 16
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
