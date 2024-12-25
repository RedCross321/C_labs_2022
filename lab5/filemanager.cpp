#include "filemanager.h"
#include <iostream>

using namespace std;


void FileManager::saveToFile(const FilmDatabase& database) {
    ofstream file(currentFilename);

    if (!file) {
        cout << "\x1B[0;32mFailed to open file for writing\x1b[0m\n";
        isFileOpen = false;
        return;
    }

    isFileOpen = true;
    size_t size = database.getSize();
    const MediaContent* const* films = database.getFilms();
    file << size << endl;
    for (size_t i = 0; i < size; ++i) {
        writeFilm(file, *films[i]);
    }

    file.close();
    isFileOpen = false;
    Film::clear();
    cout << "\x1B[0;32;40mData saved succesfully\x1b[0m\n";
}

void FileManager::loadFromFile(FilmDatabase& database) {
    ifstream file(currentFilename);

    if (!file) {
        cout << "\x1B[0;32mFailed to open file for reading\x1b[0m\n";
        isFileOpen = false;
        return;
    }

    isFileOpen = true;
    size_t filmCount;
    file >> filmCount;
    file.ignore();

    MediaContent** films = new MediaContent*[filmCount];
    for (size_t i = 0; i < filmCount; ++i) {
        readFilm(file, films[i]);
    }

    database.setFilms(films, filmCount);
    delete[] films;
    file.close();
    isFileOpen = false;
}
