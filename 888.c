#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <ctype.h>

int mygetch()
{
    struct termios oldt, newt;
    int c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

int main()
{
    int proverka1 = 0, proverka2 = 0;;
    char Kod1, Kod2;
    int sim = 0;
    unsigned c = 0;
    while (1)
    {
        char ch = mygetch();
        if (isprint(ch) && proverka1 == 0)
        {
            printf("%c", ch);
            c++;
            sim += ch;
        }
        else
        {
            if (ch == 0x1b)
            {
                proverka1 = 1;
                continue;
            }
            if (proverka1 == 1 && proverka2 == 0)
            {
                Kod1 = ch;
                proverka2 = 1;
            }
            else if (proverka1 == 1)
            {
                proverka1 = 0;
                proverka2 = 0;
                Kod2 = ch;
                __fpurge(stdin);
                if (Kod1 == 'O' && Kod2 == 'P')
                    break;
            }
        }
    }
    sim /= c;
    printf ("\n%c -%4d Среднее значение\n", sim, sim);
}