.data
getinput:  .asciiz "Input a number: "
result: .asciiz "Factorial: "


.text
main:
	li $v0 4
	la $a0 getinput
	syscall
	
	li $v0 5
	syscall
	
	addi $s0 $v0 1
	addi $s1 $0 1
	addi $s2 $0 1
	j factorial

factorial:
	beq $s2 $s0 print
	mul $s1 $s1 $s2
	addi $s2 $s2 1
	j factorial
	 
print:
	li $v0 4
	la $a0 result
	syscall
	
	add $a0 $0 $s1
	li $v0 1
	syscall
	
	li $v0 10
	syscall
	
