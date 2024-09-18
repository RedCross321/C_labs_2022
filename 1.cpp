#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef struct Computer_ {
    char processor[128];
    int vram;
    int vdisk;
    char video_adapter[128];
    int cost;
    int purchase_year;
} Computer;

typedef struct ComputerList_ {
    int alloc;
    int size;
    Computer** comps;
} ComputerList;

void toStrComputer(Computer* comp, char* str) {
    sprintf(str, "%s#%d#%d#%s#%d#%d",
            comp->processor,
            comp->vram,
            comp->vdisk,
            comp->video_adapter,
            comp->cost,
            comp->purchase_year);
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

void printUpdateComputerList(ComputerList* list, int year) {
    int pos;
    for (pos = 0; pos < list->size; ++pos) {
        if (list->comps[pos]->purchase_year <= year) {
            break;
        }
    }
    if (pos == list->size) {
        cout << "Обновления не требуются!\n";
        return;
    }

    int plen = 9, vlen = 13;
    for (int i = pos; i < list->size; ++i) {
        plen = max(plen, (int)strlen(list->comps[i]->processor));
        vlen = max(vlen, (int)strlen(list->comps[i]->video_adapter));
    }

    char stars[512];
    int stars_len = plen + vlen + 58;
    for (int i = 0; i < stars_len; ++i) {
        stars[i] = '*';
    }
    stars[stars_len] = '\0';

    cout << stars << endl;
    cout << "| # | %*s | %9s | %9s | %*s | %9s | %9s |\n",
           "#", plen, "Процессор", "ОП, GB   ", "ЖД, GB   ",
           vlen, "Видеокарта   ", "Цена     ", "Год      "
    ;
    cout << stars << endl;
    for (int i = pos, cnt = 0; i < list->size; ++i) {
        if (list->comps[i]->purchase_year > year) {
            continue;
        }
        ++cnt;
        cout << cnt << endl;
        cout << plen << endl;
        cout << list->comps[i]->processor << endl;
        cout << list->comps[i]->vram << endl;
        cout << list->comps[i]->vdisk << endl;
        cout << vlen << endl;
        cout << list->comps[i]->video_adapter << endl;
        cout << list->comps[i]->cost << endl;
        cout << list->comps[i]->purchase_year << endl;


        // cout << "| %2d | %*s | %9d | %9d | %*s | %9d | %9d |\n",
        //    cnt, plen, list->comps[i]->processor,
        //    list->comps[i]->vram, list->comps[i]->vdisk,
        //    vlen, list->comps[i]->video_adapter,
        //    list->comps[i]->cost, list->comps[i]->purchase_year
        // ;
    }
    cout << " %s\n", stars;
}

void printComputerList(ComputerList* list) {
    printUpdateComputerList(list, 2000000000);
}

void printCommands() {
    cout << "1) Добавить информацию" << endl;
    cout << "2) Вывести всю информацию" << endl;
    cout << "3) Удалить информацию" << endl;
    cout << "4) Проверить обновления" << endl;
    cout << "0) Выйти" << endl;
    cout << ">> ";
}
void inputComputer(Computer* comp) {
    cout << "Процессор     : ";
    cin >> comp->processor;
    fflush(stdin);
    cout << "Объём оперативной памяти, GB  : ";
    cin >> comp->vram; 
    fflush(stdin);
    cout << "Объём жёсткого диска, GB : ";
    cin >> comp->vdisk; 
    fflush(stdin);
    cout << "Видеоадаптер    : ";
    scanf("%128s", comp->video_adapter); 
    fflush(stdin);
    cout << "Цена          : ";
    cin >> comp->cost; 
    fflush(stdin);
    cout << "Год закупки : ";
    cin >> comp->purchase_year; 
    fflush(stdin);
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



void fromStrComputer(Computer* comp, char* str) {
    strcpy(comp->processor, strtok(str, "#"));
    comp->vram = atoi(strtok(NULL, "#"));
    comp->vdisk = atoi(strtok(NULL, "#"));
    strcpy(comp->video_adapter, strtok(NULL, "#"));
    comp->cost = atoi(strtok(NULL, "#"));
    comp->purchase_year = atoi(strtok(NULL, "#"));
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



int sizeComputerList(ComputerList* list) {
    return list->size;
}


int main() {
    cout << endl;
    char file[] = "computer.txt";
    int command, number, year;
    ComputerList list;
    initComputerList(&list);

    readComputerList(&list, file);
    do {
        printCommands();
        cin >> command; 
        fflush(stdin);
        switch (command) {
        case 1:
            cout << "\nВведите информацию о компьютере:\n";
            addInComputerList(&list);
            cout << "\nИнформация обновленна!\n\n";
            break;
        case 2:
            if (sizeComputerList(&list) == 0) {
                cout << "\nСписок пуст!\n\n";
                break;
            }
            cout << "\nСписок компьютеров:\n";
            printComputerList(&list);
            cout << endl;
            break;
        case 3:
            if (sizeComputerList(&list) == 0) {
                cout << "\nСписок пуст!\n\n";
                break;
            }
            cout << "\nВведите номер[1, %d] -> ", sizeComputerList(&list);
            
            cin >> number;
            fflush(stdin);

            if (number < 1 || number > sizeComputerList(&list)) {
                cout << "\nНеправильный номер!\n\n";
                break;
            }
            removeFromComputerList(&list, number - 1);
            cout << "\nИНформация удаленна\n\n";
            break;

        case 4:
            if (sizeComputerList(&list) == 0) {
                cout << "\nСписок пуст!\n\n";
                break;
            }
            cout << "\nВведите год -> ";
            cin >> year; 
            
            fflush(stdin);
            cout << "\nКомпьютеры для обновления:\n";


            printUpdateComputerList(&list, year);


            cout << endl;
            break;
        case 0:
            cout << "\nРабота завершина!\n\n";
            break;
        default:
            cout << "\nНеверная команда!\n\n";
            break;
        }
    } while (command != 0);

    writeComputerList(&list, file);
    freeComputerList(&list);
    return 0;
}