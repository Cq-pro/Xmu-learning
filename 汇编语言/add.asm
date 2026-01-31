stacks segment STACK
    DW 128 DUP(?)
stacks ends
datas segment
    DB 10H, 11H, 12H, 13H, 14H, 15H, 16H, 17H
datas ends
codes segment
    assume cs:codes,ds:datas
start:
    mov ax, datas
    mov ds, ax
    XOR ax,ax
    mov bx,0
    mov cx,8
    JCXZ done
sign: 
    ADC AL,[BX]
    INC BX
    loop sign
done:
    mov dx,ax
    mov ax,4C00H
    int 21H
codes ends
end start