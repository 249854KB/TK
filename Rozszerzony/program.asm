	jump.i	#program		;jump.i program
f:
	enter.i	#28			;enter.i	#28
	mov.i	#4,BP-4			;mov.i	4,q
	inttoreal.i	BP-4,BP-12		;inttoreal.i	q,$t0
	mul.r	*BP+16,BP-12,BP-20		;mul.r	b,$t0,$t1
	add.r	*BP+20,BP-20,BP-28		;add.r	a,$t1,$t2
	mov.r	BP-28,*BP+8			;mov.r	$t2,f
	leave			;leave
	return			;return
p:
	enter.i	#12			;enter.i	#12
	realtoint.r	*BP+16,BP-4		;realtoint.r	a,$t3
	mov.i	BP-4,*BP+8			;mov.i	$t3,c
	inttoreal.i	*BP+12,BP-12		;inttoreal.i	b,$t4
	mov.r	BP-12,*BP+16			;mov.r	$t4,a
	leave			;leave
	return			;return
program:
	read.i	0			;read.i	x
	read.i	4			;read.i	y
	inttoreal.i	0,24		;inttoreal.i	x,$t5
	mul.r	16,24,32		;mul.r	h,$t5,$t6
	add.r	8,32,40		;add.r	g,$t6,$t7
	mov.r	40,16			;mov.r	$t7,h
	mov.r	#12.0,48			;mov.r	12.0,$t8
	push.i	#48			;push.i	&$t8
	push.i	#0			;push.i	&x
	push.i	#4			;push.i	&y
	call.i	#p			;call.i	&p
	incsp.i	#12			;incsp.i	12
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
