  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #  
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
 
	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
	
.global delay
.global time2string
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
