#include "string.h"


void int_to_ascii(int n, char str[])
{
    int i, sign;

    if ((sign = n) < 0) n = -n;

    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);

}

int strlen(char str[])
{
    unsigned int count = 0;
    while(str[count]) count++;
    return count;
}

void reverse(char str[])
{
    int size = strlen(str);
    for(int i = 0; i < size/2; i++)
    {
        char temp = str[i];
        str[i] = str[size-1 - i];
        str[size-1 - i] = temp;
    }
}


void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}
