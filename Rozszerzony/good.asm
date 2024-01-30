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
        inttoreal.i     0,24    ;inttoreal.i    $x,$t3
        mul.r   16,24,32        ;mul.r  $h,$t3,$t4
        add.r   8,32,40 ;add.r  $g,$t4,$t5
        mov.r   40,16   ;mov.r  $t5,$h
        push.i  #16                     ;push.i &h
        inttoreal.i     0,48    ;inttoreal.i    $x,$t6
        push.i  #48                     ;push.i &t6
        mov.i   #14,56  ;mov.i  $14,$t7
        push.i  #56                     ;push.i &t7
        push.i  #60                     ;push.i &t8
        call.i  #f      ;call.i &f
        incsp.i #16     ;incsp.i        16
        realtoint.r     60,68   ;realtoint.r    $t8,$t9
        mov.i   68,0    ;mov.i  $t9,$x
        write.r 8       ;write.r        $g
        exit            ;exit