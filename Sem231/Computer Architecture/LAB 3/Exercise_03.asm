.data
.eqv SYS_PRINT_INT    1
.eqv SYS_PRINT_FLOAT  2
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT     5
.eqv SYS_READ_FLOAT   6
.eqv SYS_READ_STRING  8
.eqv SYS_DYN_ALLOC    9
.eqv SYS_OPEN_FILE    13
.eqv SYS_READ_FILE    14
.eqv SYS_CLOSE_FILE   16
.eqv SYS_EXIT         10

file_line_length: .space 1024
Name: .space 128
ID: .space 16
Weight: .space 16
Height: .space 16
Medical_condition: .space 128

file_path: .asciiz "D:/Documents/VS CODE/Computer Architecture/LAB 3/test.txt" #filename for output

warning:  .asciiz "WARNING: PLEASE SPECIFY FILE PATH BEFORE ASSEMBLING THE PROGRAM\n\n"
format_a: .asciiz "\n(a) Student Medical Information"
format_b: .asciiz "\n(b) Name: "
format_c: .asciiz "\n(c) ID: "
format_d: .asciiz "\n(d) Weight: "
format_e: .asciiz "\n(e) Height: "
format_f: .asciiz "\n(f) Medical history: "


.text
main:
    #check if file path is specified
    la $a0 warning
    li $v0 SYS_PRINT_STRING
    syscall

    li $v0  SYS_DYN_ALLOC
    li $a0  1024
    syscall
    move $s1 $v0

    li $v0 SYS_OPEN_FILE
    la $a0 file_path
    li $a1 0
    syscall
    move $s0 $v0
    
    li $v0 SYS_READ_FILE
    move $a0 $s0
    move $a1 $s1
    
    li $a2 1024
    syscall
    
    li $v0 SYS_PRINT_STRING
    move $a0 $s1
    syscall
    
    li $t1 44
    add $t2 $s1 $zero
    la $a3 ID
    add $t4 $a3 $zero
     
takeID:
    lb $t3 0($t2)	
    beq $t1 $t3  exit_takeID
    sb $t3 0($t4)
    addi $t2 $t2 1
    addi $t4 $t4 1
    j takeID
    
exit_takeID:
    addi $t2 $t2 1
    la $a3 Name
    add $t4 $a3 $zero

takeName:
    lb $t3 0 ($t2)
    beq $t1 $t3 exit_takeName
    sb $t3 0($t4)
    addi $t2 $t2 1
    addi $t4 $t4 1
    j takeName

exit_takeName:
    addi $t2 $t2 1
    la $a3 Weight
    add $t4 $a3 $zero

takeWeight:
    lb $t3 0($t2)
    beq $t3 $t1 exit_Weight
    sb $t3 0($t4)
    addi $t2 $t2 1
    addi $t4 $t4 1
    j takeWeight

exit_Weight:
    addi $t2 $t2 1
    la $a3 Height
    add $t4 $a3 $zero

takeHeight:
    lb $t3 0($t2)
    beq $t3 $t1 exit_takeHeight
    sb $t3 0($t4)
    addi $t2 $t2 1
    addi $t4 $t4 1
    j takeHeight

exit_takeHeight:
    addi $t2 $t2 1
    li $t1 46
    la $a3 Medical_condition
    add $t4 $a3 $zero

takeHealth:            
    lb $t3 0($t2)
    beq $t3 $t1 print
    sb $t3 0($t4)
    addi $t2 $t2 1
    addi $t4 $t4 1
    j takeHealth

print:
    li $v0 SYS_PRINT_STRING
    la $a0 format_a
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 format_b
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 Name
    syscall                
    
    li $v0 SYS_PRINT_STRING
    la $a0 format_c
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 ID
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 format_d
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 Weight
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 format_e
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 Height
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 format_f
    syscall
    
    li $v0 SYS_PRINT_STRING
    la $a0 Medical_condition
    syscall      
        
    #close the file
    li $v0 SYS_CLOSE_FILE
    move $a0 $s0
    syscall
    		
exit_program:
    li $v0 10
    syscall
