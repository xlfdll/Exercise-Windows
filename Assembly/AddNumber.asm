; Add number in memory

.386
.MODEL FLAT

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

.STACK 4096

.DATA
number DWORD -105
sum    DWORD ?

.CODE
_start:
    mov     eax, number
    add     eax, 158
    mov     sum, eax

    INVOKE  ExitProcess, 0

PUBLIC _start

END