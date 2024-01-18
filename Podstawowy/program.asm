	jump.i	#program		;jump.i program
program:
	mov.i	#0,0			;mov.i	$0,$x
	realtoint.r	#13.3,4		;realtoint.r	$13.3,$y
	mov.i	#13.3,4			;mov.i	$13.3,$y
	inttoreal.i	#12,16		;inttoreal.i	$12,$h
	mov.r	#12,16			;mov.r	$12,$h
	realtoint.r	16,4		;realtoint.r	$h,$y
	mov.i	16,4			;mov.i	$h,$y
	mul.i	4,16,24			;mul.i	$y,$h,$t0
	add.i	0,24,28			;add.i	$x,$t0,$t1
	inttoreal.i	28,8		;inttoreal.i	$t1,$g
	mov.r	28,8			;mov.r	$t1,$g
	write.r	8			;write.r	$g
	exit				;exit
