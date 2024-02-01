	jump.i #program                         ;jump.i program
program:                           
	mul.i #2,#3,36                          ;mul.i 2,3,$t0
	div.i 36,#4,40                          ;div.i $t0,4,$t1
	add.i #1,40,44                          ;add.i 1,$t1,$t2
	inttoreal.i 44,48                       ;inttoreal.i $t2,$t3
	mov.r 48,0                              ;mov.r $t3,x
	mul.i #2,#3,56                          ;mul.i 2,3,$t4
	inttoreal.i 56,60                       ;inttoreal.i $t4,$t5
	div.r 60,#4.0,68                        ;div.r $t5,4.0,$t6
	inttoreal.i #1,76                       ;inttoreal.i 1,$t7
	add.r 76,68,84                          ;add.r $t7,$t6,$t8
	mov.r 84,8                              ;mov.r $t8,y
	write.r 0                               ;write.r x
	write.r 8                               ;write.r y
	mov.i #4,24                             ;mov.i 4,i
	mov.i #5,28                             ;mov.i 5,j
	div.i 24,28,92                          ;div.i i,j,$t9
	mul.i 28,24,96                          ;mul.i j,i,$t10
	add.i 92,96,100                         ;add.i $t9,$t10,$t11
	mod.i 28,24,104                         ;mod.i j,i,$t12
	add.i 100,104,108                       ;add.i $t11,$t12,$t13
	sub.i 28,24,112                         ;sub.i j,i,$t14
	add.i 108,112,116                       ;add.i $t13,$t14,$t15
	mov.i 116,32                            ;mov.i $t15,k
	write.i 32                              ;write.i k
	jg.i 32,#10,#lbl1                       ;jg.i k,10,lbl1
	mov.i #0,120                            ;mov.i 0,$t16
	jump.i #lbl2                            ;jump.i lbl2
lbl1:                              
	mov.i #1,120                            ;mov.i 1,$t16
lbl2:                              
	je.i 120,#0,#lbl3                       ;je.i $t16,0,lbl3
	inttoreal.i #10,124                     ;inttoreal.i 10,$t17
	mov.r 124,16                            ;mov.r $t17,z
	jump.i #lbl4                            ;jump.i lbl4
lbl3:                              
	inttoreal.i #5,132                      ;inttoreal.i 5,$t18
	mov.r 132,16                            ;mov.r $t18,z
lbl4:                              
	write.r 16                              ;write.r z
	mov.i #0,24                             ;mov.i 0,i
	mov.i #1,28                             ;mov.i 1,j
	mov.i #3,32                             ;mov.i 3,k
	and.i 28,32,140                         ;and.i j,k,$t19
	or.i 24,140,144                         ;or.i i,$t19,$t20
	je.i 144,#0,#lbl5                       ;je.i $t20,0,lbl5
	write.i #1                              ;write.i 1
	jump.i #lbl6                            ;jump.i lbl6
lbl5:                              
	write.i #0                              ;write.i 0
lbl6:                              
lbl8:                              
	jl.i 24,32,#lbl9                        ;jl.i i,k,lbl9
	mov.i #0,148                            ;mov.i 0,$t21
	jump.i #lbl10                           ;jump.i lbl10
lbl9:                              
	mov.i #1,148                            ;mov.i 1,$t21
lbl10:                             
	je.i 148,#0,#lbl7                       ;je.i $t21,0,lbl7
	write.i 24                              ;write.i i
	add.i 24,#1,152                         ;add.i i,1,$t22
	mov.i 152,24                            ;mov.i $t22,i
	jump.i #lbl8                            ;jump.i lbl8
lbl7:                              
	inttoreal.i #6,156                      ;inttoreal.i 6,$t23
	mod.r #5.0,156,164                      ;mod.r 5.0,$t23,$t24
	mov.r 164,0                             ;mov.r $t24,x
	write.r 0                               ;write.r x
	exit                                    ;exit
