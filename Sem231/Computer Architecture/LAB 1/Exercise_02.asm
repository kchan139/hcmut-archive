.data
.eqv SYS_PRINT_INT 1
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT 5
.eqv SYS_READ_STRING 8
.eqv SYS_EXIT 10

array: .space 80
size: .word 20
prompt1: .asciiz "Enter an integer: "
prompt2: .asciiz "The reversed array is: \n"
endl: .asciiz "\n"
space: .asciiz " "

.text
main:
    li $t0, 0
    la $s0, array
    la $s1, array

inputLoop:
    beq $t0, 20, printReverse

    la $a0, prompt1
    li $v0, SYS_PRINT_STRING
    syscall

    li $v0, SYS_READ_INT
    syscall

    sw $v0, 0($s1)  
    addi $s1, $s1, 4
    addi $t0, $t0, 1

    j inputLoop

printReverse:
    la $a0, prompt2
    li $v0, SYS_PRINT_STRING
    syscall

    loop:
        addi $s1, $s1, -4

        lw $a0, 0($s1)  
        li $v0, SYS_PRINT_INT
        syscall

        la $a0, space
        li $v0, SYS_PRINT_STRING
        syscall

        beq $s1, $s0, exit

        j loop


exit:
    li $v0, SYS_EXIT
    syscall