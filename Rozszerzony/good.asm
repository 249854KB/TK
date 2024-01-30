        jump.i  #lbl0   ;jump.i lbl0
f:
        enter.i #28             ;enter.i        #28
        mov.i   #4,BP-4 ;mov.i  $4,$q
        inttoreal.i     BP-4,BP-12      ;inttoreal.i    $q,$t0
        mul.r   *BP+16,BP-12,BP-20      ;mul.r  $b,$t0,$t1
        add.r   *BP+20,BP-20,BP-28      ;add.r  $a,$t1,$t2
        mov.r   BP-28,*BP+8     ;mov.r  $t2,$f
        leave           ;leave
        return          ;return
lbl0:
        read.i  0       ;read.i $x
        read.i  4       ;read.i $y
        inttoreal.i     #2,24   ;inttoreal.i    $2,$t3
        mul.r   24,#3.5,32      ;mul.r  $t3,$3.5,$t4
        add.r   #1.5,32,40      ;add.r  $1.5,$t4,$t5
        mov.r   40,16   ;mov.r  $t5,$h
        inttoreal.i     #0,48   ;inttoreal.i    $0,$t6
        mov.r   48,8    ;mov.r  $t6,$g
        push.i  #16                     ;push.i &h
        inttoreal.i     0,56    ;inttoreal.i    $x,$t7
        push.i  #56                     ;push.i &t7
        mov.i   #14,64  ;mov.i  $14,$t8
        push.i  #64                     ;push.i &t8
        push.i  #68                     ;push.i &t9
        call.i  #f      ;call.i &f
        incsp.i #16     ;incsp.i        16
        realtoint.r     68,76   ;realtoint.r    $t9,$t10
        mov.i   76,0    ;mov.i  $t10,$x
        write.r 8       ;write.r        $g
        exit            ;exit
