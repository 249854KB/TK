	jump.i	#program		;jump.i program
f:
	enter.i	#28			;enter.i	#28
	mov.i	#4,BP-4			;mov.i	4,q
	realtoint.r	*BP+16,BP-8		;realtoint.r	b,$t0
	mul.i	BP-8,BP-4,BP-12		;mul.i	$t0,q,$t1
	realtoint.r	*BP+20,BP-16		;realtoint.r	a,$t2
	add.i	BP-16,BP-12,BP-20		;add.i	$t2,$t1,$t3
	inttoreal.i	BP-20,BP-28		;inttoreal.i	$t3,$t4
	mov.r	BP-28,*BP+8			;mov.r	$t4,f
	leave			;leave
	return			;return
program:
	read.i	0			;read.i	x
	read.i	4			;read.i	y
	inttoreal.i	#2,24		;inttoreal.i	2,$t5
	mul.r	24,#3.5,32		;mul.r	$t5,3.5,$t6
	add.r	#1.5,32,40		;add.r	1.5,$t6,$t7
	mov.r	40,16			;mov.r	$t7,h
	inttoreal.i	#0,48		;inttoreal.i	0,$t8
	mov.r	48,8			;mov.r	$t8,g
	push.i	#16			;push.i	&h
	inttoreal.i	0,56		;inttoreal.i	x,$t9
	push.i	#56			;push.i	&$t9
	mov.i	#14,64			;mov.i	14,$t10
	push.i	#64			;push.i	&$t10
	push.i	#68			;push.i	&$t11
	call.i	#f			;call.i	&f
	incsp.i	#16			;incsp.i	16
	realtoint.r	68,76		;realtoint.r	$t11,$t12
	mov.i	76,0			;mov.i	$t12,x
	write.r	8			;write.r	g
	exit				;exit
