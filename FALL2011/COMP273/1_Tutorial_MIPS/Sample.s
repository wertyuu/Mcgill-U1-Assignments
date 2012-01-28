#actual start of the main program
#to print out the length of string  "Hello World"

		.text
		.globl main
main:	
		la	$t2,str
		li	$t0,0			# store the constant 0 in $t0
                li    $t1,0

nextCh:		lb	$t0,($t2)
                beqz  $t0,strEnd
		add 	$t1,$t1,1
		add $t2,$t2,1
		
		j	nextCh

strEnd:		li	$v0, 4		#print_str (system call 4)
		la	$a0, ans		# takes the address of string as an argument 
		syscall	
		
		move $a0,$t1
		li	$v0, 1		#print_str (system call 4)
		syscall	
		
		li	$v0, 4		#print_str (system call 4)
		la	$a0, endl		# takes the address of string as an argument 
		syscall	

		li	$v0,10
		syscall

          .data
str:		.asciiz "Hello World"	#string to print
ans:		.asciiz "Length is "     #message
endl: 	.asciiz "\n"
