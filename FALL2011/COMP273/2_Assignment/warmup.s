    .text
    .globl main

main:
    add $sp, $sp, -8
    sw $s0, 0($sp)
    sw $s1, 4($sp)


    li $s0, 41              #contains the index for the outer loop

loopOUT:
    beq $s1, $zero, DONE
    li $s1, 81              #contains the index for the inner loop

loopIN:
    #Do stuff
    add $s0, $s0, -1        #decrement the index of the outer loop
    beq $s0, $zero, loopOUT

printA:
    la $t0, ACST
    li $v0, 4
    la $a0, $t0
    syscall
    jr $ra

printC:
    la $t0, 2(ACST)
    li $v0, 4
    la $a0, $t0
    syscall
    jr $ra

printS:
    la $t0, 4(ACST)
    li $v0, 4
    la $a0, $t0
    syscall
    jr $ra

printT:
    la $t0, 6(ACST)
    li $v0, 4
    la $a0, $t0
    syscall
    jr $ra

printNL:
    la $t0, newline
    li $v0, 4
    la $a0, $t0
    syscall
    jr $ra

DONE:
    add $sp, $sp, 8
    lw $s0, 0($sp)
    lw $s1, 4($sp)
    li $v0, 10
    syscall

    .data
ACST: .asciiz "A","C","S","T"
newline: .asciiz "\n"
x: .float -2.0
x_inc: .float 0.05
y: .float 2.0
y_dec: .float 0.1
