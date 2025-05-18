.data
array:				   .word    2, 7, 8, 7, 3, 7, 4, 5, 6, 7, 7, 8, 8, 8, 7
length:				   .word    56
second_largest_prompt: .asciiz "Second largest value is "
found_index_prompt:	   .asciiz "found in index "
comma:				   .asciiz ", "


.text
main:
	la $s0, array
	lw $s1, length
	li $t0, 0
	lw $s2, 0($s0)
	
first_largest:
	bgt $t0, $s1, exit_first_largest
	
	add $t1, $s0, $t0
	lw $t2, 0($t1)
	
	bge	$s2, $t2, continue_first_largest
	move $s2, $t2
	
continue_first_largest:
	addi $t0, $t0, 4
	j first_largest
	
exit_first_largest:
	li $t0, 0
	lw $s3, 0($s0)

not_first_largest:
	bgt $t0, $s1, exit_not_first_largest
	
	add $t1, $s0, $t0
	lw $t2, 0($t1)
	
	beq	$t2, $s3, continue_not_first_largest
	move $s3, $t2
	j exit_not_first_largest
	
continue_not_first_largest:
	addi $t0, $t0, 4
	j not_first_largest

exit_not_first_largest:
	li $t0, 0
	
second_largest:
	bgt $t0, $s1, exit_second_largest
	
	add $t1, $s0, $t0
	lw $t2, 0($t1)
	
	bge $s3, $t2, continue_second_largest
	bge $t2, $s2, continue_second_largest
	move $s3, $t2
	
continue_second_largest:
	addi $t0, $t0, 4
	j second_largest

exit_second_largest:
	li $v0, 4
	la $a0, second_largest_prompt
	syscall
	
	li $v0, 1
	move $a0, $s3
	syscall
	
	li $v0, 4
	la $a0, comma
	syscall
	
	li $v0, 4
	la $a0, found_index_prompt
	syscall

	li $t0, 0

find_index:
	bgt $t0, $s1, exit_find_index
	
	add $t1, $s0, $t0
	lw $t2, 0($t1)
	
	bne $t2, $s3, continue_find_index
	srl $t3, $t0, 2
	li $v0, 1
	move $a0, $t3
	syscall
	
	li $v0, 4
	la $a0, comma
	syscall
	
continue_find_index:
	addi $t0, $t0, 4
	j find_index

exit_find_index:
	li $v0, 10
	syscall
