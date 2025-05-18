.data
.eqv SYS_PRINT_INT    1
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT     5
.eqv SYS_READ_STRING  8
.eqv SYS_EXIT         10

array:          .space   28
size:           .word    7
input_prompt:   .asciiz  "Enter an integer: "
result_prompt:  .asciiz  "The result array: "
endl:           .asciiz  "\n"
space:          .asciiz  " "


.text
main:
    la  $t0  array
    lw  $t1  size

input_loop:
    li  $v0  SYS_PRINT_STRING
    la  $a0  input_prompt
    syscall

    li  $v0  SYS_READ_INT
    syscall

    sw  $v0  0($t0)
    addi  $t0  $t0  4
    subi  $t1  $t1  1
    bnez  $t1  input_loop

    la  $t0  array
    lw  $t1  size

iterate:
    lw  $t2  0($t0)
    rem  $t3  $t2  4

    beqz  $t3  divisible_by_4
    jal indivisible_by_4

    j store_result

divisible_by_4:
    div  $t2  $t2  4
    j store_result

indivisible_by_4:
    subi  $t2  $t2  1
    rem  $t3  $t2  4
    beqz  $t3  exit_ib4

    addi  $t2  $t2  2
    rem  $t3  $t2  4
    beqz  $t3  exit_ib4

    subi  $t2  $t2  3

    exit_ib4:
        jr  $ra

store_result:
    sw  $t2  0($t0)

    addi  $t0  $t0  4
    subi  $t1  $t1  1
    bnez  $t1  iterate

    la  $v0  SYS_PRINT_STRING
    la  $a0  result_prompt
    syscall

    la  $t0  array
    lw  $t1  size

print_result:
    lw  $a0  0($t0)
    li  $v0  SYS_PRINT_INT
    syscall

    li  $v0  SYS_PRINT_STRING
    la  $a0  space
    syscall

    addi  $t0  $t0  4
    subi  $t1  $t1  1   
    bnez  $t1  print_result

exit:
	li  $v0  SYS_EXIT
	syscall