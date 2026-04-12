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

Solucion: Como tenemos el condicional que no permite imprimir si existe la palabra token hacemos un link que apunte a token. En nuestro caso

ln -s /home/user/level08/token /var/crash/mitk

ejecutando luego ./level08 /var/crash/mitk obtenemos el token

quif5eloekouj29ke0vouxean

level08@SnowCrash:~$ su flag08
Password: quif5eloekouj29ke0vouxean
Don't forget to launch getflag !
flag08@SnowCrash:~$ getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
