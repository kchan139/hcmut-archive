.data
.eqv SYS_PRINT_INT 1
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT 5
.eqv SYS_READ_STRING 8
.eqv SYS_EXIT 10

input_prompt: .asciiz "Please enter two positive integers: "
gcd_result:   .asciiz "GCD: "
lcm_result:   .asciiz "LCM: "
error_msg:    .asciiz "You entered a negative number. Please restart!"
endl:         .asciiz "\n"


.text
main:
	li 			$v0  SYS_PRINT_STRING
	la 			$a0  input_prompt
	syscall
	
	li 			$v0  SYS_READ_INT
	syscall
	move 		$t0  $v0
	
	slt 		$t7  $t0  $zero
	beq 		$t7  1  exit_negative
	
	li 			$v0  SYS_READ_INT
	syscall 
	move 		$t1  $v0

	slt 		$t7  $t1  $zero
	beq 		$t7  1  exit_negative
	
	move	 	$a0  $t0
	move 		$a1  $t1
	
	jal 		GCD
	move 		$t2  $v0
	move 		$t3  $v0
	
	li 			$v0  SYS_PRINT_STRING
	la 			$a0  gcd_result
	syscall 
	
	li 			$v0  SYS_PRINT_INT
	move 		$a0  $t2
	syscall
	
	li 			$v0  SYS_PRINT_STRING
	la 			$a0  endl
	syscall
	
	mul 		$t4  $t0  $t1
	div 		$t4  $t3
	mflo		$t3
	
	li 			$v0  SYS_PRINT_STRING
	la 			$a0  lcm_result
	syscall 
	
	li 			$v0  SYS_PRINT_INT
	move 		$a0  $t3
	syscall
	
	li 			$v0  SYS_PRINT_STRING
	la 			$a0  endl
	syscall
	
	j 			exit

GCD:
	addi	 	$sp  $sp  -4
	sw 			$ra  0($sp)
	
	bne 		$a1  $zero  L1
	move 		$v0  $t0
	addi 		$sp  $sp  4
	jr 			$ra

L1:
	div 		$a0  $a1
	move 		$a0  $a1
	mfhi 		$a1
	jal 		GCD

	move 		$v0  $a0
	lw 			$ra  0($sp)
	addi 		$sp  $sp  4

	jr 			$ra
	
exit:
	li 			$v0  SYS_EXIT
	syscall


exit_negative:
	li 			$v0  SYS_PRINT_STRING
	la 			$a0  error_msg
	syscall
	
	li 			$v0  SYS_EXIT
	syscall