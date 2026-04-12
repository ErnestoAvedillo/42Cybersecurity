## Level09
hay 2 ficheros level09 y token
Descompilo level09 y veo en el código lo siguiente:

...
    var_31 = 0xffffffff;
    while (true) {
        var_31++;
        var_32 = argv + 4;
        var_33 = *var_32;
        counter = -1;
        while (counter != 0) {
            var_34 = var_33 + 1;
            counter--;
            if (!(*var_33 != 0)) {
                break;
            }
            var_33 = var_34;
        }
        if (var_31 >= ~argc - 1) {
            break;
        }
        putchar(/* c */ (int)*(var_31 + *var_32) + var_31);
    }
    var_29 = stdout;
    var_30 = fputc(/* c */ 10, /* fp */ var_29);
...

Es so es un codificador que lo que hace sendillamente es añadir a cada carácter su posición en el string:
por ejemplo 00000 pasa a ser 012345

por lo tanto el string de token se tiene que decodificar. Para ello he preparado un código que se encuentra e decript.c

se ejecuta con:

./a.out $(cat level09_token_recibido.pcap )
String to decrypt: f4kmm6p|=�p�n��DB�Du{��
f3iji1ju5yuevaus41q1afiuq

Nota, los ficheros los he descargado el virtual

posterior mente en la máquina virtual introduzco el código
level09@SnowCrash:~$ su flag09
Password: f3iji1ju5yuevaus41q1afiuq
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
