    .globl main
main:
    # input section
    ## value of a
    li $v0, 4 
    la $a0, aPrompt
    syscall
    li $v0, 6
    syscall
    mov.s $f6, $f0          #store a in $f6

    ## value of b
    li $v0, 4 
    la $a0, bPrompt
    syscall
    li $v0, 6
    syscall
    mov.s $f8, $f0           #store b in $f8

    ## value of x0
    li $v0, 4 
    la $a0, xPrompt
    syscall

    li $v0, 6
    syscall
    mov.s $f10, $f0         #store x0 in $f10

    ## value of y0
    li $v0, 4
    la $a0, yPrompt
    syscall
    li $v0, 6
    syscall
    mov.s $f16, $f0         #store y0 in $f16

    ## number of iterations
    li $v0, 4
    la $a0, nPrompt
    syscall
    li $v0, 5
    syscall
    move $t0, $v0            #store n in $t0
    
    li $v0, 4
    la $a0, lbasecase       #print (x0, y0) = (
    syscall
    li $v0, 2
    mov.s $f12, $f10        #print x0
    syscall
    li $v0, 4
    la $a0, comma           #print ,
    syscall
    
    li $v0, 2               #print y0
    mov.s $f12, $f16
    syscall

    li $v0, 4               #print )
    la $a0, cBraq
    syscall
    la $a0, newline         # print newline
    syscall

    # Counter is in $t1
    li $t1, 1
    add $t0, $t0, 1

loop:
    beq $t1, $t0, Done

    # f(x,y) = ( x^2-y^2+a , 2xy+b )
    # compute f(x,y) and new x is stored in $f10 and
    # new y is stored in $f16
    
    # x^2 
    mul.s $f20, $f10, $f10
    # y^2
    mul.s $f22, $f16, $f16
    # x^2-y^2 in $f20
    sub.s $f20, $f20, $f22

    # 2xy
    mul.s $f22, $f10, $f16
    l.s $f24, two
    mul.s $f22, $f22, $f24 

    # new x
    add.s $f10, $f20, $f6

    # new y
    add.s $f16, $f22, $f8

    li $v0, 4               # print (x
    la $a0, rBraq
    syscall
    li $v0, 1               # print counter
    move $a0, $t1
    syscall
    li $v0, 4               # print ,
    la $a0, comma
    syscall
    li $v0, 4               # print y
    la $a0, y
    syscall
    li $v0, 1               # print counter
    move $a0, $t1
    syscall
    li $v0, 4               # print ) = (
    la $a0, lBraq
    syscall
    li $v0, 2               # print xi
    mov.s $f12, $f10
    syscall
    li $v0, 4               # print comma
    la $a0, comma
    syscall
    li $v0, 2               # print yi
    mov.s $f12, $f16
    syscall
    li $v0, 4               # print )
    la $a0, cBraq
    syscall
    la $a0, newline         # print newline
    syscall



    addi $t1, $t1, 1         #increase counter by 1

    j loop

    


Done:
    li $v0, 10
    syscall
    

    .data
aPrompt: .asciiz "Enter the value of a: "
bPrompt: .asciiz "Enter the value of b: "
xPrompt: .asciiz "Enter the value of x0: "
yPrompt: .asciiz "Enter the value of y0: "
nPrompt: .asciiz "Enter the number of iterations n: "
newline: .asciiz "\n"
two: .float 2.0
lbasecase: .asciiz "(x0, y0) = ("
rBraq: .asciiz "(x"
comma: .asciiz ", "
y: .asciiz "y"
lBraq: .asciiz ") = ("
cBraq: .asciiz ")"

