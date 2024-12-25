#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "mediacontent.h"
#include "filmdatabase.h"
#include "filemanager.h"

using namespace std;

class Film;
class Series;

bool validateDatabaseSize(const FilmDatabase& db) {
    return db.size <= 100 && db.size <= db.capacity;
}

int main() {

    string filename;
    FileManager fileManager;
    FilmDatabase database;

    int choice;
    do {
        cout << "\n1. Add\n"
                  << "2. Delete film\n"
                  << "3. Print all films\n"
                  << "4. Save\n"
                  << "5. Load\n"
                  << "6. Search\n"
                  << "7. Combine films\n"
                  << "8. Multiply film\n"
                  << "9. Increment film\n"
                  << "10. Compare films\n"
                  << "11. Create Director's Cut\n"
                  << "12. Combine series\n"
                  << "0. Exit\n";
        cout << "Input: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                database.addFilm();
                break;
            case 2:
                database.deleteFilm();
                break;
            case 3:
                database.printFilms();
                break;
            case 4:
                cout << "Input file name: ";
                cin >> filename;
                fileManager.setFilename(filename + ".txt");
                fileManager.saveToFile(database);
                break;
            case 5:
                cout << "Input file name: ";
                cin >> filename;
                fileManager.setFilename(filename + ".txt");
                fileManager.loadFromFile(database);
                break;
            case 6:
                database.searchFilmByActor();
                break;
            case 7:
                database.combineFilms();
                break;
            case 8:
                database.multiplyFilm();
                break;
            case 9:
                database.incrementFilm();
                break;
            case 10:
                database.compareFilms();
                break;
            case 11:
                database.createSpecialVersion();
                break;
            case 12:
                database.compareTotalDuration();
                break;
            case 0:
                cout << "Exit...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}