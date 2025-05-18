.data
string_get_input_a: .asciiz "Input a: "
string_get_input_b: .asciiz "Input b: "
string_get_input_c: .asciiz "Input c: "
string_get_input_d: .asciiz "Input d: "

error1_msg: .asciiz "\na can't be equal to 0, F can't be calculated"
error2_msg: .asciiz "\na and c can't be equal, G can't be calculated"

string_error: .asciiz "\nUndefined Error: Divided-by-0"

F: .asciiz "F = "
G: .asciiz "\nG = "


.text
main:
	# a
	li $v0 4
	la $a0 string_get_input_a
	syscall
	li $v0 5
	syscall
	add $s0 $0 $v0
	#check a = 0
	
	# b
	li $v0 4
	la $a0 string_get_input_b
	syscall
	li $v0 5
	syscall
	add $s1 $0 $v0
	
	# c
	li $v0 4
	la $a0 string_get_input_c
	syscall
	li $v0 5
	syscall
	add $s2 $0 $v0
	# check a = c
	
	# d
	li $v0 4
	la $a0 string_get_input_d
	syscall
	li $v0 5
	syscall
	add $s3 $0 $v0
	
	# Calculating
	jal calc_F
	jal calc_G
	li $v0 10
	syscall
	
calc_F:
	beq $s0 0 error

	add $t0 $s0 $s1
	sub $t1 $s2 $s3
	mul $t3 $s0 $s0
	mul $t4 $t0 $t1
	div $t5 $t4 $t3

	li $v0 4
	la $a0 F
	syscall

	add $a0 $0 $t5
	li $v0 1
	syscall
	jr $ra
	
calc_G:	
	beq $s0 $s2 error

	add $t0 $s0 1
	add $t1 $s1 2
	add $t2 $s2 -3
	sub $t3 $s2 $s0
	mul $t4 $t0 $t1
	mul $t5 $t4 $t2
	div $t6 $t5 $t3

	li $v0 4
	la $a0 G
	syscall
    
	add $a0 $0 $t6
	li $v0 1
	syscall
	jr $ra
	
error: 
	li $v0 4
	la $a0 string_error
	syscall
	jr $ra
