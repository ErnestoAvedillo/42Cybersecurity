#include <stdio.h>
#include <unistd.h>

void main()
{
  char *str = "cdiiddwpgswtgt";
  char c;
  for (int j = -2; j < 15; j++)
  {
    for (int i = 0; str[i] != '\0'; i++)
    {
      if (str[i] + j > 122) // Restar 26 para mantenerlo dentro del rango de caracteres ASCII
        c = str[i] - 26;
      else
        c = str[i];
      c += j; // Restar 1 al carácter
      write(1, &c, 1);
    }
    printf("\n");
  }
  printf("\n%s\n", str);
}
