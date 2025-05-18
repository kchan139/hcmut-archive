.data
string:			.space 1024
freq:			.space 512
input_prompt:	.asciiz	"Input a string: "
output_prompt:  .asciiz "Frequency: "
comma:			.asciiz ", "
semi_colon:		.asciiz "; "


.text
main:
	li $v0 4
	la $a0 input_prompt
	syscall
	
	li $v0 8
	li $a1 1024
	la $a0 string
	syscall
	move $s0 $a0

	li $t0 0
	la $s1 freq
	
init_array:
	slti $t1 $t0 512
	beqz $t1 exit_init

	add $t2 $s1 $t0
	sw $zero 0($t2)
	addi $t0 $t0 4

	j init_array

    exit_init:
        li $s2 10

count:
	lb $t0 0($s0)
	beq $t0 $s2 exit_count
	
	sll $t0 $t0 2
	add $t1 $s1 $t0
	lw $t2 0($t1)
	addi $t2 $t2 1
	sw $t2 0($t1)	
	
	addi $s0 $s0 1

	j count 

    exit_count:	
        li $t1 0
        li $v0 4
        la $a0 output_prompt
        syscall
        
        li $s3 128

print:
	li $t0 0
	li $t2 128
	li $t3 1025

	sub_print:
		slti $t1 $t0 512
		beqz $t1 exit_sub_print
	
		add $t4 $s1 $t0 
		lw $t5 0($t4)
		
		beqz $t5 not_change
		slt $t6 $t5 $t3
		beqz $t6 not_change
		srl $t2 $t0 2
		move $t3 $t5

	not_change:
		addi $t0 $t0 4
		j sub_print
		
	exit_sub_print:
	
	beq $t2 $s3 end
	
	li $v0 11
	move $a0 $t2
	syscall
	
	li $v0 4
	la $a0 comma
	syscall
	
	li $v0 1
	move $a0 $t3
	syscall
	
	li $v0 4
	la $a0 semi_colon
	syscall
	
	sll $t0 $t2 2
	add $t1 $s1 $t0
	sw $zero 0($t1)
	
	j print


end:
	li $v0 10
	syscall