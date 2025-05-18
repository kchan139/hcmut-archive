.data
.eqv SYS_PRINT_INT    1
.eqv SYS_PRINT_FLOAT  2
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT     5
.eqv SYS_READ_FLOAT   6
.eqv SYS_READ_STRING  8
.eqv SYS_EXIT         10

float_0: .float 0.0
float_1: .float 1.0
float_2: .float 2.0
float_3: .float 3.0
float_4: .float 4.0
float_5: .float 5.0
float_6: .float 6.0
float_1_third: .float 0.333333333
float_const_prism: .float 0.4330127019
float_const_sphere: .float 1.3333333333
float_pi: .float 3.14159265
float_pi_over_4: .float 12.5663706

prompt_metric: .asciiz "Metric options: [1]-meters [2]-centimeters\n"
prompt_shape:  .asciiz "Shape options: \n[1]: Rectangular box\n[2]: Cube\n[3]: Cylinder\n[4]: Pyramid\n[5]: Prism\n[6]: Sphere\n"

box_l:   .asciiz "\nLength: "
box_w:   .asciiz "\nWidth: "
box_h:   .asciiz "\nHeight: "

cube_s:  .asciiz "\nSide: "

cyl_r:   .asciiz "\nRadius: "
cyl_h:   .asciiz "\nHeight: "

pyr_b:   .asciiz "\nBase: "
pyr_h:   .asciiz "\nHeight: "

prism_b: .asciiz "\nBase: "
prism_h: .asciiz "\nHeight: "

sphere_r: .asciiz "\nRadius: "

result_volume: .asciiz "\nVolume: "
result_area:   .asciiz "\nTotal surface area: "


.text
main:
    li $v0 SYS_PRINT_STRING
    la $a0 prompt_metric
    syscall

    li $v0 SYS_READ_INT
    syscall
    move $s0 $v0

    li $v0 SYS_PRINT_STRING
    la $a0 prompt_shape
    syscall

    li $v0 SYS_READ_INT
    syscall
    move $s1 $v0

    beq $s1 1 box
    beq $s1 2 cube
    beq $s1 3 cylinder
    beq $s1 4 pyramid
    beq $s1 5 prism
    beq $s1 6 sphere

    j exit

box:
    li $v0 SYS_PRINT_STRING
	la $a0 box_l
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f20 $f4 $f0

	li $v0 SYS_PRINT_STRING
	la $a0 box_w
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f21 $f4 $f0

	li $v0 SYS_PRINT_STRING
	la $a0 box_h
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f22 $f4 $f0

	mul.s $f24 $f20 $f21
	mul.s $f23 $f24 $f22
	mul.s $f21 $f21 $f22
	mul.s $f20 $f20 $f22
	add.s $f22 $f20 $f21
	add.s $f22 $f22 $f24
	add.s $f22 $f22 $f22

    j print_result

cube:
    li $v0 SYS_PRINT_STRING
    la $a0 cube_s
    syscall
    li $v0 SYS_READ_FLOAT
    syscall
    
    mul.s $f23 $f0 $f0
    mul.s $f23 $f23 $f0

    lwc1 $f22 float_6
    mul.s $f1 $f0 $f0
    mul.s $f1 $f1 $f22

    j print_result

cylinder:
    # Calculate volume and surface area for a cylinder
    li $v0 SYS_PRINT_STRING
    la $a0 cyl_r
    syscall

    lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f21 $f4 $f0

	li $v0 SYS_PRINT_STRING
	la $a0 cyl_h
	syscall

    lwc1 $f20 float_pi
	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f22 $f4 $f0

	mul.s $f23 $f21 $f21
	mul.s $f24 $f21 $f22
	add.s $f24 $f23 $f24
	mul.s $f23 $f23 $f20
	mul.s $f24 $f24 $f20
	mul.s $f23 $f23 $f22
	add.s $f22 $f24 $f24

    j print_result

pyramid:
    lwc1 $f20 float_1_third
	lwc1 $f25 float_2

	li $v0 SYS_PRINT_STRING
	la $a0 pyr_b
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f21 $f4 $f0

	li $v0 SYS_PRINT_STRING
	la $a0 pyr_h
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f22 $f4 $f0
	mul.s $f23 $f21 $f21
	mul.s $f23 $f23 $f22
	mul.s $f23 $f23 $f20

	div.s $f24 $f21 $f25   
	mul.s $f26 $f22 $f22   
	mul.s $f27 $f24 $f24	
	add.s $f24 $f26 $f27  
	mul.s $f26 $f21 $f21  
	sqrt.s $f24 $f24
	mul.s $f24 $f24 $f21
	mul.s $f24 $f24 $f25
	add.s $f22 $f24 $f26

    j print_result

prism:
    lwc1 $f20 float_const_prism
	lwc1 $f25 float_3

	li $v0 SYS_PRINT_STRING
	la $a0 prism_b
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f21 $f4 $f0

	li $v0 SYS_PRINT_STRING
	la $a0 prism_h
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f24 $f4 $f0

	mul.s $f23 $f21 $f21
	mul.s $f23 $f23 $f20
	add.s $f22 $f23 $f23
	mul.s $f23 $f23 $f24
	mul.s $f21 $f21 $f24
	mul.s $f21 $f21 $f25
	add.s $f22 $f22 $f21

    j print_result

sphere:
    lwc1 $f20 float_const_sphere
	lwc1 $f21 float_4
	lwc1 $f22 float_pi
	li $v0 SYS_PRINT_STRING
	la $a0 sphere_r
	syscall

	lwc1 $f4 float_0
	li $v0 SYS_READ_FLOAT
	syscall
	add.s $f23 $f4 $f0

	mul.s $f22 $f22 $f23
	mul.s $f22 $f22 $f23
	mul.s $f23 $f22 $f23
	mul.s $f22 $f22 $f21
	mul.s $f23 $f23 $f20

    j print_result

print_result:
    # Print volume
    li $v0 SYS_PRINT_STRING
    la $a0 result_volume
    syscall

    li $v0 SYS_PRINT_FLOAT
    mov.s $f12 $f23
    syscall

    # Print surface area
    li $v0 SYS_PRINT_STRING
    la $a0 result_area
    syscall

    li $v0 SYS_PRINT_FLOAT
    mov.s $f12 $f22
    syscall

exit:
    li $v0 SYS_EXIT
    syscall