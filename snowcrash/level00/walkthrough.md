## Level 00

```bash
cat /etc/passwd
(mucho texto)
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
level00:x:2000:2000::/home/user/level00:/bin/bash
```

Vemos que hay un usuario para flag y otro para level (estamos en level) , por lo que vamos a ver que archivos puede tener la flag

```bash
find / -user flag00 2>/dev/null
/usr/sbin/john
/rofs/usr/sbin/john
```

Para encontrar el siguiente nivel he hecho un find / -user flag00 2>/dev/null
conel que me salen los siguientes ficheros

```bash
ll /rofs/usr/sbin/john
----r--r-- 1 flag00 flag00 15 Mar  5  2016 /rofs/usr/sbin/john
```

Vemos que tiene un archivo de 15 bytes por lo que vamos a abrirlo

```bash
cat /rofs/usr/sbin/john
cdiiddwpgswtgt
```

Parece una contraseña cifrada
Pensando en distintas formas de cifrar vemos que usando ROT encontramos una solucion
[ROT-N to calculate the rotations](https://www.rot-n.com)

cdiiddwpgswtgt -> ROT11 -> nottoohardhere

```bash
su flag00
Password:
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```