.data
store:  .space 11
string_getinput:  .asciiz "Please input a 10-bit binary number: "
string_result: .asciiz "\nDecimal value: "

.text
main:
	li $v0 4
	la $a0 string_getinput
	syscall
	la $a0 store
	addi $a1 $0 11
	li $v0 8
	syscall
	
	addi $s0 $0 0
	addi $s1 $0 9
	addi $s2 $0 1
	
	
	loop:
		lbu $t0 store($s1)
		sub $t0 $t0 48
		mul $t0 $t0 $s2
		add $s0 $s0 $t0
		
		addi $s1 $s1 -1
		add $s2 $s2 $s2
		
		bgt $s1 -1 loop
	
	
	li $v0 4
	la $a0 string_result
	syscall
	add $a0 $0 $s0
	li $v0 1
	syscall
	li $v0 10
	syscall
