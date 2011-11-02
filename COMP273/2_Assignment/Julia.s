# Jonathan Fok kan
# 260447938
# Assignment 3 MIPS
# Question 1
# Part 2

    #.globl main
main:
    # input
    ## value of a
    li $v0, 4 
    la $a0, aPrompt
    syscall
    li $v0, 6
    syscall
    mov.s $f4, $f0          #store a in $f4

    ## value of b
    li $v0, 4 
    la $a0, bPrompt
    syscall
    li $v0, 6
    syscall
    mov.s $f6, $f0           #store b in $f6

    # set outerloop counter as $t0
    li $t0, 0
    

    # load y into $f10
    l.s $f10, y

    # load x_inc into $f16
    l.s $f16, x_inc
    
    #load y_dec into $f18
    l.s $f18, y_dec

outerloop:
    beq $t0, 40, outerloopdone

    # load x into $f8
    l.s $f8, x

    # set innerloop counter as $t1
    li $t1, 0

innerloop:
    beq $t1, 80, innerloopdone

    # set julia iterations counter, n,
    # as $t2
    li $t2, 0

    # copy over x onto new temporary registers
    mov.s $f26, $f8

    # copy over y onto new temporary registers
    mov.s $f28, $f10

juliaiterations:
    
    beq $t2, 1000, bounded
        
    add $sp, $sp, -8
    swc1 $f26, 0($sp)
    swc1 $f28, 4($sp)
    
    mul.s $f26, $f26, $f26          # temp x^2
    mul.s $f28, $f28, $f28          # temp y^2
    add.s $f26, $f26, $f28

    l.s $f28, million
    c.le.s $f28, $f26
    lwc1 $f26, 0($sp)
    lwc1 $f28, 4($sp)
    add $sp, $sp, 8
    bc1t unbounded

    # x^2 
    mul.s $f20, $f26, $f26
    # y^2
    mul.s $f22, $f28, $f28
    # x^2-y^2 in $f20
    sub.s $f20, $f20, $f22

    # 2xy
    mul.s $f22, $f26, $f28
    l.s $f24, two
    mul.s $f22, $f22, $f24 

    # new x
    add.s $f26, $f20, $f4

    # new y
    add.s $f28, $f22, $f6

    # increment n
    add $t2, $t2, 1

    j juliaiterations

bounded:
    li $v0, 4
    la $a0, space
    syscall
    
    # increment x
    add.s $f8, $f8, $f16
    # increment innerloop counter
    add $t1, $t1, 1

    j innerloop

unbounded:
    li $v0, 1
    li $t3, 10
    div $t2, $t3
    mfhi $a0
    syscall

    # increment x
    add.s $f8, $f8, $f16
    # increment innerloop counter
    add $t1, $t1, 1
    j innerloop

innerloopdone:
    # increment outer loop counter
    add $t0, $t0, 1

    # decrement y
    sub.s $f10, $f10, $f18

    # print newline
    li $v0, 4
    la $a0, newline
    syscall
    j outerloop

outerloopdone:
    li $v0, 10
    syscall

    .data
aPrompt: .asciiz "Enter the value of a: "
bPrompt: .asciiz "Enter the value of b: "
newline: .asciiz "\n"
space: .asciiz " "
million: .float 1000000.0
two: .float 2.0
x: .float -2.0
x_inc: .float 0.05
y: .float 2.0
y_dec: .float 0.1
