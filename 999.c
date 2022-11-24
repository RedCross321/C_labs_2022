#include <stdio.h>
#include <string.h>
int main()
{
    char str[256];
    printf("Строка: ");
    fgets(str, 256, stdin);
    char *bukva, *bukva2, *p;
    bukva = str;
    while( *bukva )
    {
        while( *bukva && !((*bukva >= 'a' && *bukva <= 'z') || (*bukva >= 'A' && *bukva <= 'Z')))
            putchar( *bukva++ );
        bukva2 = bukva;
        while(((*bukva2 >= 'a' && *bukva2 <= 'z') || (*bukva2 >= 'A' && *bukva2 <= 'Z')))
            bukva2++;
        p = bukva2 - 1;
        while( p >= bukva )
            putchar( *p-- );
        bukva = bukva2;
    }
//    printf("\n");
}
