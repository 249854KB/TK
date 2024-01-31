	jump.i #program                         ;jump.i program
p2:                                
	enter.i #8                              ;enter.i #8
lbl2:                              
	jl.i *BP+12,*BP+8,#lbl3                 ;jl.i i,j,lbl3
	mov.i #0,BP-4                           ;mov.i 0,$t0
	jump.i #lbl4                            ;jump.i lbl4
lbl3:                              
	mov.i #1,BP-4                           ;mov.i 1,$t0
lbl4:                              
	je.i BP-4,#0,#lbl1                      ;je.i $t0,0,lbl1
	add.i *BP+12,#1,BP-8                    ;add.i i,1,$t1
	mov.i BP-8,*BP+12                       ;mov.i $t1,i
	jump.i #lbl2                            ;jump.i lbl2
lbl1:                              
	leave                                   ;leave
	return                                  ;return
f:                                 
	enter.i #28                             ;enter.i #28
	mov.i #4,BP-4                           ;mov.i 4,q
	inttoreal.i BP-4,BP-12                  ;inttoreal.i q,$t2
	mul.r *BP+20,BP-12,BP-20                ;mul.r b,$t2,$t3
	add.r *BP+24,BP-20,BP-28                ;add.r a,$t3,$t4
	mov.r BP-28,*BP+8                       ;mov.r $t4,f
	leave                                   ;leave
	return                                  ;return
p:                                 
	enter.i #16                             ;enter.i #16
	jl.i *BP+12,*BP+8,#lbl5                 ;jl.i b,c,lbl5
	mov.i #0,BP-4                           ;mov.i 0,$t5
	jump.i #lbl6                            ;jump.i lbl6
lbl5:                              
	mov.i #1,BP-4                           ;mov.i 1,$t5
lbl6:                              
	je.i BP-4,#0,#lbl7                      ;je.i $t5,0,lbl7
	realtoint.r *BP+16,BP-8                 ;realtoint.r a,$t6
	mov.i BP-8,*BP+8                        ;mov.i $t6,c
	jump.i #lbl8                            ;jump.i lbl8
lbl7:                              
	inttoreal.i *BP+12,BP-16                ;inttoreal.i b,$t7
	mov.r BP-16,*BP+16                      ;mov.r $t7,a
lbl8:                              
	leave                                   ;leave
	return                                  ;return
program:                           
	read.i 0                                ;read.i x
	read.i 4                                ;read.i y
	inttoreal.i 0,24                        ;inttoreal.i x,$t8
	mul.r 16,24,32                          ;mul.r h,$t8,$t9
	add.r 8,32,40                           ;add.r g,$t9,$t10
	mov.r 40,16                             ;mov.r $t10,h
	mov.r #12.0,48                          ;mov.r 12.0,$t11
	push.i #48                              ;push.i &$t11
	push.i #0                               ;push.i &x
	push.i #4                               ;push.i &y
	call.i #p                               ;call.i &p
	incsp.i #12                             ;incsp.i 12
	mov.i #0,56                             ;mov.i 0,$t12
	push.i #56                              ;push.i &$t12
	mov.i #3,60                             ;mov.i 3,$t13
	push.i #60                              ;push.i &$t13
	call.i #p2                              ;call.i &p2
	incsp.i #8                              ;incsp.i 8
	push.i #16                              ;push.i &h
	inttoreal.i 0,64                        ;inttoreal.i x,$t14
	push.i #64                              ;push.i &$t14
	mov.i #14,72                            ;mov.i 14,$t15
	push.i #72                              ;push.i &$t15
	push.i #76                              ;push.i &$t16
	call.i #f                               ;call.i &f
	incsp.i #16                             ;incsp.i 16
	realtoint.r 76,84                       ;realtoint.r $t16,$t17
	mov.i 84,0                              ;mov.i $t17,x
	write.r 8                               ;write.r g
	exit                                    ;exit
