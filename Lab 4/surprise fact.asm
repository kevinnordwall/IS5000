.text

addi $a0,$0,8
addi $v0,$0,1

loop:
	beq $a0,$0,finito
	mul $v0,$v0,$a0
	addi $a0,$a0,-1
	beq $0,$0,loop
	
finito:
	beq $0,$0,finito