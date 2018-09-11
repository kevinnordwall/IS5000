  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000 # Assignment 3 value = 2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #

hexasc:
	andi $t0,$a0,0xf
	slti $t1,$t0,10
	beqz $t1,isHigher
	nop
	
	addi $v0,$t0,48
	
	jr $ra
	nop
	
isHigher:
	addi $v0,$t0,55
	
	jr $ra
	nop
	
delay:
	PUSH $ra
	div $a0,$a0,1000

while:
	slt $t1,$0,$a0
	beqz $t1, whileEnd
	nop
	
	sub $a0,$a0,1
	li $t2,0
	j for
	nop
	
	
	 
for:
	
	slti $t3, $t2, 4711
	addi $t2,$t2,1
	bnez $t3,for
	nop
	
	j while
	nop
	
	
whileEnd:
	POP $ra
	jr $ra
	nop
	


time2string:
	PUSH $ra

	move $t2,$a0 # Moving address to temp var.
	
	andi $a0,$a1,0xf000
	srl $a0,$a0,12
	jal hexasc
	nop
	sb $v0, 0($t2)
	
	andi $a0,$a1,0xf00
	srl $a0,$a0,8
	jal hexasc
	nop
	sb $v0, 1($t2)
	
	andi $a0,$a1,0xf0
	srl $a0,$a0,4
	jal hexasc
	nop
	sb $v0, 3($t2)
	
	andi $a0,$a1,0xf
	jal hexasc
	nop
	sb $v0, 4($t2)
	
	addi $t1,$0,0x3A #COLON
	addi $t3,$0,0x00 #NULLBYTE
	sb $t1,2($t2)
	sb $t3,5($t2)
	
	POP $ra
	jr $ra
	nop
	
	
	