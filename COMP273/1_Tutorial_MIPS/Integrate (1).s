          .data
x:	 .float 0.0, 0.1, 0.2, 0.3, 0.4
xdot:	 .float 2.0, 2.0, 2.0, 2.0, 2.0
out:	 .space 20      # 5 floats
h:	 .float 0.01	# step size
space:	 .asciiz " "
newLine: .asciiz "\n"

          .text
main:
	la $a0,x
	li $a1,5
	jal printfloatarray		 

	la $a0,x
	li $a1,5
	la $a2,xdot
	la $a3,out
	l.s $f12,h	
	#la  $t1,h
	#lwc1 $f12,0($t1)
	jal integrate

	la $a0,out
	li $a1,5
	jal printfloatarray		 
		
        li $v0, 10      # load exit call code 10 into $v0
        syscall         # call operating system to exit

integrate: #( float*x, int n, float* xdot, float* out, float h )
        # no need to save anything, can do everything with temporaries!
        # recall that arguments are in $a0-$a3 and $f12 $f14 for floating point arguments.
	# &(x[])  is in $a0
	# n       is in $a1
	# &(xdot[]) is in $a2
	# &(out[]) is in $a3
	# h        is in $f12
	# Let i (a counter) be $t0

	        move $t0,$zero         # i = 0
iloop:		beq $a1,$t0,iloopdone  # done if i == n
                
	        sll  $t1,$t0,2         # compute address x[i]
	        add  $t2,$a0,$t1
	        lwc1 $f4,0($t2)        # f4 = x[i]
	        add  $t2,$a2,$t1
	        lwc1 $f6,0($t2)        # f6 = xdot[i]
	
		mul.s $f6,$f6,$f12
	        add.s $f6,$f6,$f4      # f6 = f4 + f6*f12

		add  $t2,$a3,$t1
		swc1  $f6,0($t2)       # out[i] = f6
	
	        addi $t0,$t0,1	       # increment loop counter
	        j    iloop
iloopdone:	jr   $ra

	
printfloatarray: # ( float* A, int n )
	# s0 = A  (passed in $a0)
	# s1 = n  (passed in $a1)
	# s2 = i
	add $sp,$sp,-16
	sw  $s0,0($sp)
	sw  $s1,4($sp)
	sw  $s2,8($sp)
	sw  $ra,12($sp)
	move $s0,$a0
	move $s1,$a1
	move $s2,$zero
loop:	beq $s2, $s1, loopdone
	sll $t0,$s2,2	# compute address for A[i]
	add $t0,$s0,$t0
       	lwc1 $f12,0($t0)# load A[i]
	li $v0, 2       # print float
	syscall         # call operating system to print
	li $v0, 4       # print a space
        la $a0, space   
	syscall         
	addi $s2, $s2, 1
	j loop
loopdone:
	li $v0, 4       # print a new line
        la $a0, newLine   
	syscall         			
	lw  $s0,0($sp)  # restore stack and return
	lw  $s1,4($sp)
	lw  $s2,8($sp)
	lw  $ra,12($sp)
	add $sp,$sp,16	
	jr  $ra
	

