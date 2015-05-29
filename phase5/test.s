	.data
__1:	.space 4
__2:	.space 4
__3:	.space 560
__s0:
	.byte 37
	.byte 100
	.byte 9
	.byte 0
__s1:
	.byte 10
	.byte 0
	.byte 0
	.byte 0
__s2:
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 99
	.byte 32
	.byte 37
	.byte 100
	.byte 44
	.byte 32
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.byte 0
	.byte 0
__s3:
	.byte 10
	.byte 0
	.byte 0
	.byte 0
__s4:
	.byte 37
	.byte 100
	.byte 32
	.byte 0
__s5:
	.byte 10
	.byte 0
	.byte 0
	.byte 0
	.text
_comp1:
	addu $sp, $sp, -16
	sw $ra, 0($sp)
	la $t0, 20($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 4($sp)
	la $t0, 24($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 8($sp)
	lw $t0, 4($sp)
	lw $t0, 0($t0)
	lw $t1, 8($sp)
	lw $t1, 0($t1)
	sne $t2, $t0, $t1
	sw $t2, 12($sp)
	lw $t0, 12($sp)
	bne $t0, 0, label1
	li $v0, 1
	sw $v0, 16($sp)
	j __end__comp1
	j label2
label1:
	li $v0, 0
	sw $v0, 16($sp)
	j __end__comp1
label2:
__end__comp1:
	lw $ra, 0($sp)
	addu $sp, $sp, 16
	j $ra
_compare:
	addu $sp, $sp, -176
	sw $ra, 12($sp)
	la $t0, 28($sp)
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 24($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label4
label3:
	lw $t0, 24($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 32($sp)
	la $t0, 24($sp)
	lw $t1, 32($sp)
	sw $t1, 0($t0)
label4:
	lw $t0, 24($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 36($sp)
	lw $t0, 36($sp)
	beq $t0, 0, label5
	la $t0, 28($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label7
label6:
	lw $t0, 28($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 40($sp)
	la $t0, 28($sp)
	lw $t1, 40($sp)
	sw $t1, 0($t0)
label7:
	lw $t0, 28($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 44($sp)
	lw $t0, 44($sp)
	beq $t0, 0, label8
	lw $t0, 28($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 48($sp)
	lw $t0, 24($sp)
	li $t1, 20
	mul $t2, $t0, $t1
	sw $t2, 56($sp)
	la $t0, 180($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 64($sp)
	lw $t0, 64($sp)
	lw $t1, 56($sp)
	addu $t1, $t0, $t1
	sw $t1, 60($sp)
	lw $t0, 60($sp)
	lw $t1, 48($sp)
	addu $t1, $t0, $t1
	sw $t1, 52($sp)
	lw $t0, 28($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 68($sp)
	lw $t0, 24($sp)
	li $t1, 20
	mul $t2, $t0, $t1
	sw $t2, 76($sp)
	la $t0, 292($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 84($sp)
	lw $t0, 84($sp)
	lw $t1, 76($sp)
	addu $t1, $t0, $t1
	sw $t1, 80($sp)
	lw $t0, 80($sp)
	lw $t1, 68($sp)
	addu $t1, $t0, $t1
	sw $t1, 72($sp)
	lw $t0, 52($sp)
	lw $t0, 0($t0)
	lw $t1, 72($sp)
	lw $t1, 0($t1)
	sne $t2, $t0, $t1
	sw $t2, 88($sp)
	lw $t0, 88($sp)
	bne $t0, 0, label9
	j label10
label9:
	li $v0, 0
	sw $v0, 176($sp)
	j __end__compare
label10:
	j label6
label8:
	j label3
label5:
	li $t0, 0
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 92($sp)
	la $t0, 180($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 100($sp)
	lw $t0, 100($sp)
	lw $t1, 92($sp)
	addu $t1, $t0, $t1
	sw $t1, 96($sp)
	li $t0, 0
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 104($sp)
	la $t0, 292($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 112($sp)
	lw $t0, 112($sp)
	lw $t1, 104($sp)
	addu $t1, $t0, $t1
	sw $t1, 108($sp)
	lw $t0, 96($sp)
	lb $t0, 0($t0)
	lw $t1, 108($sp)
	lb $t1, 0($t1)
	sne $t2, $t0, $t1
	sw $t2, 116($sp)
	lw $t0, 116($sp)
	bne $t0, 0, label11
	li $t0, 1
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 120($sp)
	la $t0, 180($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 128($sp)
	lw $t0, 128($sp)
	lw $t1, 120($sp)
	addu $t1, $t0, $t1
	sw $t1, 124($sp)
	li $t0, 1
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 132($sp)
	la $t0, 292($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 140($sp)
	lw $t0, 140($sp)
	lw $t1, 132($sp)
	addu $t1, $t0, $t1
	sw $t1, 136($sp)
	lw $t0, 124($sp)
	lb $t0, 0($t0)
	lw $t1, 136($sp)
	lb $t1, 0($t1)
	sne $t2, $t0, $t1
	sw $t2, 144($sp)
	lw $t0, 144($sp)
	bne $t0, 0, label13
	la $t0, 180($sp)
	li $t1, 108
	addu $t1, $t0, $t1
	sw $t1, 148($sp)
	la $t0, 292($sp)
	li $t1, 108
	addu $t1, $t0, $t1
	sw $t1, 152($sp)
	la $t0, 156($sp)
	lw $t1, 148($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 156($sp)
	sw $t0, 4($sp)
	la $t0, 160($sp)
	lw $t1, 152($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 160($sp)
	sw $t0, 8($sp)
	jal _comp1
	la $t0, 164($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 168($sp)
	lw $t1, 164($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $v0, 168($sp)
	sw $v0, 176($sp)
	j __end__compare
	j label14
label13:
	li $v0, 0
	sw $v0, 176($sp)
	j __end__compare
label14:
	j label12
label11:
	li $v0, 0
	sw $v0, 176($sp)
	j __end__compare
label12:
	li $t0, 1
	negu $t0, $t0
	sw $t0, 172($sp)
	lw $v0, 172($sp)
	sw $v0, 176($sp)
	j __end__compare
__end__compare:
	lw $ra, 12($sp)
	addu $sp, $sp, 176
	j $ra
_getNode:
	addu $sp, $sp, -256
	sw $ra, 0($sp)
	lw $t0, 368($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 8($sp)
	la $t0, 124($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 124($sp)
	lw $t1, 8($sp)
	addu $t1, $t0, $t1
	sw $t1, 12($sp)
	lw $t0, 12($sp)
	li $t1, 104
	addu $t1, $t0, $t1
	sw $t1, 4($sp)
	la $t0, 128($sp)
	lw $t1, 4($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 4($sp)
	lw $t0, 0($t0)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 132($sp)
	lw $t0, 4($sp)
	lw $t1, 132($sp)
	sw $t1, 0($t0)
	lw $t0, 368($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 136($sp)
	la $t0, 252($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 252($sp)
	lw $t1, 136($sp)
	addu $t1, $t0, $t1
	sw $t1, 140($sp)
	lw $t0, 140($sp)
	la $v0, 256($sp)
	lw $t1, 0($t0)
	sw $t1, 0($v0)
	lw $t1, 4($t0)
	sw $t1, 4($v0)
	lw $t1, 8($t0)
	sw $t1, 8($v0)
	lw $t1, 12($t0)
	sw $t1, 12($v0)
	lw $t1, 16($t0)
	sw $t1, 16($v0)
	lw $t1, 20($t0)
	sw $t1, 20($v0)
	lw $t1, 24($t0)
	sw $t1, 24($v0)
	lw $t1, 28($t0)
	sw $t1, 28($v0)
	lw $t1, 32($t0)
	sw $t1, 32($v0)
	lw $t1, 36($t0)
	sw $t1, 36($v0)
	lw $t1, 40($t0)
	sw $t1, 40($v0)
	lw $t1, 44($t0)
	sw $t1, 44($v0)
	lw $t1, 48($t0)
	sw $t1, 48($v0)
	lw $t1, 52($t0)
	sw $t1, 52($v0)
	lw $t1, 56($t0)
	sw $t1, 56($v0)
	lw $t1, 60($t0)
	sw $t1, 60($v0)
	lw $t1, 64($t0)
	sw $t1, 64($v0)
	lw $t1, 68($t0)
	sw $t1, 68($v0)
	lw $t1, 72($t0)
	sw $t1, 72($v0)
	lw $t1, 76($t0)
	sw $t1, 76($v0)
	lw $t1, 80($t0)
	sw $t1, 80($v0)
	lw $t1, 84($t0)
	sw $t1, 84($v0)
	lw $t1, 88($t0)
	sw $t1, 88($v0)
	lw $t1, 92($t0)
	sw $t1, 92($v0)
	lw $t1, 96($t0)
	sw $t1, 96($v0)
	lw $t1, 100($t0)
	sw $t1, 100($v0)
	lw $t1, 104($t0)
	sw $t1, 104($v0)
	lw $t1, 108($t0)
	sw $t1, 108($v0)
	j __end__getNode
__end__getNode:
	lw $ra, 0($sp)
	addu $sp, $sp, 256
	j $ra
_exchange:
	addu $sp, $sp, -260
	sw $ra, 0($sp)
	la $t0, 228($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 260($sp)
	lw $t1, 228($sp)
	addu $t1, $t0, $t1
	sw $t1, 232($sp)
	la $t0, 116($sp)
	lw $t1, 232($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 236($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 260($sp)
	lw $t1, 236($sp)
	addu $t1, $t0, $t1
	sw $t1, 240($sp)
	la $t0, 244($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 264($sp)
	lw $t1, 244($sp)
	addu $t1, $t0, $t1
	sw $t1, 248($sp)
	lw $t0, 240($sp)
	lw $t1, 248($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 252($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 264($sp)
	lw $t1, 252($sp)
	addu $t1, $t0, $t1
	sw $t1, 256($sp)
	lw $t0, 256($sp)
	lw $t1, 116($sp)
	sw $t1, 0($t0)
__end__exchange:
	lw $ra, 0($sp)
	addu $sp, $sp, 260
	j $ra
_comp:
	addu $sp, $sp, -1148
	sw $ra, 116($sp)
	la $t0, 464($sp)
	lw $t1, 1152($sp)
	sw $t1, 0($t0)
	lw $t0, 464($sp)
	sw $t0, 112($sp)
	jal _getNode
	la $t0, 468($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 580($sp)
	lw $t1, 468($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 352($sp)
	la $t1, 580($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 804($sp)
	lw $t1, 1156($sp)
	sw $t1, 0($t0)
	lw $t0, 804($sp)
	sw $t0, 112($sp)
	jal _getNode
	la $t0, 808($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 920($sp)
	lw $t1, 808($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 692($sp)
	la $t1, 920($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 1032($sp)
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 1036($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label16
label15:
	lw $t0, 1032($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1040($sp)
	la $t0, 1032($sp)
	lw $t1, 1040($sp)
	sw $t1, 0($t0)
label16:
	lw $t0, 1032($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 1044($sp)
	lw $t0, 1044($sp)
	beq $t0, 0, label17
	j label19
label18:
	lw $t0, 1036($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1048($sp)
	la $t0, 1036($sp)
	lw $t1, 1048($sp)
	sw $t1, 0($t0)
label19:
	lw $t0, 1036($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 1052($sp)
	lw $t0, 1052($sp)
	beq $t0, 0, label20
	lw $t0, 1036($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 1056($sp)
	lw $t0, 1032($sp)
	li $t1, 20
	mul $t2, $t0, $t1
	sw $t2, 1064($sp)
	la $t0, 352($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 1072($sp)
	lw $t0, 1072($sp)
	lw $t1, 1064($sp)
	addu $t1, $t0, $t1
	sw $t1, 1068($sp)
	lw $t0, 1068($sp)
	lw $t1, 1056($sp)
	addu $t1, $t0, $t1
	sw $t1, 1060($sp)
	lw $t0, 1036($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 1076($sp)
	lw $t0, 1032($sp)
	li $t1, 20
	mul $t2, $t0, $t1
	sw $t2, 1084($sp)
	la $t0, 692($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 1092($sp)
	lw $t0, 1092($sp)
	lw $t1, 1084($sp)
	addu $t1, $t0, $t1
	sw $t1, 1088($sp)
	lw $t0, 1088($sp)
	lw $t1, 1076($sp)
	addu $t1, $t0, $t1
	sw $t1, 1080($sp)
	lw $t0, 1060($sp)
	lw $t0, 0($t0)
	lw $t1, 1080($sp)
	lw $t1, 0($t1)
	sgt $t2, $t0, $t1
	sw $t2, 1096($sp)
	lw $t0, 1096($sp)
	bne $t0, 0, label21
	j label22
label21:
	la $t0, 352($sp)
	sw $t0, 1100($sp)
	la $t0, 692($sp)
	sw $t0, 1104($sp)
	la $t0, 1108($sp)
	lw $t1, 1100($sp)
	sw $t1, 0($t0)
	lw $t0, 1108($sp)
	sw $t0, 0($sp)
	la $t0, 1112($sp)
	lw $t1, 1104($sp)
	sw $t1, 0($t0)
	lw $t0, 1112($sp)
	sw $t0, 4($sp)
	jal _exchange
	la $t0, 352($sp)
	li $t1, 108
	addu $t1, $t0, $t1
	sw $t1, 1120($sp)
	lw $t0, 1120($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 1116($sp)
	la $t0, 1124($sp)
	lw $t1, 1116($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 1116($sp)
	lw $t0, 0($t0)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1128($sp)
	lw $t0, 1116($sp)
	lw $t1, 1128($sp)
	sw $t1, 0($t0)
	la $t0, 692($sp)
	li $t1, 108
	addu $t1, $t0, $t1
	sw $t1, 1136($sp)
	lw $t0, 1136($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 1132($sp)
	la $t0, 1140($sp)
	lw $t1, 1132($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 1132($sp)
	lw $t0, 0($t0)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 1144($sp)
	lw $t0, 1132($sp)
	lw $t1, 1144($sp)
	sw $t1, 0($t0)
label22:
	j label18
label20:
	j label15
label17:
__end__comp:
	lw $ra, 116($sp)
	addu $sp, $sp, 1148
	j $ra
_show:
	addu $sp, $sp, -784
	sw $ra, 24($sp)
	la $t0, 36($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label24
label23:
	lw $t0, 36($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 40($sp)
	la $t0, 36($sp)
	lw $t1, 40($sp)
	sw $t1, 0($t0)
label24:
	lw $t0, 36($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 44($sp)
	lw $t0, 44($sp)
	beq $t0, 0, label25
	la $t0, 48($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label27
label26:
	lw $t0, 48($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 52($sp)
	la $t0, 48($sp)
	lw $t1, 52($sp)
	sw $t1, 0($t0)
label27:
	lw $t0, 48($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 56($sp)
	lw $t0, 56($sp)
	beq $t0, 0, label28
	la $t0, 60($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	lw $t0, 48($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 64($sp)
	lw $t0, 36($sp)
	li $t1, 20
	mul $t2, $t0, $t1
	sw $t2, 72($sp)
	lw $t0, 784($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 84($sp)
	la $t0, 200($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 200($sp)
	lw $t1, 84($sp)
	addu $t1, $t0, $t1
	sw $t1, 88($sp)
	lw $t0, 88($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 80($sp)
	lw $t0, 80($sp)
	lw $t1, 72($sp)
	addu $t1, $t0, $t1
	sw $t1, 76($sp)
	lw $t0, 76($sp)
	lw $t1, 64($sp)
	addu $t1, $t0, $t1
	sw $t1, 68($sp)
	la $t0, 204($sp)
	lw $t1, 60($sp)
	sw $t1, 0($t0)
	lw $t0, 204($sp)
	sw $t0, 4($sp)
	la $t0, 208($sp)
	lw $t1, 68($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 208($sp)
	sw $t0, 8($sp)
	jal _printf
	la $t0, 212($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 216($sp)
	lw $t1, 212($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label26
label28:
	la $t0, 220($sp)
	la $t1, __s1
	sw $t1, 0($t0)
	la $t0, 224($sp)
	lw $t1, 220($sp)
	sw $t1, 0($t0)
	lw $t0, 224($sp)
	sw $t0, 4($sp)
	jal _printf
	la $t0, 228($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 232($sp)
	lw $t1, 228($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label23
label25:
	la $t0, 236($sp)
	la $t1, __s2
	sw $t1, 0($t0)
	li $t0, 0
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 240($sp)
	lw $t0, 784($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 252($sp)
	la $t0, 368($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 368($sp)
	lw $t1, 252($sp)
	addu $t1, $t0, $t1
	sw $t1, 256($sp)
	lw $t0, 256($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 248($sp)
	lw $t0, 248($sp)
	lw $t1, 240($sp)
	addu $t1, $t0, $t1
	sw $t1, 244($sp)
	li $t0, 1
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 372($sp)
	lw $t0, 784($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 384($sp)
	la $t0, 500($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 500($sp)
	lw $t1, 384($sp)
	addu $t1, $t0, $t1
	sw $t1, 388($sp)
	lw $t0, 388($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 380($sp)
	lw $t0, 380($sp)
	lw $t1, 372($sp)
	addu $t1, $t0, $t1
	sw $t1, 376($sp)
	lw $t0, 784($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 508($sp)
	la $t0, 624($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 624($sp)
	lw $t1, 508($sp)
	addu $t1, $t0, $t1
	sw $t1, 512($sp)
	lw $t0, 512($sp)
	li $t1, 104
	addu $t1, $t0, $t1
	sw $t1, 504($sp)
	lw $t0, 784($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 636($sp)
	la $t0, 752($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 752($sp)
	lw $t1, 636($sp)
	addu $t1, $t0, $t1
	sw $t1, 640($sp)
	lw $t0, 640($sp)
	li $t1, 108
	addu $t1, $t0, $t1
	sw $t1, 632($sp)
	lw $t0, 632($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 628($sp)
	la $t0, 756($sp)
	lw $t1, 236($sp)
	sw $t1, 0($t0)
	lw $t0, 756($sp)
	sw $t0, 4($sp)
	la $t0, 760($sp)
	lw $t1, 244($sp)
	lb $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 760($sp)
	sw $t0, 8($sp)
	la $t0, 764($sp)
	lw $t1, 376($sp)
	lb $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 764($sp)
	sw $t0, 12($sp)
	la $t0, 768($sp)
	lw $t1, 504($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 768($sp)
	sw $t0, 16($sp)
	la $t0, 772($sp)
	lw $t1, 628($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	lw $t0, 772($sp)
	sw $t0, 20($sp)
	jal _printf
	la $t0, 776($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 780($sp)
	lw $t1, 776($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
__end__show:
	lw $ra, 24($sp)
	addu $sp, $sp, 784
	j $ra
main:
	addu $sp, $sp, -2968
	sw $ra, 228($sp)
	la $t0, __1
	li $t1, 5
	sw $t1, 0($t0)
	la $t0, __2
	li $t1, 5
	sw $t1, 0($t0)
	la $t0, 248($sp)
	li $t1, 7
	sw $t1, 0($t0)
	la $t0, 252($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label30
label29:
	lw $t0, 252($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 264($sp)
	la $t0, 252($sp)
	lw $t1, 264($sp)
	sw $t1, 0($t0)
label30:
	lw $t0, 252($sp)
	lw $t1, __2
	slt $t2, $t0, $t1
	sw $t2, 268($sp)
	lw $t0, 268($sp)
	beq $t0, 0, label31
	la $t0, 256($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label33
label32:
	lw $t0, 256($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 272($sp)
	la $t0, 256($sp)
	lw $t1, 272($sp)
	sw $t1, 0($t0)
label33:
	lw $t0, 256($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 276($sp)
	lw $t0, 276($sp)
	beq $t0, 0, label34
	la $t0, 260($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label36
label35:
	lw $t0, 260($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 280($sp)
	la $t0, 260($sp)
	lw $t1, 280($sp)
	sw $t1, 0($t0)
label36:
	lw $t0, 260($sp)
	lw $t1, __1
	slt $t2, $t0, $t1
	sw $t2, 284($sp)
	lw $t0, 284($sp)
	beq $t0, 0, label37
	lw $t0, 260($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 288($sp)
	lw $t0, 256($sp)
	li $t1, 20
	mul $t2, $t0, $t1
	sw $t2, 296($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 308($sp)
	la $t0, 424($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 424($sp)
	lw $t1, 308($sp)
	addu $t1, $t0, $t1
	sw $t1, 312($sp)
	lw $t0, 312($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 304($sp)
	lw $t0, 304($sp)
	lw $t1, 296($sp)
	addu $t1, $t0, $t1
	sw $t1, 300($sp)
	lw $t0, 300($sp)
	lw $t1, 288($sp)
	addu $t1, $t0, $t1
	sw $t1, 292($sp)
	lw $t0, 256($sp)
	li $t1, 5110
	mul $t2, $t0, $t1
	sw $t2, 428($sp)
	lw $t0, 428($sp)
	lw $t1, 260($sp)
	addu $t2, $t0, $t1
	sw $t2, 432($sp)
	li $t0, 34
	lw $t1, 252($sp)
	subu $t2, $t0, $t1
	sw $t2, 436($sp)
	lw $t0, 432($sp)
	lw $t1, 436($sp)
	rem $t2, $t0, $t1
	sw $t2, 440($sp)
	lw $t0, 440($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 444($sp)
	lw $t0, 292($sp)
	lw $t1, 444($sp)
	sw $t1, 0($t0)
	li $t0, 0
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 448($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 460($sp)
	la $t0, 576($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 576($sp)
	lw $t1, 460($sp)
	addu $t1, $t0, $t1
	sw $t1, 464($sp)
	lw $t0, 464($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 456($sp)
	lw $t0, 456($sp)
	lw $t1, 448($sp)
	addu $t1, $t0, $t1
	sw $t1, 452($sp)
	lw $t0, 256($sp)
	lw $t1, 256($sp)
	mul $t2, $t0, $t1
	sw $t2, 580($sp)
	lw $t0, 580($sp)
	lw $t1, 256($sp)
	mul $t2, $t0, $t1
	sw $t2, 584($sp)
	lw $t0, 252($sp)
	lw $t1, 584($sp)
	addu $t2, $t0, $t1
	sw $t2, 588($sp)
	lw $t0, 452($sp)
	lw $t1, 588($sp)
	sb $t1, 0($t0)
	li $t0, 1
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 592($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 604($sp)
	la $t0, 720($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 720($sp)
	lw $t1, 604($sp)
	addu $t1, $t0, $t1
	sw $t1, 608($sp)
	lw $t0, 608($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 600($sp)
	lw $t0, 600($sp)
	lw $t1, 592($sp)
	addu $t1, $t0, $t1
	sw $t1, 596($sp)
	lw $t0, 260($sp)
	lw $t1, 256($sp)
	addu $t2, $t0, $t1
	sw $t2, 724($sp)
	lw $t0, 724($sp)
	lw $t1, 252($sp)
	addu $t2, $t0, $t1
	sw $t2, 728($sp)
	lw $t0, 728($sp)
	li $t1, 1
	sll $t2, $t0, $t1
	sw $t2, 732($sp)
	lw $t0, 596($sp)
	lw $t1, 732($sp)
	sb $t1, 0($t0)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 744($sp)
	la $t0, 860($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 860($sp)
	lw $t1, 744($sp)
	addu $t1, $t0, $t1
	sw $t1, 748($sp)
	lw $t0, 748($sp)
	li $t1, 108
	addu $t1, $t0, $t1
	sw $t1, 740($sp)
	lw $t0, 740($sp)
	li $t1, 0
	addu $t1, $t0, $t1
	sw $t1, 736($sp)
	lw $t0, 256($sp)
	not $t0, $t0
	sw $t0, 864($sp)
	lw $t0, 252($sp)
	lw $t1, 864($sp)
	addu $t2, $t0, $t1
	sw $t2, 868($sp)
	lw $t0, 868($sp)
	lw $t1, 260($sp)
	or $t2, $t0, $t1
	sw $t2, 872($sp)
	lw $t0, 736($sp)
	lw $t1, 872($sp)
	sw $t1, 0($t0)
	li $t0, 0
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 876($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 888($sp)
	la $t0, 1004($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 1004($sp)
	lw $t1, 888($sp)
	addu $t1, $t0, $t1
	sw $t1, 892($sp)
	lw $t0, 892($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 884($sp)
	lw $t0, 884($sp)
	lw $t1, 876($sp)
	addu $t1, $t0, $t1
	sw $t1, 880($sp)
	li $t0, 0
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 1008($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 1020($sp)
	la $t0, 1136($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 1136($sp)
	lw $t1, 1020($sp)
	addu $t1, $t0, $t1
	sw $t1, 1024($sp)
	lw $t0, 1024($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 1016($sp)
	lw $t0, 1016($sp)
	lw $t1, 1008($sp)
	addu $t1, $t0, $t1
	sw $t1, 1012($sp)
	li $t0, 122
	li $t1, 97
	subu $t2, $t0, $t1
	sw $t2, 1140($sp)
	lw $t0, 1140($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1144($sp)
	lw $t0, 1012($sp)
	lb $t0, 0($t0)
	lb $t0, 1144($sp)
	rem $t2, $t0, $t1
	sw $t2, 1148($sp)
	lw $t0, 1148($sp)
	li $t1, 97
	addu $t2, $t0, $t1
	sw $t2, 1152($sp)
	lw $t0, 880($sp)
	lw $t1, 1152($sp)
	sb $t1, 0($t0)
	li $t0, 1
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 1156($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 1168($sp)
	la $t0, 1284($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 1284($sp)
	lw $t1, 1168($sp)
	addu $t1, $t0, $t1
	sw $t1, 1172($sp)
	lw $t0, 1172($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 1164($sp)
	lw $t0, 1164($sp)
	lw $t1, 1156($sp)
	addu $t1, $t0, $t1
	sw $t1, 1160($sp)
	li $t0, 1
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, 1288($sp)
	lw $t0, 252($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 1300($sp)
	la $t0, 1416($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 1416($sp)
	lw $t1, 1300($sp)
	addu $t1, $t0, $t1
	sw $t1, 1304($sp)
	lw $t0, 1304($sp)
	li $t1, 100
	addu $t1, $t0, $t1
	sw $t1, 1296($sp)
	lw $t0, 1296($sp)
	lw $t1, 1288($sp)
	addu $t1, $t0, $t1
	sw $t1, 1292($sp)
	li $t0, 90
	li $t1, 65
	subu $t2, $t0, $t1
	sw $t2, 1420($sp)
	lw $t0, 1420($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1424($sp)
	lw $t0, 1292($sp)
	lb $t0, 0($t0)
	lb $t0, 1424($sp)
	rem $t2, $t0, $t1
	sw $t2, 1428($sp)
	lw $t0, 1428($sp)
	li $t1, 65
	addu $t2, $t0, $t1
	sw $t2, 1432($sp)
	lw $t0, 1160($sp)
	lw $t1, 1432($sp)
	sb $t1, 0($t0)
	j label35
label37:
	j label32
label34:
	j label29
label31:
	la $t0, 256($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label39
label38:
	lw $t0, 256($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1436($sp)
	la $t0, 256($sp)
	lw $t1, 1436($sp)
	sw $t1, 0($t0)
label39:
	lw $t0, 256($sp)
	lw $t1, __2
	slt $t2, $t0, $t1
	sw $t2, 1440($sp)
	lw $t0, 1440($sp)
	beq $t0, 0, label40
	la $t0, 260($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label42
label41:
	lw $t0, 260($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1444($sp)
	la $t0, 260($sp)
	lw $t1, 1444($sp)
	sw $t1, 0($t0)
label42:
	lw $t0, 260($sp)
	lw $t1, __2
	slt $t2, $t0, $t1
	sw $t2, 1448($sp)
	lw $t0, 1448($sp)
	beq $t0, 0, label43
	la $t0, 1452($sp)
	lw $t1, 256($sp)
	sw $t1, 0($t0)
	lw $t0, 1452($sp)
	sw $t0, 4($sp)
	la $t0, 1456($sp)
	lw $t1, 260($sp)
	sw $t1, 0($t0)
	lw $t0, 1456($sp)
	sw $t0, 8($sp)
	jal _comp
	la $t0, 1460($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 1464($sp)
	lw $t1, 1460($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label41
label43:
	j label38
label40:
	la $t0, 252($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label45
label44:
	lw $t0, 252($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 1468($sp)
	la $t0, 252($sp)
	lw $t1, 1468($sp)
	sw $t1, 0($t0)
label45:
	lw $t0, 252($sp)
	lw $t1, __2
	slt $t2, $t0, $t1
	sw $t2, 1472($sp)
	lw $t0, 1472($sp)
	beq $t0, 0, label46
	la $t0, 1476($sp)
	lw $t1, 252($sp)
	sw $t1, 0($t0)
	lw $t0, 1476($sp)
	sw $t0, 0($sp)
	jal _show
	j label44
label46:
	lw $t0, __2
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 1480($sp)
	la $t0, 256($sp)
	lw $t1, 1480($sp)
	sw $t1, 0($t0)
	j label48
label47:
	la $t0, 1484($sp)
	lw $t1, 256($sp)
	sw $t1, 0($t0)
	lw $t0, 256($sp)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 1488($sp)
	la $t0, 256($sp)
	lw $t1, 1488($sp)
	sw $t1, 0($t0)
label48:
	li $t0, 1
	negu $t0, $t0
	sw $t0, 1492($sp)
	lw $t0, 256($sp)
	lw $t1, 1492($sp)
	sgt $t2, $t0, $t1
	sw $t2, 1496($sp)
	lw $t0, 1496($sp)
	beq $t0, 0, label49
	lw $t0, 256($sp)
	li $t1, 3
	rem $t2, $t0, $t1
	sw $t2, 1500($sp)
	lw $t0, 1500($sp)
	li $t1, 0
	seq $t2, $t0, $t1
	sw $t2, 1504($sp)
	lw $t0, 1504($sp)
	bne $t0, 0, label50
	lw $t0, 256($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 1508($sp)
	la $t0, 1624($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 1624($sp)
	lw $t1, 1508($sp)
	addu $t1, $t0, $t1
	sw $t1, 1512($sp)
	la $t0, 1628($sp)
	lw $t1, 256($sp)
	sw $t1, 0($t0)
	lw $t0, 1628($sp)
	sw $t0, 112($sp)
	jal _getNode
	la $t0, 1632($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 1744($sp)
	lw $t1, 1632($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	lw $t0, 1512($sp)
	la $t1, 1744($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	j label51
label50:
	lw $t0, 256($sp)
	li $t1, 112
	mul $t2, $t0, $t1
	sw $t2, 1856($sp)
	la $t0, 1972($sp)
	la $t1, __3
	sw $t1, 0($t0)
	lw $t0, 1972($sp)
	lw $t1, 1856($sp)
	addu $t1, $t0, $t1
	sw $t1, 1860($sp)
	lw $t0, 256($sp)
	li $t1, 3
	addu $t2, $t0, $t1
	sw $t2, 1976($sp)
	lw $t0, 1976($sp)
	lw $t1, __2
	rem $t2, $t0, $t1
	sw $t2, 1980($sp)
	la $t0, 1984($sp)
	lw $t1, 1980($sp)
	sw $t1, 0($t0)
	lw $t0, 1984($sp)
	sw $t0, 112($sp)
	jal _getNode
	la $t0, 1988($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2100($sp)
	lw $t1, 1988($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	lw $t0, 1860($sp)
	la $t1, 2100($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
label51:
	j label47
label49:
	la $t0, 2212($sp)
	la $t1, __s3
	sw $t1, 0($t0)
	la $t0, 2216($sp)
	lw $t1, 2212($sp)
	sw $t1, 0($t0)
	lw $t0, 2216($sp)
	sw $t0, 4($sp)
	jal _printf
	la $t0, 2220($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2224($sp)
	lw $t1, 2220($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 256($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label53
label52:
	lw $t0, 256($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 2228($sp)
	la $t0, 256($sp)
	lw $t1, 2228($sp)
	sw $t1, 0($t0)
label53:
	lw $t0, 256($sp)
	lw $t1, __2
	slt $t2, $t0, $t1
	sw $t2, 2232($sp)
	lw $t0, 2232($sp)
	beq $t0, 0, label54
	la $t0, 260($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label56
label55:
	lw $t0, 260($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 2236($sp)
	la $t0, 260($sp)
	lw $t1, 2236($sp)
	sw $t1, 0($t0)
label56:
	lw $t0, 260($sp)
	lw $t1, __2
	slt $t2, $t0, $t1
	sw $t2, 2240($sp)
	lw $t0, 2240($sp)
	beq $t0, 0, label57
	la $t0, 2244($sp)
	la $t1, __s4
	sw $t1, 0($t0)
	la $t0, 2248($sp)
	lw $t1, 256($sp)
	sw $t1, 0($t0)
	lw $t0, 2248($sp)
	sw $t0, 112($sp)
	jal _getNode
	la $t0, 2252($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2364($sp)
	lw $t1, 2252($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 2476($sp)
	lw $t1, 260($sp)
	sw $t1, 0($t0)
	lw $t0, 2476($sp)
	sw $t0, 112($sp)
	jal _getNode
	la $t0, 2480($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2592($sp)
	lw $t1, 2480($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 2704($sp)
	la $t1, 2364($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 2704($sp)
	lw $t1, 0($t0)
	sw $t1, 4($sp)
	lw $t1, 4($t0)
	sw $t1, 8($sp)
	lw $t1, 8($t0)
	sw $t1, 12($sp)
	lw $t1, 12($t0)
	sw $t1, 16($sp)
	lw $t1, 16($t0)
	sw $t1, 20($sp)
	lw $t1, 20($t0)
	sw $t1, 24($sp)
	lw $t1, 24($t0)
	sw $t1, 28($sp)
	lw $t1, 28($t0)
	sw $t1, 32($sp)
	lw $t1, 32($t0)
	sw $t1, 36($sp)
	lw $t1, 36($t0)
	sw $t1, 40($sp)
	lw $t1, 40($t0)
	sw $t1, 44($sp)
	lw $t1, 44($t0)
	sw $t1, 48($sp)
	lw $t1, 48($t0)
	sw $t1, 52($sp)
	lw $t1, 52($t0)
	sw $t1, 56($sp)
	lw $t1, 56($t0)
	sw $t1, 60($sp)
	lw $t1, 60($t0)
	sw $t1, 64($sp)
	lw $t1, 64($t0)
	sw $t1, 68($sp)
	lw $t1, 68($t0)
	sw $t1, 72($sp)
	lw $t1, 72($t0)
	sw $t1, 76($sp)
	lw $t1, 76($t0)
	sw $t1, 80($sp)
	lw $t1, 80($t0)
	sw $t1, 84($sp)
	lw $t1, 84($t0)
	sw $t1, 88($sp)
	lw $t1, 88($t0)
	sw $t1, 92($sp)
	lw $t1, 92($t0)
	sw $t1, 96($sp)
	lw $t1, 96($t0)
	sw $t1, 100($sp)
	lw $t1, 100($t0)
	sw $t1, 104($sp)
	lw $t1, 104($t0)
	sw $t1, 108($sp)
	lw $t1, 108($t0)
	sw $t1, 112($sp)
	la $t0, 2816($sp)
	la $t1, 2592($sp)
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t0)
	lw $t2, 8($t1)
	sw $t2, 8($t0)
	lw $t2, 12($t1)
	sw $t2, 12($t0)
	lw $t2, 16($t1)
	sw $t2, 16($t0)
	lw $t2, 20($t1)
	sw $t2, 20($t0)
	lw $t2, 24($t1)
	sw $t2, 24($t0)
	lw $t2, 28($t1)
	sw $t2, 28($t0)
	lw $t2, 32($t1)
	sw $t2, 32($t0)
	lw $t2, 36($t1)
	sw $t2, 36($t0)
	lw $t2, 40($t1)
	sw $t2, 40($t0)
	lw $t2, 44($t1)
	sw $t2, 44($t0)
	lw $t2, 48($t1)
	sw $t2, 48($t0)
	lw $t2, 52($t1)
	sw $t2, 52($t0)
	lw $t2, 56($t1)
	sw $t2, 56($t0)
	lw $t2, 60($t1)
	sw $t2, 60($t0)
	lw $t2, 64($t1)
	sw $t2, 64($t0)
	lw $t2, 68($t1)
	sw $t2, 68($t0)
	lw $t2, 72($t1)
	sw $t2, 72($t0)
	lw $t2, 76($t1)
	sw $t2, 76($t0)
	lw $t2, 80($t1)
	sw $t2, 80($t0)
	lw $t2, 84($t1)
	sw $t2, 84($t0)
	lw $t2, 88($t1)
	sw $t2, 88($t0)
	lw $t2, 92($t1)
	sw $t2, 92($t0)
	lw $t2, 96($t1)
	sw $t2, 96($t0)
	lw $t2, 100($t1)
	sw $t2, 100($t0)
	lw $t2, 104($t1)
	sw $t2, 104($t0)
	lw $t2, 108($t1)
	sw $t2, 108($t0)
	la $t0, 2816($sp)
	lw $t1, 0($t0)
	sw $t1, 116($sp)
	lw $t1, 4($t0)
	sw $t1, 120($sp)
	lw $t1, 8($t0)
	sw $t1, 124($sp)
	lw $t1, 12($t0)
	sw $t1, 128($sp)
	lw $t1, 16($t0)
	sw $t1, 132($sp)
	lw $t1, 20($t0)
	sw $t1, 136($sp)
	lw $t1, 24($t0)
	sw $t1, 140($sp)
	lw $t1, 28($t0)
	sw $t1, 144($sp)
	lw $t1, 32($t0)
	sw $t1, 148($sp)
	lw $t1, 36($t0)
	sw $t1, 152($sp)
	lw $t1, 40($t0)
	sw $t1, 156($sp)
	lw $t1, 44($t0)
	sw $t1, 160($sp)
	lw $t1, 48($t0)
	sw $t1, 164($sp)
	lw $t1, 52($t0)
	sw $t1, 168($sp)
	lw $t1, 56($t0)
	sw $t1, 172($sp)
	lw $t1, 60($t0)
	sw $t1, 176($sp)
	lw $t1, 64($t0)
	sw $t1, 180($sp)
	lw $t1, 68($t0)
	sw $t1, 184($sp)
	lw $t1, 72($t0)
	sw $t1, 188($sp)
	lw $t1, 76($t0)
	sw $t1, 192($sp)
	lw $t1, 80($t0)
	sw $t1, 196($sp)
	lw $t1, 84($t0)
	sw $t1, 200($sp)
	lw $t1, 88($t0)
	sw $t1, 204($sp)
	lw $t1, 92($t0)
	sw $t1, 208($sp)
	lw $t1, 96($t0)
	sw $t1, 212($sp)
	lw $t1, 100($t0)
	sw $t1, 216($sp)
	lw $t1, 104($t0)
	sw $t1, 220($sp)
	lw $t1, 108($t0)
	sw $t1, 224($sp)
	jal _compare
	la $t0, 2928($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2932($sp)
	lw $t1, 2928($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	la $t0, 2936($sp)
	lw $t1, 2244($sp)
	sw $t1, 0($t0)
	lw $t0, 2936($sp)
	sw $t0, 4($sp)
	la $t0, 2940($sp)
	lw $t1, 2932($sp)
	sw $t1, 0($t0)
	lw $t0, 2940($sp)
	sw $t0, 8($sp)
	jal _printf
	la $t0, 2944($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2948($sp)
	lw $t1, 2944($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label55
label57:
	la $t0, 2952($sp)
	la $t1, __s5
	sw $t1, 0($t0)
	la $t0, 2956($sp)
	lw $t1, 2952($sp)
	sw $t1, 0($t0)
	lw $t0, 2956($sp)
	sw $t0, 4($sp)
	jal _printf
	la $t0, 2960($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 2964($sp)
	lw $t1, 2960($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
	j label52
label54:
	li $v0, 0
	sw $v0, 2968($sp)
	j __end__main
__end__main:
	lw $ra, 228($sp)
	addu $sp, $sp, 2968
	li $v0, 10
	syscall
_printf:
	la $a1, 4($sp)
	lw $a2, 4($sp)
	j _printf_loop
_printf_end:
	j $ra
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
	beq $a0, 'd', _printf_int
	beq $a0, 's', _printf_str
	beq $a0, 'c', _printf_char
	beq $a0, '0', _printf_width
	beq $a0, '.', _printf_width
_printf_int:
	addu $a1, $a1, 4
	lw $a0, 0($a1)
	li $v0, 1
	syscall
	j _printf_loop
_printf_str:
	addu $a1, $a1, 4
	lw $a0, 0($a1)
	li $v0, 4
	syscall
	j _printf_loop
_printf_char:
	addu $a1, $a1, 4
	lb $a0, 0($a1)
	li $v0, 11
	syscall
	j _printf_loop
_printf_width:
	addu $a1, $a1, 4
	lb $t0, 0($a2)
	subu $t0, $t0, '0'
	addu $a2, $a2, 2
	lw $t1, 0($a1)
	li $t2, 1
	blt $t0, 2, _printf_width_end
_label_width_1:
	subu $t0, $t0, 1
	mul $t2, $t2, 10
	bgt $t0, 1, _label_width_1
	li $a0, 0
	li $v0, 1
_label_width_2:
	bge $t1, $t2, _printf_width_end
	syscall
	div $t2, $t2, 10
	j _label_width_2
_printf_width_end:	lw $a0, 0($a1)
	li $v0, 1
	syscall
	j _printf_loop
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
