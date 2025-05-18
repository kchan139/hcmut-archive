.data
string_prompt1: .asciiz  "Enter the first number: "
string_prompt2: .asciiz  "Enter the second number: "

string_prompt3: .asciiz  "Choose an operation ('1' for addition, '2' for subtraction, '3' for multiplication, '4' for division): "
string_result: .asciiz   "Result: "

string_errormsg: .asciiz "Divide-by-0 ERROR"


.text
main:
    ori $v0, $zero, 4
    la $a0, string_prompt1
    syscall

    ori $v0, $zero, 5
    syscall
    add $t0, $zero, $v0

    ori $v0, $zero, 4
    la $a0, string_prompt2
    syscall

    ori $v0, $zero, 5
    syscall
    add $t1, $zero, $v0

    ori $v0, $zero, 4
    la $a0, string_prompt3
    syscall

    ori $v0, $zero, 5
    syscall
    
    beq $v0, 1, addition
    beq $v0, 2, subtraction
    beq $v0, 3, multiplication
    beq $v0, 4, division

addition:
    addu $t2, $t0, $t1
    j print_result

subtraction:
    subu $t2, $t0, $t1
    j print_result

multiplication:
    multu $t0, $t1 
	mflo	$t2 
	j print_result 

division:
	beq $t1, $zero, exception
	div $t0, $t1
	j print_result 

print_result:
	ori	$v0, $zero, 4 
	la	$a0, string_result
	syscall 

	add	$a0, $zero, $t2 
	ori	$v0, $zero, 1 
	syscall
	
	j exit
	
exception:
	ori $v0, $zero, 4
    la $a0, string_errormsg
    syscall

exit:
   ori   $v0, $zero, 10
   syscall
