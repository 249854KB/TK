	jump.i	#program		;jump.i program
f:
	enter.i	#28			;enter.i	#28
	mov.i	#4,BP+0			;mov.i	4,q
	inttoreal.i	BP+0,BP-12		;inttoreal.i	q,$t0
	mul.r	*BP+16,BP-12,BP-20		;mul.r	b,$t0,$t1
	add.r	*BP+20,BP-20,BP-28		;add.r	a,$t1,$t2
	mov.r	BP-28,*BP+8			;mov.r	$t2,f
	leave			;leave
	return			;return
p:
	enter.i	#16			;enter.i	#16
	jl.i	*BP+12,*BP+8,#lbl1		;jl.i	b,c,lbl1
	mov.i	#0,BP-4			;mov.i	0,$t3
	jump.i	#lbl2				;jump.i	lbl2
lbl1:
	mov.i	#1,BP-4			;mov.i	1,$t3
lbl2:
	je.i	BP-4,#0,#lbl3		;je.i	$t3,0,lbl3
	realtoint.r	*BP+16,BP-8		;realtoint.r	a,$t4
	mov.i	BP-8,*BP+8			;mov.i	$t4,c
	jump.i	#lbl4				;jump.i	lbl4
lbl3:
	inttoreal.i	*BP+12,BP-16		;inttoreal.i	b,$t5
	mov.r	BP-16,*BP+16			;mov.r	$t5,a
lbl4:
	leave			;leave
	return			;return
program:
	read.i	0			;read.i	x
	read.i	4			;read.i	y
	inttoreal.i	0,24		;inttoreal.i	x,$t6
	mul.r	16,24,32		;mul.r	h,$t6,$t7
	add.r	8,32,40		;add.r	g,$t7,$t8
	mov.r	40,16			;mov.r	$t8,h
	mov.r	#12.0,48			;mov.r	12.0,$t9
	push.i	#48			;push.i	&$t9
	push.i	#0			;push.i	&x
	push.i	#4			;push.i	&y
	call.i	#p			;call.i	&p
	incsp.i	#12			;incsp.i	12
	push.i	#16			;push.i	&h
	inttoreal.i	0,56		;inttoreal.i	x,$t10
	push.i	#56			;push.i	&$t10
	mov.i	#14,64			;mov.i	14,$t11
	push.i	#64			;push.i	&$t11
	push.i	#68			;push.i	&$t12
	call.i	#f			;call.i	&f
	incsp.i	#16			;incsp.i	16
	realtoint.r	68,76		;realtoint.r	$t12,$t13
	mov.i	76,0			;mov.i	$t13,x
	write.r	8			;write.r	g
	exit				;exit
