###########################################################
#		Program Description

###########################################################
#		Register Usage
#	$t0
#	$t1
#	$t2
#	$t3
#	$t4
#	$t5
#	$t6
#	$t7
#	$t8
#	$t9
###########################################################
		.data

###########################################################
		.text
main:
	li $t2, -8
	lw $t1,0($t7)
	mul $t1, $t1, $t2
	sw $t1,0($t7)

	li $v0, 10		#End Program
	syscall
###########################################################

