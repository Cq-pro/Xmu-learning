DATA SEGMENT
    DATA1 DB 31H,21H,42H,52H,87H,23H,98H,01H
    COUNT DB 8
    SEARCH DB 42H
    UP DB 0
    DOWN DB 0
    EQUA DB 0
    UPSTRING DB 0AH,0DH,'UP Number: $'
    DOWNSTRING DB 0AH,0DH,'Down Number: $'
    EQUASTRING DB 0AH,0DH,'Equal Number: $'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX
    MOV BX, 0
    MOV CX, 8 ; 设置循环计数器为数组的元素个数


AGAIN:
    MOV AL, [DATA1 + BX] ; 从数组中加载一个字节到AL寄存器

    CMP AL, SEARCH ; 比较AL和SEARCH
    JZ EQUAL ; 如果相等，跳转到EQUAL标签
    JA LARGER ; 如果AL大于SEARCH，跳转到LARGER标签
    JB SMALLER ; 如果AL小于SEARCH，跳转到SMALLER标签

LARGER:
    INC UP ; UP加1
    JMP NEXT_ITERATION

SMALLER:
    INC DOWN ; DOWN加1
    JMP NEXT_ITERATION

EQUAL:
    INC EQUA ; EQUA加1
    JMP NEXT_ITERATION

NEXT_ITERATION:
    INC BX ; 移动到下一个数组元素
    LOOP AGAIN ; 循环

    ; 输出结果
    MOV DX, OFFSET UPSTRING
    MOV AH, 09H
    INT 21H

    ADD UP, '0' ; 转换数字为字符
    MOV DL, UP
    MOV AH, 02H
    INT 21H

    MOV DX, OFFSET DOWNSTRING
    MOV AH, 09H
    INT 21H

    ADD DOWN, '0' ; 转换数字为字符
    MOV DL, DOWN
    MOV AH, 02H
    INT 21H

    MOV DX, OFFSET EQUASTRING
    MOV AH, 09H
    INT 21H

    ADD EQUA, '0' ; 转换数字为字符
    MOV DL, EQUA
    MOV AH, 02H
    INT 21H

    ; 退出程序
    MOV AH, 4CH
    INT 21H

CODE ENDS
    END START
