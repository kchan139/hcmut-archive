.data
init_array:			.word	1, 2, 2, 2, 7, 8, 2, 2, 2, 1
unique_array:			.space	40
unique_prompt:			.asciiz	"Unique values: "
duplicate_prompt:		.asciiz	"Duplicate values: "
repeated_prompt:		.asciiz	"repeated "
times_prompt	:		.asciiz	" time(s)"
semi_colon:				.asciiz	"; "
comma:					.asciiz	", "
newline:				.asciiz "\n"


.text
main:
	la $s0, init_array
	la $s1, unique_array
	
	li $s2, 40
	li $s3, 0
	
	li $t0, 0
	
categorize:
	bge $t0, $s2, exit_categorize
	
	add $t1, $s0, $t0
	lw $t2, 0($t1)
	
	# Check exist
	li $t3, 0
	move $a0, $s1
	move $a1, $s3
	jal check_visit
	#
	
	bnez $t3, continue_categorize
	add $t4, $s1, $s3
	sw $t2, 0($t4)
	addi $s3, $s3, 4
	
continue_categorize:
	addi $t0, $t0, 4
	j categorize

check_visit:
	add $sp, $sp, -4
	sw $t0, 0($sp)
	
	li $t0, 0
	
	check_array:
		bge $t0, $a1, exit_check_array
		
		add $t4, $a0, $t0
		lw $t5, 0($t4)
		
		bne $t5, $t2, continue_check_array
		li $t3, 1
		j exit_check_array	
	
	continue_check_array:
		addi $t0, $t0, 4
		j check_array
	
	exit_check_array:
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	jr $ra

exit_categorize:
	li $t0, 0
	li $s4, 1
	
	li $v0, 4
	la $a0, unique_prompt
	syscall

print_unique:
	bge $t0, $s3, exit_print_unique
	
	add $t1, $s1, $t0
	lw $t2, 0($t1)
	
	li $t3, 0
	move $a3, $s0
	move $a1, $s2
	move $a2, $t2
	jal count
	
	bgt $t3, $s4, continue_print_unique
	li $v0, 1
	move $a0, $t2
	syscall
	li $v0, 4
	la $a0, comma
	syscall
	
continue_print_unique:
	addi $t0, $t0, 4
	j print_unique

exit_print_unique:
	li $t0, 0
	li $s4, 2
	
	li $v0, 4
	la $a0, newline
	syscall
	li $v0, 4
	la $a0, duplicate_prompt
	syscall

print_duplicate:
	bge $t0, $s3, exit_print_duplicate
	
	add $t1, $s1, $t0
	lw $t2, 0($t1)
	
	li $t3, 0
	move $a3, $s0
	move $a1, $s2
	move $a2, $t2
	jal count
	
	blt $t3, $s4, continue_print_duplicate
	li $v0, 1
	move $a0, $t2
	syscall
	li $v0, 4
	la $a0, comma
	syscall
	li $v0, 4
	la $a0, repeated_prompt
	syscall
	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 4
	la $a0, times_prompt
	syscall
	li $v0, 4
	la $a0, semi_colon
	syscall
	
continue_print_duplicate:
	addi $t0, $t0, 4
	j print_duplicate

exit_print_duplicate:
	li $v0, 10
	syscall
	
count:

	addi $sp, $sp, -12
	sw $t0, 8($sp)
	sw $t1, 4($sp)
	sw $t2, 0($sp)
	li $t0, 0
	
	count_loop:
	
		bge $t0, $a1, exit_count_loop
	
		add $t1, $a3, $t0
		lw $t2, 0($t1)
	
		bne $t2, $a2, continue_count_loop
		addi $t3, $t3, 1
	
		continue_count_loop:
	
		addi $t0, $t0, 4
		j count_loop
	
	exit_count_loop:
	
	lw $t2, 0($sp)
	lw $t1, 4($sp)
	lw $t0, 8($sp)
	addi $sp, $sp, 12
	jr $ra
