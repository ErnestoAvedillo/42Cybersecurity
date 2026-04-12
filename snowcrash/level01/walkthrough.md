## Level 01

```bash
cat /etc/passwd
(mucho texto)
level01:x:2001:2001::/home/user/level01:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

Vemos que hay un usuario para flag 1 y lo que parece ser una contraseña

```bash
echo -n "42hDRfypTqqnw" > pass_snow.txt
john --incremental pass_snow.txt
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 64/64])
Will run 8 OpenMP threads
Warning: MaxLen = 13 is too large for the current hash type, reduced to 8
Press 'q' or Ctrl-C to abort, almost any other key for status
abcdefg          (?)
1g 0:00:00:02 0.4329g/s 1326Kp/s 1326Kc/s 1326KC/s cecifel..abbalet
Use the "--show" option to display all of the cracked passwords reliably
Session completed
john --show pass_snow.txt
?:abcdefg
1 password hash cracked, 0 left
```

```bash
su flag01
Password: abcdefg
Don't forget to launch getflag !
getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
```