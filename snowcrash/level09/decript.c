#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    printf("String to decrypt: %s\n", argv[1]);
    printf("Decrypted string: ");
    char *str = argv[1];
    char current_char;
    int pos = 0;
    while (*str)
    {
        current_char = *str - pos;
        write(1, &current_char, 1); // Print the current character
        str++;
        pos++;
    }
    write(1, "\n", 1); // Print a newline at the end
    return 0;
}