	jump.i	#program		;jump.i program
program:
	mov.i	#0,0			;mov.i	0,x
	realtoint.r	#13.3,24		;realtoint.r	13.3,$t0
	mov.i	24,4			;mov.i	$t0,y
	inttoreal.i	#12,28		;inttoreal.i	12,$t1
	mov.r	28,16			;mov.r	$t1,h
	inttoreal.i	4,36		;inttoreal.i	y,$t2
	mul.r	36,16,44			;mul.r	$t2,h,$t3
	inttoreal.i	0,52		;inttoreal.i	x,$t4
	add.r	52,44,60			;add.r	$t4,$t3,$t5
	mov.r	60,8			;mov.r	$t5,g
	write.r	8			;write.r	g
	exit				;exit
