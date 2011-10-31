.globl		main
main:	#start of code section
	#load the adress of the message
	#into the $a0 register. Then load 4 into
	
	#the $v0 register to tell the processor
	#that you want to print a string.
	la $a0, hello_msg
	li $v0, 4
	syscall
	
	la $t1, test
	la $a0, 0($t1)
	syscall
	
	la $a0, 2($t1)
	syscall
	
	# Now da a graceful exit
	li $v0, 10
	syscall
	
		.data	# Data declaration section
hello_msg: .asciiz "Hello World!\n", "this is 2"
test: .asciiz "a", "b"

# End of program
