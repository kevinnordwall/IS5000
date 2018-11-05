.text

addi $a0,$0,8
addi $a1,$a0,-1
add $a2,$0,$0
add $a3,$0,$0
addi $v0,$0,1

outer:
	beq $a0,$0,finito
	beq $a1,$0,finito
	add $a3,$a1,$0
	
	inner:
		beq $a1,$0,iter_done
		add $a2,$a2,$a0
		addi $a1,$a1,-1
		beq $0,$0,inner
		
	iter_done:
		add $a0,$a2,$0
		add $a2,$0,$0
		addi $a1,$a3,-1
		add $v0,$a0,$0
		beq $0,$0,outer		
	
	
finito:
	beq $0,$0,finito