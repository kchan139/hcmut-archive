.data
array: .word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
size: .word 15

string_mode_in: .asciiz "\nPlease choose string_mode_in 1 (Print value) or 2 (Print sequence): "
string_value_in: .asciiz "\nPlease choose an index [0, 14]: "

strseq_in_1: .asciiz "\nPlease choose the 1st index [0, 14]: "
strseq_in_2: .asciiz "\nPlease choose the 2nd index [0, 14] and >= the 1st index: "

result: .asciiz "\nThe result is: "

out_of_bound: .asciiz "\nIndex out of range!"
invalid_seq: .asciiz "\nThe 2nc index must be >= to the first index!"


.text
main: 
	la $s0 array
	lw $s1 size
	li $v0 4
	la $a0 string_mode_in
	syscall

	li $v0 5
	syscall

	add $s2 $0 $v0
	beq $s2 1 value
	beq $s2 2 sequence

value:
	li $v0 4
	la $a0 string_value_in
	syscall

	li $v0 5
	syscall

	add $s3 $0 $v0
	addi $t1 $0 4
	mul $t0 $s3 $t1
	add $t1 $s0 $t0
	li $v0 4
	la $a0 result
	syscall
	
	lw $a0 ($t1)
	li $v0 1
	syscall
	
sequence:
	# 1st index
	li $v0 4
	la $a0 strseq_in_1
	syscall
	li $v0 5
	syscall
	add $s3 $0 $v0
	
	# Out of range
	blt $s3 0 out_of_range
	bgt $s3 14 out_of_range
	
	# 2nd index
	li $v0 4
	la $a0 strseq_in_2
	syscall
	li $v0 5
	syscall
	add $s4 $0 $v0

	# Out of range
	blt $s4 0 out_of_range
	bgt $s4 14 out_of_range

	# s3: 1st index, s4: 2nd index
	blt $s4 $s3 invalid_sequence
	
	mul $t0 $s3 4
	mul $t1 $s4 4
	add $s5 $0 $t0
	loop:
		beq $s5 $t1 exit
		lw $a0 ($s5)
		li $v0 1
		syscall
	
		addi $s5 $s5 4
		j loop
	exit:
		li $v0 10
		syscall	
	
out_of_range:
	li $v0 4
	la $a0 out_of_bound
	syscall
	li $v0 10
	syscall

invalid_sequence:
	li $v0 4
	la $a0 invalid_seq
	syscall
	li $v0 10
	syscall
