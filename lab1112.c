#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Computer_ {
    char processor[128];
    int vram;
    int vdisk;
    char video_adapter[128];
    int cost;
    int purchase_year;
} Computer;

void inputComputer(Computer* comp) {
    printf("Процессор     : ");
    scanf("%128s", comp->processor); fflush(stdin);
    printf("Объём оперативной памяти, GB  : ");
    scanf("%d", &comp->vram); fflush(stdin);
    printf("Объём жёсткого диска, GB : ");
    scanf("%d", &comp->vdisk); fflush(stdin);
    printf("Видеоадаптер    : ");
    scanf("%128s", comp->video_adapter); fflush(stdin);
    printf("Цена          : ");
    scanf("%d", &comp->cost); fflush(stdin);
    printf("Год закупки : ");
    scanf("%d", &comp->purchase_year); fflush(stdin);
}

void printComputer(Computer* comp) {
    printf("Процессор     : %s\n", comp->processor);
    printf("Объём оперативной памяти, GB  : %d\n", comp->vram);
    printf("Объём жёсткого диска, GB : %d\n", comp->vdisk);
    printf("Видеоадаптер  : %s\n", comp->video_adapter);
    printf("Цена          : %d\n", comp->cost);
    printf("Год закупки   : %d\n", comp->purchase_year);
}

void fromStrComputer(Computer* comp, char* str) {
    strcpy(comp->processor, strtok(str, "#"));
    comp->vram = atoi(strtok(NULL, "#"));
    comp->vdisk = atoi(strtok(NULL, "#"));
    strcpy(comp->video_adapter, strtok(NULL, "#"));
    comp->cost = atoi(strtok(NULL, "#"));
    comp->purchase_year = atoi(strtok(NULL, "#"));
}

void toStrComputer(Computer* comp, char* str) {
    sprintf(str, "%s#%d#%d#%s#%d#%d",
            comp->processor,
            comp->vram,
            comp->vdisk,
            comp->video_adapter,
            comp->cost,
            comp->purchase_year);
}


typedef struct ComputerList_ {
    int alloc;
    int size;
    Computer** comps;
} ComputerList;

void initComputerList(ComputerList* list) {
    list->alloc = 0;
    list->size = 0;
    list->comps = NULL;
}

void freeComputerList(ComputerList* list) {
    for (int i = 0; i < list->size; ++i) {
        free(list->comps[i]);
    }
    if (list->comps) {
        free(list->comps);
    }
    initComputerList(list);
}

void resizeComputerList(ComputerList* list) {
    list->alloc = list->alloc ? list->alloc * 2 : 1;
    Computer** olds = list->comps;
    list->comps = (Computer**)malloc(list->alloc * sizeof(Computer));
    for (int i = 0; i < list->size; ++i) {
        list->comps[i] = olds[i];
    }
    free(olds);
}

int sizeComputerList(ComputerList* list) {
    return list->size;
}

void addComputerList(ComputerList* list, Computer* comp) {
    if (list->size == list->alloc) {
        resizeComputerList(list);
    }
    list->comps[list->size++] = comp;
}

void addInComputerList(ComputerList* list) {
    Computer* comp = (Computer*)malloc(sizeof(Computer));
    inputComputer(comp);
    addComputerList(list, comp);
}

void removeFromComputerList(ComputerList* list, int pos) {
    free(list->comps[pos]);
    for (int i = pos; i + 1 < list->size; ++i) {
        list->comps[i] = list->comps[i + 1];
    }
    --list->size;
}

int max(int a, int b) {
    return a < b ? b : a;
}

void printUpdateComputerList(ComputerList* list, int year) {
    int pos;
    for (pos = 0; pos < list->size; ++pos) {
        if (list->comps[pos]->purchase_year <= year) {
            break;
        }
    }
    if (pos == list->size) {
        printf("Обновления не требуются!\n");
        return;
    }

    int plen = 9, vlen = 13;
    for (int i = pos; i < list->size; ++i) {
        plen = max(plen, strlen(list->comps[i]->processor));
        vlen = max(vlen, strlen(list->comps[i]->video_adapter));
    }

    char stars[512];
    int stars_len = plen + vlen + 58;
    for (int i = 0; i < stars_len; ++i) {
        stars[i] = '*';
    }
    stars[stars_len] = '\0';

    printf(" %s\n", stars);
    printf("| %2s | %*s | %9s | %9s | %*s | %9s | %9s |\n",
           "#", plen, "Процессор", "ОП, GB   ", "ЖД, GB   ",
           vlen, "Видеокарта   ", "Цена     ", "Год      "
    );
    printf(" %s\n", stars);
    for (int i = pos, cnt = 0; i < list->size; ++i) {
        if (list->comps[i]->purchase_year > year) {
            continue;
        }
        ++cnt;
        printf("| %2d | %*s | %9d | %9d | %*s | %9d | %9d |\n",
           cnt, plen, list->comps[i]->processor,
           list->comps[i]->vram, list->comps[i]->vdisk,
           vlen, list->comps[i]->video_adapter,
           list->comps[i]->cost, list->comps[i]->purchase_year
        );
    }
    printf(" %s\n", stars);
}

void printComputerList(ComputerList* list) {
    printUpdateComputerList(list, 2000000000);
}

void readComputerList(ComputerList* list, char fname[]) {
    FILE* file = fopen(fname, "r");
    if (!file) {
        return;
    }
    Computer* comp;
    char buffer[512];
    while (fgets(buffer, 512, file)) {
        comp = (Computer*)malloc(sizeof(Computer));
        fromStrComputer(comp, buffer);
        addComputerList(list, comp);
    }
    fclose(file);
}

void writeComputerList(ComputerList* list, char fname[]) {
    FILE* file = fopen(fname, "w");
    char buffer[512];
    for (int i = 0; i < list->size; ++i) {
        toStrComputer(list->comps[i], buffer);
        fprintf(file, "%s\n", buffer);
    }
    fclose(file);
}


void printCommands() {
    printf("1) Добавить информацию\n");
    printf("2) Вывести всю информацию\n");
    printf("3) Удалить информацию\n");
    printf("4) Проверить обновления\n");
    printf("0) Выйти\n");
    printf("\n>> ");
}

int main() {
    printf("\n");
    char file[] = "computer.txt";
    int command, number, year;
    ComputerList list;
    initComputerList(&list);

    readComputerList(&list, file);
    do {
        printCommands();
        scanf("%d", &command); fflush(stdin);
        switch (command) {
        case 1:
            printf("\nВведите информацию о компьютере:\n");
            addInComputerList(&list);
            printf("\nИнформация обновленна!\n\n");
            break;
        case 2:
            if (sizeComputerList(&list) == 0) {
                printf("\nСписок пуст!\n\n");
                break;
            }
            printf("\nСписок компьютеров:\n");
            printComputerList(&list);
            printf("\n");
            break;
        case 3:
            if (sizeComputerList(&list) == 0) {
                printf("\nСписок пуст!\n\n");
                break;
            }
            printf("\nВведите номер[1, %d] -> ", sizeComputerList(&list));
            scanf("%d", &number); fflush(stdin);
            if (number < 1 || number > sizeComputerList(&list)) {
                printf("\nНеправильный номер!\n\n");
                break;
            }
            removeFromComputerList(&list, number - 1);
            printf("\nИНформация удаленна\n\n");
            break;
        case 4:
            if (sizeComputerList(&list) == 0) {
                printf("\nСписок пуст!\n\n");
                break;
            }
            printf("\nВведите год -> ");
            scanf("%d", &year); fflush(stdin);
            printf("\nКомпьютеры для обновления:\n");
            printUpdateComputerList(&list, year);
            printf("\n");
            break;
        case 0:
            printf("\nРабота завершина!\n\n");
            break;
        default:
            printf("\nНеверная команда!\n\n");
            break;
        }
    } while (command != 0);

    writeComputerList(&list, file);
    freeComputerList(&list);
    return 0;
}
