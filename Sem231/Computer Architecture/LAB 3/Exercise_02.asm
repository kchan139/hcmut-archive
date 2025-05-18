.data
.eqv SYS_PRINT_INT    1
.eqv SYS_PRINT_FLOAT  2
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT     5
.eqv SYS_READ_FLOAT   6
.eqv SYS_READ_STRING  8
.eqv SYS_EXIT         10

float_0:   .float 0.0
float_1:   .float 1.0
float_3:   .float 3.0
float_4:   .float 4.0
float_5:   .float 5.0
float_10:  .float 10.0

prompt_id: .asciiz "Student ID: "
prompt_a : .asciiz "a: "
prompt_b : .asciiz "b: "
prompt_c : .asciiz "c: "
prompt_d : .asciiz "d: "
prompt_u : .asciiz "u: "
prompt_v : .asciiz "v: "
result:    .asciiz "Result: "


.text
#? s0 = e - s1 = a - s2 = b - s3 = c - s4 = d - f24 = u - f25 = v
main:
    li $v0 SYS_PRINT_STRING
    la $a0 prompt_id
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f20 $f4 $f0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_a
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f21 $f4 $f0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_b
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f22 $f4 $f0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_c
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f23 $f4 $f0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_d
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f24 $f4 $f0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_u
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f25 $f4 $f0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_v
    syscall

    lwc1 $f4 float_0
    li $v0 SYS_READ_FLOAT
    syscall
    add.s $f26 $f4 $f0

calculating:
    lwc1 $f1 float_10

    div.s $f2 $f20 $f1
    floor.w.s $f2 $f2
    cvt.s.w $f2 $f2
    mul.s $f2 $f2 $f1
    sub.s $f20 $f20 $f2
    mul.s $f20 $f20 $f20
    sub.s $f27 $f25 $f26
    mul.s $f12 $f27 $f24

    mul.s $f28 $f25 $f25
    mul.s $f28 $f28 $f25
    mul.s $f29 $f26 $f26
    mul.s $f29 $f29 $f26
    sub.s $f27 $f28 $f29
    mul.s $f13 $f27 $f23

    mul.s $f28 $f28 $f25
    mul.s $f29 $f29 $f26
    sub.s $f27 $f28 $f29
    mul.s $f14 $f27 $f22

    mul.s $f28 $f28 $f25
    mul.s $f29 $f29 $f26
    sub.s $f27 $f28 $f29
    mul.s $f15 $f27 $f21

    lwc1 $f0 float_3
    div.s $f13 $f13 $f0

    lwc1 $f0 float_4
    div.s $f14 $f14 $f0

    lwc1 $f0 float_5
    div.s $f15 $f15 $f0

    add.s $f12 $f12 $f13
    add.s $f12 $f12 $f14
    add.s $f12 $f12 $f15

    div.s $f12 $f12 $f20

print:
    li $v0 SYS_PRINT_STRING
    la $a0 result
    syscall

    li $v0 SYS_PRINT_FLOAT
    mov.s $f12 $f12
    syscall

exit:
    li $v0 SYS_EXIT
    syscall