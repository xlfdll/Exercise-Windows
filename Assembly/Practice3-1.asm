; Add number in memory

.386
.MODEL FLAT

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

.STACK 4096

.DATA
Value DWORD -1

.CODE
_start:
    mov ebx, ecx
    mov eax, 100
    mov edx, Value
    mov ah, 0
    mov al, -1
    mov Value, ebx
    mov ecx, 128
            
    INVOKE  ExitProcess, 0

PUBLIC _start

END