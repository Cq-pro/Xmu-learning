movl $0x1, 0xc(%esp)      ; 将立即数0x1存储到栈指针(esp)偏移12字节处
movl $0xffffffff, 0x8(%esp)   ; 将立即数0xffffffff存储到栈指针(esp)偏移8字节处

mov 0x8(%esp), %eax        ; 将栈指针(esp)偏移8字节处的值加载到寄存器eax中
and %eax, 0xc(%esp)        ; 将eax寄存器的值与栈指针(esp)偏移12字节处的值进行逻辑与操作，并将结果存储回栈中

mov 0x8(%esp), %eax        ; 将栈指针(esp)偏移8字节处的值加载到寄存器eax中
or %eax, 0xc(%esp)         ; 将eax寄存器的值与栈指针(esp)偏移12字节处的值进行逻辑或操作，并将结果存储回栈中
