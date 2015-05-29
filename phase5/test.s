	.data
__s0:
	.byte 37
	.byte 100
	.byte 10
	.byte 0
	.text
main:
	addu $sp, $sp, -80256
	sw $ra, 12($sp)
	la $t0, 80040($sp)
	li $t1, 0
	sw $t1, 0($t0)
	la $t0, 80032($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label2
label1:
	la $t0, 80044($sp)
	lw $t1, 80032($sp)
	sw $t1, 0($t0)
	lw $t0, 80032($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80048($sp)
	la $t0, 80032($sp)
	lw $t1, 80048($sp)
	sw $t1, 0($t0)
label2:
	lw $t0, 80032($sp)
	li $t1, 100
	slt $t2, $t0, $t1
	sw $t2, 80052($sp)
	lw $t0, 80052($sp)
	beq $t0, 0, label3
	la $t0, 80036($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label5
label4:
	la $t0, 80056($sp)
	lw $t1, 80036($sp)
	sw $t1, 0($t0)
	lw $t0, 80036($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80060($sp)
	la $t0, 80036($sp)
	lw $t1, 80060($sp)
	sw $t1, 0($t0)
label5:
	lw $t0, 80036($sp)
	li $t1, 100
	slt $t2, $t0, $t1
	sw $t2, 80064($sp)
	lw $t0, 80064($sp)
	beq $t0, 0, label6
	lw $t0, 80036($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 80068($sp)
	lw $t0, 80032($sp)
	li $t1, 400
	mul $t2, $t0, $t1
	sw $t2, 80076($sp)
	la $t0, 80084($sp)
	la $t1, 40032($sp)
	sw $t1, 0($t0)
	lw $t0, 80084($sp)
	lw $t1, 80076($sp)
	addu $t1, $t0, $t1
	sw $t1, 80080($sp)
	lw $t0, 80080($sp)
	lw $t1, 80068($sp)
	addu $t1, $t0, $t1
	sw $t1, 80072($sp)
	lw $t0, 80072($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label4
label6:
	j label1
label3:
	la $t0, 80032($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label8
label7:
	la $t0, 80088($sp)
	lw $t1, 80032($sp)
	sw $t1, 0($t0)
	lw $t0, 80032($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80092($sp)
	la $t0, 80032($sp)
	lw $t1, 80092($sp)
	sw $t1, 0($t0)
label8:
	lw $t0, 80032($sp)
	li $t1, 100
	slt $t2, $t0, $t1
	sw $t2, 80096($sp)
	lw $t0, 80096($sp)
	beq $t0, 0, label9
	lw $t0, 80032($sp)
	li $t1, 20
	sgt $t2, $t0, $t1
	sw $t2, 80100($sp)
	lw $t0, 80100($sp)
	beq $t0, 0, label12
	lw $t0, 80032($sp)
	li $t1, 80
	slt $t2, $t0, $t1
	sw $t2, 80108($sp)
	la $t0, 80104($sp)
	lw $t1, 80108($sp)
	sne $t1, $t1, 0
	sw $t1, 0($t0)
	j label13
label12:
	la $t0, 80104($sp)
	li $t1, 0
	sw $t1, 0($t0)
label13:
	lw $t0, 80104($sp)
	bne $t0, 0, label10
	j label11
label10:
	lw $t0, 80032($sp)
	li $t1, 400
	mul $t2, $t0, $t1
	sw $t2, 80116($sp)
	la $t0, 80124($sp)
	la $t1, 40032($sp)
	sw $t1, 0($t0)
	lw $t0, 80124($sp)
	lw $t1, 80116($sp)
	addu $t1, $t0, $t1
	sw $t1, 80120($sp)
	la $t0, 80112($sp)
	lw $t1, 80120($sp)
	sw $t1, 0($t0)
	la $t0, 80036($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label15
label14:
	la $t0, 80128($sp)
	lw $t1, 80036($sp)
	sw $t1, 0($t0)
	lw $t0, 80036($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80132($sp)
	la $t0, 80036($sp)
	lw $t1, 80132($sp)
	sw $t1, 0($t0)
label15:
	lw $t0, 80036($sp)
	li $t1, 100
	slt $t2, $t0, $t1
	sw $t2, 80136($sp)
	lw $t0, 80136($sp)
	beq $t0, 0, label16
	lw $t0, 80036($sp)
	li $t1, 5
	sgt $t2, $t0, $t1
	sw $t2, 80140($sp)
	lw $t0, 80140($sp)
	bne $t0, 0, label19
	lw $t0, 80032($sp)
	li $t1, 90
	slt $t2, $t0, $t1
	sw $t2, 80148($sp)
	la $t0, 80144($sp)
	lw $t1, 80148($sp)
	sne $t1, $t1, 0
	sw $t1, 0($t0)
	j label20
label19:
	la $t0, 80144($sp)
	li $t1, 1
	sw $t1, 0($t0)
label20:
	lw $t0, 80144($sp)
	bne $t0, 0, label17
	j label18
label17:
	lw $t0, 80036($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 80152($sp)
	lw $t0, 80152($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 80160($sp)
	lw $t0, 80112($sp)
	lw $t1, 80160($sp)
	addu $t2, $t0, $t1
	sw $t2, 80156($sp)
	la $t0, 80164($sp)
	li $t1, 0
	sw $t1, 0($t0)
	lw $t0, 80156($sp)
	lw $t1, 80164($sp)
	addu $t1, $t0, $t1
	sw $t1, 80168($sp)
	li $t0, 100
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 80172($sp)
	lw $t0, 80172($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80176($sp)
	lw $t0, 80176($sp)
	li $t1, 1
	subu $t2, $t0, $t1
	sw $t2, 80180($sp)
	lw $t0, 80180($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80184($sp)
	lw $t0, 80184($sp)
	li $t1, 2
	div $t2, $t0, $t1
	sw $t2, 80188($sp)
	lw $t0, 80036($sp)
	lw $t1, 80188($sp)
	addu $t2, $t0, $t1
	sw $t2, 80192($sp)
	lw $t0, 80168($sp)
	lw $t1, 80192($sp)
	sw $t1, 0($t0)
label18:
	j label14
label16:
label11:
	j label7
label9:
	la $t0, 80032($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label22
label21:
	la $t0, 80196($sp)
	lw $t1, 80032($sp)
	sw $t1, 0($t0)
	lw $t0, 80032($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80200($sp)
	la $t0, 80032($sp)
	lw $t1, 80200($sp)
	sw $t1, 0($t0)
label22:
	lw $t0, 80032($sp)
	li $t1, 100
	slt $t2, $t0, $t1
	sw $t2, 80204($sp)
	lw $t0, 80204($sp)
	beq $t0, 0, label23
	la $t0, 80036($sp)
	li $t1, 0
	sw $t1, 0($t0)
	j label25
label24:
	la $t0, 80208($sp)
	lw $t1, 80036($sp)
	sw $t1, 0($t0)
	lw $t0, 80036($sp)
	li $t1, 1
	addu $t2, $t0, $t1
	sw $t2, 80212($sp)
	la $t0, 80036($sp)
	lw $t1, 80212($sp)
	sw $t1, 0($t0)
label25:
	lw $t0, 80036($sp)
	li $t1, 100
	slt $t2, $t0, $t1
	sw $t2, 80216($sp)
	lw $t0, 80216($sp)
	beq $t0, 0, label26
	lw $t0, 80036($sp)
	li $t1, 4
	mul $t2, $t0, $t1
	sw $t2, 80220($sp)
	lw $t0, 80032($sp)
	li $t1, 400
	mul $t2, $t0, $t1
	sw $t2, 80228($sp)
	la $t0, 80236($sp)
	la $t1, 40032($sp)
	sw $t1, 0($t0)
	lw $t0, 80236($sp)
	lw $t1, 80228($sp)
	addu $t1, $t0, $t1
	sw $t1, 80232($sp)
	lw $t0, 80232($sp)
	lw $t1, 80220($sp)
	addu $t1, $t0, $t1
	sw $t1, 80224($sp)
	lw $t0, 80040($sp)
	lw $t1, 80224($sp)
	lw $t1, 0($t1)
	addu $t2, $t0, $t1
	sw $t2, 80240($sp)
	la $t0, 80040($sp)
	lw $t1, 80240($sp)
	sw $t1, 0($t0)
	j label24
label26:
	j label21
label23:
	la $t0, 80244($sp)
	la $t1, __s0
	sw $t1, 0($t0)
	lw $t0, 80244($sp)
	sw $t0, 4($sp)
	lw $t0, 80040($sp)
	sw $t0, 8($sp)
	jal _printf
	la $t0, 80248($sp)
	la $t1, 0($sp)
	sw $t1, 0($t0)
	la $t0, 80252($sp)
	lw $t1, 80248($sp)
	lw $t1, 0($t1)
	sw $t1, 0($t0)
__end__main:
	lw $ra, 12($sp)
	addu $sp, $sp, 80256
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
	addu $a2, $a2, 2
	lw $a3, 0($a1)
	bgt $a3, 999, _printf_width_end
	li $v0, 1
	li $a0, 0
	syscall
	bgt $a3, 99, _printf_width_end
	li $v0, 1
	li $a0, 0
	syscall
	bgt $a3, 9, _printf_width_end
	li $v0, 1
	li $a0, 0
	syscall
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
