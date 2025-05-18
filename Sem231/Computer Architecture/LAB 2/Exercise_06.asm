.data
.eqv SYS_PRINT_INT    1
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT     5
.eqv SYS_READ_STRING  8
.eqv SYS_EXIT         10

input_prompt:  .asciiz  "Enter a non-negative integer: "
result_prompt: .asciiz  "Factorial: "
error_msg:  .asciiz  "A factorial for your number can not be found"


.text
main:
    la  $a0  input_prompt
    li  $v0  SYS_PRINT_STRING
    syscall

    li  $v0  SYS_READ_INT
    syscall

    slt	 $t0  $v0  $zero		# $t0 = ($s0 < 0) ? 1 : 0
    bne  $t0  $zero  error_exit

    

    j exit

error_exit:
    la  $a0  error_msg
    li  $v0  SYS_PRINT_STRING
    syscall

exit:
	li  $v0  SYS_EXIT
	syscall