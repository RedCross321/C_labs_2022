#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio_ext.h>
#include <string.h>
/***************/

#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <iomanip>

/************************************************Структура и базированый код****************************************************/

using namespace std;

struct film
{
    char *name;
    char *country;
    char *rez;
    char *gg;
    int year;
};

struct film *database = NULL;
int nomer1 = 0;

void free_film(struct film* film);
void write_file(struct film* db, int nomer1, const char* filename);
int read_file(struct film** db, int nomer1, const char* filename);
void color(int n);
void menu();
void start();
void danet(int m);
void danet1(int m);
void free_db(struct film** db, int nomer1);
void print_found(struct film db[], int nomer1);
void print(struct film db[], int nomer1);
void opred(int n);




int mygetch()
{
    struct termios oldt, newt;
    int c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

/*******************************************************************************************************************************/

/************************************************Добавление или удаление********************************************************/

void dobav(struct film *nenew)
{
    char *name = new char(200);
    char *country = new char(200);
    char *rez = new char(200);
    char *gg = new char(200);
    int year;
    
    //!!!!!!!
    //!!!!!!
    //!!!!!!!
    //!!!!!!!

    system("clear");
    cout << "\x1B[5;32mВведите название :\x1b[0m ";
    //fgets(name, 200, stdin);
    cin.getline(name, 200);

    name[strlen(name)-1] = 0;
    cout << "\x1B[5;32mВведите страну:\x1b[0m ";
    //fgets(country, 200, stdin);
    cin.getline(country, 200);


    country[strlen(country)-1] = 0;
    cout << "\x1B[5;32mРежиссера:\x1b[0m ";
    //fgets(rez, 200, stdin);
    cin.getline(rez, 200);

    rez[strlen(rez)-1] = 0;
    cout << "\x1B[5;32mГлавный актер:\x1b[0m ";
    //fg5ets(gg, 200, stdin);
    cin.getline(gg, 200);
    
    gg[strlen(gg)-1] = 0;
    cout << "\x1B[5;32mВведите год :\x1b[0m ";
    cin >> year;

    nenew->name = name;
    nenew->country = country;
    nenew->rez = rez;
    nenew->gg = gg;
    nenew->year = year;
}

int dob_film(struct film **db, int nomer1)
{
    
    db = (film**)realloc(*db, (nomer1 + 1) * sizeof(struct film));


    if (NULL == db)
    {
       cout << "Не удалось выделить память!\n";
        exit(EXIT_FAILURE);
    }

    struct film *new_film = &(*db)[nomer1++];
    system("clear");
    dobav(new_film);
    system("clear");
   cout << "\x1B[5;32mФильм внесен в список\x1b[0m\n";
   cout << "\x1B[5;32mХотите добавить ещё один?\x1b[0m\n";
    return nomer1;
}

int delete_film(struct film** db, int nomer1, int poz)
{
    system("clear");
    
    if (nomer1 <= 0)
        return 0;

    free_film(&(*db)[poz]);

    nomer1--;
    struct film* new_loc = (film*)malloc( nomer1 * sizeof(struct film) );
    size_t glue_offset = poz * sizeof(struct film);

    memcpy(new_loc, *db, glue_offset);
    if (poz + 1 <= nomer1)
        memcpy(new_loc + poz, *db + poz + 1, nomer1 * sizeof(struct film) - glue_offset);

    *db = new_loc;
   cout << "\r\x1B[0;32;40mФильм успешно удален\x1b[0m\n";
   cout << "\x1B[0;30;42mВыйти в меню\x1b[0m";
    return nomer1;
}

void free_film(struct film* film)
{
    free(film->name);
    free(film->country);
    free(film->rez);
    free(film->gg);
    film->name = NULL;
    film->country = NULL;
    film->rez = NULL;
    film->gg = NULL;
}

/*******************************************************************************************************************************/

/************************************************Управление numpad'ом***********************************************************/

int main()
{
    system("clear");
    menu();
    int n = 0;
    color(0);
    while (1)
    {
        char answer;
        answer = mygetch();
        switch (answer)
        {
        case '8':
            if ((n - 1) >= 0)
                n--;
            color(n);
            break;
        case '2':
            if (6 > (n + 1))
                n++;
            color(n);
            break;
        case '5':
            opred(n);
            break;
        default:
            color(n);
            break;
        }
        __fpurge(stdin);
    }
}

int podvert(int m)
{
    while (1)
    {
        char answer;
        answer = mygetch();
        switch (answer)
        {
        case '4':
            if (m > 6)
               cout << "\r\x1B[0;30;42mВыйти в меню\x1b[0m";
            if ((m - 1) >= 0 && m < 5)
                m--;
            danet(m);
            break;
        case '6':
            if (m > 6)
               cout << "\r\x1B[0;30;42mВыйти в меню\x1b[0m";
            if (2 > (m + 1))
                m++;
            danet(m);
            break;
        case '5':
            if (m == 0)
                opred(0);
            else if (m == 10)
                color(1);
            else if (m == 11)
                color(2);
            else if (m == 7)
                color(3);
            else if (m == 8)
                color(4);
            else
                color(0);
            return 0;
            break;
        default:
            danet(m);
            if (m > 6)
               cout << "\r\x1B[0;30;42mВыйти в меню\x1b[0m";
            break;
        }
        __fpurge(stdin);
    }
}

int fast(int m, int g)
{
    char file[] = "film.txt";
    while (1)
    {
        char answer;
        answer = mygetch();
        switch (answer)
        {
        case '4':
            if ((m - 1) >= 0 && m < 5)
                m--;
            danet1(m);
            break;
        case '6':
            if (2 > (m + 1))
                m++;
            danet1(m);
            break;
        case '5':
            if (m == 0 && g == 5)
                start();
            else if (m == 1 && g == 5)
            {
                system("clear");
                exit(0);
            }
            else if (m == 0 && g == 10)
            {
                system("clear");
                opred(6);
            }
            else if (m == 1 && g == 10)
                color(0);
            else if (m == 0 && g == 15)
            {
                write_file(database, nomer1, file);
                system("clear");
            }
            else
            {
                system("clear");
                exit(0);
            }
            return 0;
            break;
        default:
            danet1(m);
            break;
        }
        __fpurge(stdin);
    }
}

/*******************************************************************************************************************************/

/************************************************Управление менюшкой************************************************************/
int prok = 0;

void opred(int n)
{
    char file[] = "film.txt";
    if (n == 6)
        nomer1 = read_file(&database, nomer1, file);
    if (n == 0)
    {
        prok = 0;
        nomer1 = dob_film(&database, nomer1);
        podvert(0);
    }
    if (n == 1)
    {
        prok = 0;
        system("clear");
        int poz;
       cout << "\x1B[0;32mВведите № фильма, который хотите удалить: \x1b[0m";
        scanf("%d", &poz);
        if (!(poz <= 0 || poz > nomer1))
        {
            nomer1 = delete_film(&database, nomer1, poz - 1);
            podvert(10);
        }
        else
        {
            system("clear");
           cout << "\x1B[0;32mНет фильма с таким номером\x1b[0m\n";
           cout << "\x1B[0;30;42mВыйти в меню\x1b[0m";    
            podvert(10);
        }
    }
    if (n == 2)
    {
        prok++;
        write_file(database, nomer1, file);
       cout << "\x1B[0;30;42mВыйти в меню\x1b[0m";
        podvert(11);
    }
    if (n == 3)
    {
        print(database, nomer1);
        podvert(7);
    }
    if (n == 4)
    {
        print_found(database, nomer1);
        podvert(8);       
    }
    if (n == 5)
    {
        if(prok == 0)
        {
            system("clear");
           cout << "\x1B[0;32;40m  Вы не сохранили последнии изменения. Сохранить сейчас?   \n";
           cout << "                   \x1b[0m\x1B[0;30;42mДА\x1b[0m\x1B[0;30;40m";
           cout << "         \x1b[0m\x1B[0;32;40mНЕТ                          \x1b[0m";
            fast(0, 15);
        }
        system("clear");
        exit(0);        
    }
}

/*******************************************************************************************************************************/

/************************************************Вывод списка на экран**********************************************************/

void print_film(struct film nenew)
{
   cout << "\x1B[0;32;40m" 
   << setw(30) << nenew.name << "|" 
   << setw(20) << nenew.country << "|" 
   << setw(28) << nenew.rez << "|" 
   << setw(30) << nenew.gg << "|" 
   << setw(4) << nenew.year;
}

void print(struct film db[], int nomer1)
{
    system("clear");
   cout << "\x1B[0;32;40m  № | Название                     | Страна             | Режиссер                    | Главный актер                |Год  \x1b[0m\n";
   cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";
    for (int i = 0; i < nomer1; i++)
    {
       cout << "\x1B[0;32;40m" << setw(4) << i + 1 << "|\x1b[0m";
        print_film(db[i]);
       cout << endl;
    }
   cout << "\r\x1B[0;30;42mВыйти в меню\x1b[0m";
}

void print_found(struct film db[], int nomer1)
{
    system("clear");
    int k = 0;
   cout << "\x1B[0;32;40mВведите имя актера: \x1b[0m";
    char named[256];
    fgets(named, 256, stdin);
    named[strlen(named)-1] = 0;
    system("clear");
   cout << "\x1B[0;32;40m  № | Название                     | Страна             | Режиссер                    | Главный актер                |Год  \x1b[0m\n";
   cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";
    for (int i = 0; i < nomer1; i++)
    {
        if (strcmp(named, db[i].gg) == 0)
        {
            k++;
           cout << "\x1B[0;32;40m" << setw(4) << i + 1 << "|\x1b[0m";
            print_film(db[i]);
           cout << endl;
        }
    }
    if (k == 0)
    {
        system("clear");
       cout << "\x1B[0;32mНе найдено фильмов с данным актером или его имя введено не правильно(\x1b[0m\n";
    }
   cout << "\r\x1B[0;30;42mВыйти в меню\x1b[0m";
}

/*******************************************************************************************************************************/

/************************************************Работа с файлом****************************************************************/

void write_file(struct film* db, int nomer1, const char* filename)
{
    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", nomer1);
    for (int i = 0; i < nomer1; i++)
    {
        fprintf(file, "%s\n%s\n%s\n%s\n%d\n", db[i].name, db[i].country, db[i].rez, db[i].gg, db[i].year);
    }
    fclose(file);
    system("clear");
   cout << "\x1B[0;32;40mДанные успешно сохранены\x1b[0m\n";
}

int read_file(struct film** db, int nomer1, const char* filename)
{
    if (*db != NULL)
        free_db(db, nomer1);

    FILE* file = fopen(filename, "r");
    if (NULL == file)
    {
        *db = NULL;
       cout << "\x1B[0;30;42mфайл %s не найден.\x1b[0m\n", filename;
        return 0;
    }

    nomer1 = 0;
    fscanf(file, "%d", &nomer1);
    *db = (film*)malloc(nomer1 * sizeof(struct film));
    for (int i = 0; i < nomer1; i++)
    {
        struct film* s = &(*db)[i];

        char* trash = new char(5);    
        char* name = new char(200);
        char* country = new char(200);
        char* rez = new char(200);
        char* gg = new char(200);

        fgets(trash, 5, file);
        fgets(name, 200, file);
        name[strlen(name)-1] = 0;
        fgets(country, 200, file);
        country[strlen(country)-1] = 0;
        fgets(rez, 200, file);
        rez[strlen(rez)-1] = 0;
        fgets(gg, 200, file);
        gg[strlen(gg)-1] = 0;
        //cin >> file;

        fscanf(file, "%d", &s->year);
        s->name = name;
        s->country = country;
        s->rez = rez;
        s->gg = gg;
    }
    return nomer1;
}

void free_db(struct film** db, int nomer1)
{
    for (int i = 0; i < nomer1; i++)
        free_film(db[i]);

    free(*db);
    *db = NULL;
}

/*******************************************************************************************************************************/

/************************************************Графическое оформление*********************************************************/

void menu()
{
   cout << "\x1B[1;32;40m              ПРИЛОЖЕНИЕ ДЛЯ ЗАПИСИ ФИЛЬМОВ                \x1b[0m\n";
   cout << "\x1B[0;32;40m                         />     フ                         \x1b[0m\n";
   cout << "\x1B[0;32;40m                        |   _  _ |                         \x1b[0m\n";
   cout << "\x1B[0;32;40m                        / ミ _x 彡                         \x1b[0m\n";
   cout << "\x1B[0;32;40m                       /        |                          \x1b[0m\n"; 
   cout << "\x1B[0;32;40m                      /         ﾉ                          \x1b[0m\n";
   cout << "\x1B[0;32;40m                   ／￣|    | | |                          \x1b[0m\n";
   cout << "\x1B[0;32;40m                  | (￣ヽ__ヽ_)_)                          \x1b[0m\n";
   cout << "\x1B[0;32;40m                   ＼二つ                                  \x1b[0m\n";
   cout << "\x1B[0;32;40m                   Начать работу?                          \n";
   cout << "                   \x1b[0m\x1B[0;30;42mДА\x1b[0m\x1B[0;30;40m";
   cout << "         \x1b[0m\x1B[0;32;40mНЕТ                          \x1b[0m";
    fast(0, 5);
}

void start()
{
    system("clear");
   cout << "\x1B[0;32;40m           Открыть файл для редактирования?                \n      В противном случае данные будут переписаны.          \n";
   cout << "                   \x1b[0m\x1B[0;30;42mДА\x1b[0m\x1B[0;30;40m";
   cout << "         \x1b[0m\x1B[0;32;40mНЕТ                          \x1b[0m";    
    fast(0, 10);
}

void color(int n)
{
    system("clear");
    if (n == 0)
    {
       cout << "\x1B[0;30;42mВнести фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mУдалить фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mСохранить записи в файл.\x1b[0m\n";
       cout << "\x1B[0;32;40mВывести все фильмы.\x1b[0m\n";
       cout << "\x1B[0;32;40mУзнать фильм(-ы) с участием конкретного актера.\x1b[0m\n";
       cout << "\x1B[0;32;40mВыход.\x1b[0m\n";
    }
    if (n == 1)
    {
       cout << "\x1B[0;32;40mВнести фильм.\x1b[0m\n";
       cout << "\x1B[0;30;42mУдалить фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mСохранить записи в файл.\x1b[0m\n";
       cout << "\x1B[0;32;40mВывести все фильмы.\x1b[0m\n";
       cout << "\x1B[0;32;40mУзнать фильм(-ы) с участием конкретного актера.\x1b[0m\n";
       cout << "\x1B[0;32;40mВыход.\x1b[0m\n";
    }
    if (n == 2)
    {
       cout << "\x1B[0;32;40mВнести фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mУдалить фильм.\x1b[0m\n";
       cout << "\x1B[0;30;42mСохранить записи в файл.\x1b[0m\n";
       cout << "\x1B[0;32;40mВывести все фильмы.\x1b[0m\n";
       cout << "\x1B[0;32;40mУзнать фильм(-ы) с участием конкретного актера.\x1b[0m\n";
       cout << "\x1B[0;32;40mВыход.\x1b[0m\n";
    }
    if (n == 3)
    {
       cout << "\x1B[0;32;40mВнести фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mУдалить фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mСохранить записи в файл.\x1b[0m\n";
       cout << "\x1B[0;30;42mВывести все фильмы.\x1b[0m\n";
       cout << "\x1B[0;32;40mУзнать фильм(-ы) с участием конкретного актера.\x1b[0m\n";
       cout << "\x1B[0;32;40mВыход.\x1b[0m\n";
    }
    if (n == 4)
    {
       cout << "\x1B[0;32;40mВнести фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mУдалить фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mСохранить записи в файл.\x1b[0m\n";
       cout << "\x1B[0;32;40mВывести все фильмы.\x1b[0m\n";
       cout << "\x1B[0;30;42mУзнать фильм(-ы) с участием конкретного актера.\x1b[0m\n";
       cout << "\x1B[0;32;40mВыход.\x1b[0m\n";
    }
    if (n == 5)
    {
       cout << "\x1B[0;32;40mВнести фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mУдалить фильм.\x1b[0m\n";
       cout << "\x1B[0;32;40mСохранить записи в файл.\x1b[0m\n";
       cout << "\x1B[0;32;40mВывести все фильмы.\x1b[0m\n";
       cout << "\x1B[0;32;40mУзнать фильм(-ы) с участием конкретного актера.\x1b[0m\n";
       cout << "\x1B[0;30;42mВыход.\x1b[0m\n";
    }
}

void danet1(int m)
{
    if (m == 0)
       cout << "\r\x1B[0;32;40m                   \x1b[0m\x1B[0;30;42mДА\x1b[0m\x1B[0;32;40m         \x1b[0m\x1B[0;32;40mНЕТ\x1b[0m";
    if (m == 1)
       cout << "\r\x1B[0;32;40m                   ДА         \x1b[0m\x1B[0;30;42mНЕТ\x1b[0m";
}

void danet(int m)
{
    if (m == 0)
    {
       cout << "\r\x1B[0;32m\x1B[0;30;42mДА\x1b[0m";
       cout << "         \x1B[0;32;40mНЕТ\x1b[0m";
    }
    if (m == 1)
    {
       cout << "\r\x1B[0;32mДА";
       cout << "         \x1b[0m\x1B[0;30;42mНЕТ\x1b[0m";
    }
}

/*******************************************************************************************************************************/
