; Add number in memory

.386
.MODEL FLAT

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

.STACK 4096

.DATA
Value DWORD -1

.CODE
_start:
    xchg ebx, ecx
    xchg Value, eax
    xchg dl, dh
    xchg ah, bl
    xchg eax, edx
            
    INVOKE  ExitProcess, 0

PUBLIC _start

END