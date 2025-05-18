.data
string_get_input_N: .asciiz "Input N: "
string_get_input_M: .asciiz "Input M: "
string_get_input_X: .asciiz "Input X: "
endl:               .asciiz "\n"


.text
main:
	#N
	li $v0 4
	la $a0 string_get_input_N
	syscall
	li $v0 5
	syscall
	add $s0 $0 $v0
	
	#M
	li $v0 4
	la $a0 string_get_input_M
	syscall
	li $v0 5
	syscall
	add $s1 $0 $v0
	
	#X
	li $v0 4
	la $a0 string_get_input_X
	syscall
	li $v0 5
	syscall
	addi $s2 $v0 -1 
	
	add $s3 $0 $s0
	addi $s4 $0 0 
	
	jal print
	
	loop:
		mul $s3 $s3 $s1 
		jal print
		addi $s4 $s4 1 
		blt $s4 $s2 loop
		
	li $v0 10
	syscall

print:
	li $v0 1
	add $a0 $0 $s3
	syscall
	li $v0 4
	la $a0 endl
	syscall
	jr $ra
