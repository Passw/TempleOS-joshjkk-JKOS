org 0x7c00
bits 16

start:
    mov si, hello
    call puts
    jmp $

puts:
    mov ah, 0Eh
.run:
    lodsb
    cmp al, 0x00
    je .done
    int 10h
    jmp .run
.done:
    ret

hello: db "Hello JKOS!", 0x00

times 510-($-$$) db 0
dw 0xaa55