	.data
__1:	.space 4
__2:	.space 4
__3:	.space 4
__4:	.space 4
__5:	.space 4
__6:	.space 4
__7:	.space 4
__8:	.space 4
__9:	.space 48000
__10:	.space 48000
__11:	.space 4
__12:	.space 4
__13:	.space 4
__14:	.space 44944
__15:	.space 4
__16:	.space 4
__s0:
	.byte 110
	.byte 111
	.byte 32
	.byte 115
	.byte 111
	.byte 108
	.byte 117
	.byte 116
	.byte 105
	.byte 111
	.byte 110
	.byte 33
	.byte 10
	.byte 0
	.byte 0
	.byte 0
__s1:
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.text
_check:
	addu $sp, $sp, -8
	lw $t0, 12($sp)
	lw $t1, 16($sp)
	bge $t0, $t1, label1
	lw $t0, 12($sp)
	sge $t2, $t0, 0
	sw $t2, 4($sp)
	lw $t1, 4($sp)
	sne $t1, $t1, 0
	sw $t1, 0($sp)
	j label2
label1:
	li $t1, 0
	sw $t1, 0($sp)
label2:
	lw $v0, 0($sp)
	sw $v0, 8($sp)
	j __end__check
__end__check:
	addu $sp, $sp, 8
	j $ra
_addList:
	addu $sp, $sp, -124
	sw $ra, 12($sp)
	lw $t0, 128($sp)
	sw $t0, 4($sp)
	lw $t0, __1
	sw $t0, 8($sp)
	jal _check
	la $t1, 0($sp)
	sw $t1, 16($sp)
	lw $t1, 16($sp)
	lw $t1, 0($t1)
	sw $t1, 20($sp)
	lw $t0, 20($sp)
	bne $t0, 1, label7
	lw $t0, 132($sp)
	sw $t0, 4($sp)
	lw $t0, __1
	sw $t0, 8($sp)
	jal _check
	la $t1, 0($sp)
	sw $t1, 28($sp)
	lw $t1, 28($sp)
	lw $t1, 0($t1)
	sw $t1, 32($sp)
	lw $t0, 32($sp)
	seq $t2, $t0, 1
	sw $t2, 36($sp)
	lw $t1, 36($sp)
	sne $t1, $t1, 0
	sw $t1, 24($sp)
	j label8
label7:
	li $t1, 0
	sw $t1, 24($sp)
label8:
	lw $t0, 24($sp)
	beq $t0, 0, label5
	lw $t0, 132($sp)
	mul $t2, $t0, 4
	sw $t2, 44($sp)
	lw $t0, 128($sp)
	mul $t2, $t0, 424
	sw $t2, 52($sp)
	la $t1, __14
	sw $t1, 60($sp)
	lw $t0, 60($sp)
	lw $t1, 52($sp)
	addu $t1, $t0, $t1
	sw $t1, 56($sp)
	lw $t0, 56($sp)
	lw $t1, 44($sp)
	addu $t1, $t0, $t1
	sw $t1, 48($sp)
	lw $t0, 48($sp)
	lw $t0, 0($t0)
	seq $t2, $t0, -1
	sw $t2, 64($sp)
	lw $t1, 64($sp)
	sne $t1, $t1, 0
	sw $t1, 40($sp)
	j label6
label5:
	li $t1, 0
	sw $t1, 40($sp)
label6:
	lw $t0, 40($sp)
	bne $t0, 0, label3
	j label4
label3:
	lw $t0, __11
	addu $t0, $t0, 1
	sw $t0, __11
	lw $t0, __11
	mul $t2, $t0, 4
	sw $t2, 68($sp)
	la $t1, __9
	sw $t1, 76($sp)
	lw $t0, 76($sp)
	lw $t1, 68($sp)
	addu $t1, $t0, $t1
	sw $t1, 72($sp)
	lw $t0, 72($sp)
	lw $t1, 128($sp)
	sw $t1, 0($t0)
	lw $t0, __11
	mul $t2, $t0, 4
	sw $t2, 80($sp)
	la $t1, __10
	sw $t1, 88($sp)
	lw $t0, 88($sp)
	lw $t1, 80($sp)
	addu $t1, $t0, $t1
	sw $t1, 84($sp)
	lw $t0, 84($sp)
	lw $t1, 132($sp)
	sw $t1, 0($t0)
	lw $t0, 132($sp)
	mul $t2, $t0, 4
	sw $t2, 92($sp)
	lw $t0, 128($sp)
	mul $t2, $t0, 424
	sw $t2, 100($sp)
	la $t1, __14
	sw $t1, 108($sp)
	lw $t0, 108($sp)
	lw $t1, 100($sp)
	addu $t1, $t0, $t1
	sw $t1, 104($sp)
	lw $t0, 104($sp)
	lw $t1, 92($sp)
	addu $t1, $t0, $t1
	sw $t1, 96($sp)
	lw $t0, __13
	addu $t2, $t0, 1
	sw $t2, 112($sp)
	lw $t0, 96($sp)
	lw $t1, 112($sp)
	sw $t1, 0($t0)
	lw $t0, 128($sp)
	lw $t1, __5
	bne $t0, $t1, label11
	lw $t0, 132($sp)
	lw $t1, __6
	seq $t2, $t0, $t1
	sw $t2, 120($sp)
	lw $t1, 120($sp)
	sne $t1, $t1, 0
	sw $t1, 116($sp)
	j label12
label11:
	li $t1, 0
	sw $t1, 116($sp)
label12:
	lw $t0, 116($sp)
	bne $t0, 0, label9
	j label10
label9:
	li $t1, 1
	sw $t1, __12
label10:
label4:
__end__addList:
	lw $ra, 12($sp)
	addu $sp, $sp, 124
	j $ra
main:
	addu $sp, $sp, -232
	sw $ra, 12($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 16($sp)
	lw $t1, 16($sp)
	lw $t1, 0($t1)
	sw $t1, 20($sp)
	lw $t0, 20($sp)
	subu $t2, $t0, 48
	sw $t2, 24($sp)
	li $t0, 100
	lw $t1, 24($sp)
	mul $t2, $t0, $t1
	sw $t2, 28($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 32($sp)
	lw $t1, 32($sp)
	lw $t1, 0($t1)
	sw $t1, 36($sp)
	lw $t0, 36($sp)
	subu $t2, $t0, 48
	sw $t2, 40($sp)
	li $t0, 10
	lw $t1, 40($sp)
	mul $t2, $t0, $t1
	sw $t2, 44($sp)
	lw $t0, 28($sp)
	lw $t1, 44($sp)
	addu $t2, $t0, $t1
	sw $t2, 48($sp)
	jal _getchar
	la $t1, 0($sp)
	sw $t1, 52($sp)
	lw $t1, 52($sp)
	lw $t1, 0($t1)
	sw $t1, 56($sp)
	lw $t0, 48($sp)
	lw $t1, 56($sp)
	addu $t2, $t0, $t1
	sw $t2, 60($sp)
	lw $t0, 60($sp)
	subu $t2, $t0, 48
	sw $t2, 64($sp)
	lw $t1, 64($sp)
	sw $t1, __1
	lw $t0, __1
	subu $t2, $t0, 1
	sw $t2, 68($sp)
	lw $t1, 68($sp)
	sw $t1, __6
	lw $t1, __6
	sw $t1, __5
	li $t1, 0
	sw $t1, __15
	j label14
label13:
	lw $t0, __15
	addu $t0, $t0, 1
	sw $t0, __15
label14:
	lw $t0, __15
	lw $t1, __1
	bge $t0, $t1, label15
	li $t1, 0
	sw $t1, __16
	j label17
label16:
	lw $t0, __16
	addu $t0, $t0, 1
	sw $t0, __16
label17:
	lw $t0, __16
	lw $t1, __1
	bge $t0, $t1, label18
	lw $t0, __16
	mul $t2, $t0, 4
	sw $t2, 72($sp)
	lw $t0, __15
	mul $t2, $t0, 424
	sw $t2, 80($sp)
	la $t1, __14
	sw $t1, 88($sp)
	lw $t0, 88($sp)
	lw $t1, 80($sp)
	addu $t1, $t0, $t1
	sw $t1, 84($sp)
	lw $t0, 84($sp)
	lw $t1, 72($sp)
	addu $t1, $t0, $t1
	sw $t1, 76($sp)
	lw $t0, 76($sp)
	li $t1, -1
	sw $t1, 0($t0)
	j label16
label18:
	j label13
label15:
label19:
	lw $t0, __2
	lw $t1, __11
	bgt $t0, $t1, label20
	lw $t0, __2
	mul $t2, $t0, 4
	sw $t2, 92($sp)
	la $t1, __9
	sw $t1, 100($sp)
	lw $t0, 100($sp)
	lw $t1, 92($sp)
	addu $t1, $t0, $t1
	sw $t1, 96($sp)
	lw $t1, 96($sp)
	lw $t1, 0($t1)
	sw $t1, __7
	lw $t0, __2
	mul $t2, $t0, 4
	sw $t2, 104($sp)
	la $t1, __10
	sw $t1, 112($sp)
	lw $t0, 112($sp)
	lw $t1, 104($sp)
	addu $t1, $t0, $t1
	sw $t1, 108($sp)
	lw $t1, 108($sp)
	lw $t1, 0($t1)
	sw $t1, __8
	lw $t0, __8
	mul $t2, $t0, 4
	sw $t2, 116($sp)
	lw $t0, __7
	mul $t2, $t0, 424
	sw $t2, 124($sp)
	la $t1, __14
	sw $t1, 132($sp)
	lw $t0, 132($sp)
	lw $t1, 124($sp)
	addu $t1, $t0, $t1
	sw $t1, 128($sp)
	lw $t0, 128($sp)
	lw $t1, 116($sp)
	addu $t1, $t0, $t1
	sw $t1, 120($sp)
	lw $t1, 120($sp)
	lw $t1, 0($t1)
	sw $t1, __13
	lw $t0, __7
	subu $t2, $t0, 1
	sw $t2, 136($sp)
	lw $t0, __8
	subu $t2, $t0, 2
	sw $t2, 140($sp)
	lw $t0, 136($sp)
	sw $t0, 4($sp)
	lw $t0, 140($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	subu $t2, $t0, 1
	sw $t2, 144($sp)
	lw $t0, __8
	addu $t2, $t0, 2
	sw $t2, 148($sp)
	lw $t0, 144($sp)
	sw $t0, 4($sp)
	lw $t0, 148($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	addu $t2, $t0, 1
	sw $t2, 152($sp)
	lw $t0, __8
	subu $t2, $t0, 2
	sw $t2, 156($sp)
	lw $t0, 152($sp)
	sw $t0, 4($sp)
	lw $t0, 156($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	addu $t2, $t0, 1
	sw $t2, 160($sp)
	lw $t0, __8
	addu $t2, $t0, 2
	sw $t2, 164($sp)
	lw $t0, 160($sp)
	sw $t0, 4($sp)
	lw $t0, 164($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	subu $t2, $t0, 2
	sw $t2, 168($sp)
	lw $t0, __8
	subu $t2, $t0, 1
	sw $t2, 172($sp)
	lw $t0, 168($sp)
	sw $t0, 4($sp)
	lw $t0, 172($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	subu $t2, $t0, 2
	sw $t2, 176($sp)
	lw $t0, __8
	addu $t2, $t0, 1
	sw $t2, 180($sp)
	lw $t0, 176($sp)
	sw $t0, 4($sp)
	lw $t0, 180($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	addu $t2, $t0, 2
	sw $t2, 184($sp)
	lw $t0, __8
	subu $t2, $t0, 1
	sw $t2, 188($sp)
	lw $t0, 184($sp)
	sw $t0, 4($sp)
	lw $t0, 188($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __7
	addu $t2, $t0, 2
	sw $t2, 192($sp)
	lw $t0, __8
	addu $t2, $t0, 1
	sw $t2, 196($sp)
	lw $t0, 192($sp)
	sw $t0, 4($sp)
	lw $t0, 196($sp)
	sw $t0, 8($sp)
	jal _addList
	lw $t0, __12
	beq $t0, 1, label21
	j label22
label21:
	j label20
label22:
	lw $t0, __2
	addu $t2, $t0, 1
	sw $t2, 200($sp)
	lw $t1, 200($sp)
	sw $t1, __2
	j label19
label20:
	lw $t0, __12
	beq $t0, 1, label23
	la $t1, __s0
	sw $t1, 204($sp)
	lw $t0, 204($sp)
	sw $t0, 4($sp)
	jal _printf
	j label24
label23:
	la $t1, __s1
	sw $t1, 208($sp)
	lw $t0, __6
	mul $t2, $t0, 4
	sw $t2, 212($sp)
	lw $t0, __5
	mul $t2, $t0, 424
	sw $t2, 220($sp)
	la $t1, __14
	sw $t1, 228($sp)
	lw $t0, 228($sp)
	lw $t1, 220($sp)
	addu $t1, $t0, $t1
	sw $t1, 224($sp)
	lw $t0, 224($sp)
	lw $t1, 212($sp)
	addu $t1, $t0, $t1
	sw $t1, 216($sp)
	lw $t0, 208($sp)
	sw $t0, 4($sp)
	lw $t0, 216($sp)
	lw $t0, 0($t0)
	sw $t0, 8($sp)
	jal _printf
label24:
	li $v0, 0
	sw $v0, 232($sp)
	j __end__main
__end__main:
	lw $ra, 12($sp)
	addu $sp, $sp, 232
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
