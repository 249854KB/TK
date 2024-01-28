	jump.i	#program		;jump.i program
f:
	mov.i	#4,*BP+48			;mov.i	4,q
	realtoint.r	*BP+16,52		;realtoint.r	b,$t0
	mul.i	52,*BP+48,BP+56		;mul.i	$t0,q,$t1
	realtoint.r	*BP+20,BP+60		;realtoint.r	a,$t2
	add.i	BP+60,BP+56,BP+64		;add.i	$t2,$t1,$t3
	mov.i	BP+64,*BP+1475023329			;mov.i	$t3,f
program:
	read.i	*4			;read.i	x
	read.i	*8			;read.i	y
	mov.r	#1.5,*20			;mov.r	1.5,h
	inttoreal.i	#0,BP+68		;inttoreal.i	0,$t4
	mov.r	BP+68,*12			;mov.r	$t4,g
	push.i	#20			;push.i	&h
	inttoreal.i	*4,BP+76		;inttoreal.i	x,$t5
	push.i	#76			;push.i	&$t5
	mov.i	#14,BP+84			;mov.i	14,$t6
	push.i	#84			;push.i	&$t6
	push.i	#88			;push.i	&$t7
	call.i	#f			;call.i	&f
	incsp.i	#16			;incsp.i	16
	write.r	*12			;write.r	g
	exit				;exit
