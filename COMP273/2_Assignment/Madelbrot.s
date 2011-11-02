    .globl main
main:
    # set outerloop counter as $t0
    li $t0, 0
    
    # load b into $f6
    l.s $f6, b_

    # load increment of a into $f16
    l.s $f16, a_inc

    # load decrement of b into $f18
    l.s $f18, b_dec

outerloop:
    beq $t0, 40, outerloopdone

    # load a into $f4
    l.s $f4, a

    # set innerloop counter as $t1
    li $t1, 0

innerloop:
    beq $t1, 80, innerloopdone

    # load x into $f8
    l.s $f8, zero

    # load y into $f10
    l.s $f10, zero

    # set julia iterations counter, n,
    # as $t2
    li $t2, 0

juliaiterations:
    
    beq $t2, 1000, bounded
        
    # load x and y into $f26 and $f28 temporarily
    mov.s $f26, $f8
    mov.s $f28, $f10

    mul.s $f26, $f26, $f26          # temp x^2
    mul.s $f28, $f28, $f28          # temp y^2
    add.s $f26, $f26, $f28

    l.s $f28, million
    c.le.s $f28, $f26
    bc1t unbounded


    # x^2 in $f20
    mul.s $f20, $f8, $f8
    # y^2 in $f22
    mul.s $f22, $f10, $f10
    # x^2-y^2 in $f20
    sub.s $f20, $f20, $f22

    # 2xy in $f22
    mul.s $f22, $f8, $f10
    l.s $f24, two
    mul.s $f22, $f22, $f24 

    # new x
    add.s $f8, $f20, $f4

    # new y
    add.s $f10, $f22, $f6

    # increment n
    add $t2, $t2, 1

    j juliaiterations

bounded:
    li $v0, 4
    la $a0, space
    syscall
    
    # increment a
    add.s $f4, $f4, $f16

    # increment innerloop counter
    add $t1, $t1, 1
    j innerloop

unbounded:
    li $v0, 1
    li $t3, 10
    div $t2, $t3
    mfhi $a0
    syscall

    # increment a
    add.s $f4, $f4, $f16

    # increment innerloop counter
    add $t1, $t1, 1
    j innerloop

innerloopdone:
    # increment outer loop counter
    add $t0, $t0, 1

    # decrement b
    sub.s $f6, $f6, $f18

    # print newline
    li $v0, 4
    la $a0, newline
    syscall
    j outerloop

outerloopdone:
    li $v0, 10
    syscall

    .data
newline: .asciiz "\n"
space: .asciiz " "
million: .float 1000000.0
two: .float 2.0
a: .float -2.0
b_: .float 1.5
a_inc: .float 0.0375
b_dec: .float 0.075
zero: .float 0.0
