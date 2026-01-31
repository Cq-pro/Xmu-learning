section .data
    array dq 8, 1, 5, 2, 7, 9, 6, 4, 3, 10
    array_size equ 10
    newline db 10 ; newline character

section .text
    global _start

    _start:
        ; 升序排序
        mov rdi, array_size
        dec rdi

    ascending_loop:
        mov rax, 0
        mov rbx, 0

    ascending_inner_loop:
        mov r8, rbx
        inc r8
        cmp r8, rdi
        jge ascending_exit_inner_loop

        mov r9, [array + rbx]
        mov r10, [array + r8]

        cmp r9, r10
        jle ascending_no_swap

        ; 交换元素
        mov [array + rbx], r10
        mov [array + r8], r9

    ascending_no_swap:
        inc rbx
        jmp ascending_inner_loop

    ascending_exit_inner_loop:
        ; 输出升序排序结果
        mov rax, 1          ; syscall number for write
        mov rdi, 1          ; file descriptor for stdout
        mov rsi, array      ; pointer to the array
        mov rdx, array_size ; array length
        syscall

        ; 输出换行
        mov rax, 1          ; syscall number for write
        mov rdi, 1          ; file descriptor for stdout
        mov rsi, newline    ; pointer to the newline character
        mov rdx, 1          ; newline character length
        syscall

        ; 降序排序
        mov rdi, array_size
        dec rdi

    descending_loop:
        mov rax, 0
        mov rbx, 0

    descending_inner_loop:
        mov r8, rbx
        inc r8
        cmp r8, rdi
        jge descending_exit_inner_loop

        mov r9, [array + rbx]
        mov r10, [array + r8]

        cmp r9, r10
        jge descending_no_swap

        ; 交换元素
        mov [array + rbx], r10
        mov [array + r8], r9

    descending_no_swap:
        inc rbx
        jmp descending_inner_loop

    descending_exit_inner_loop:
        ; 输出降序排序结果
        mov rax, 1          ; syscall number for write
        mov rdi, 1          ; file descriptor for stdout
        mov rsi, array      ; pointer to the array
        mov rdx, array_size ; array length
        syscall

        ; 输出换行
        mov rax, 1          ; syscall number for write
        mov rdi, 1          ; file descriptor for stdout
        mov rsi, newline    ; pointer to the newline character
        mov rdx, 1          ; newline character length
        syscall

        ; 退出程序
        mov rax, 60         ; syscall number for exit
        xor rdi, rdi        ; exit code 0
        syscall
