#include <cstring>
#include <fstream>
#include <iostream>
#include "mediacontent.h"
#include "film.h"
#include "series.h"
#include "miniseries.h"
#include "filmdatabase.h"


#ifndef FILEMANAGER_H
#define FILEMANAGER_H


class FileManager {
private:
    std::string currentFilename;
    bool isFileOpen;

    void writeFilm(std::ostream& file, const MediaContent& film) {
        file << film.getName() << "\n"
             << film.getCountry() << "\n"
             << film.getDirector() << "\n"
             << film.getYear() << "\n"
             << film.getType() << "\n";
        film.writeSpecificData(file);
    }

    void readFilm(std::istream& file, MediaContent*& film) {
        std::string name, country, director, type;
        int year;

        getline(file, name);
        getline(file, country);
        getline(file, director);
        file >> year;
        file.ignore();
        getline(file, type);

        if (type == "Film") {
            film = new Film();
        } else if (type == "Series") {
            film = new Series();
        } else if (type == "MiniSeries") {
            film = new MiniSeries();
        }

        film->setName(name);
        film->setCountry(country);
        film->setDirector(director);
        film->setYear(year);
        film->readSpecificData(file);
    }
public:
    FileManager() : currentFilename(""), isFileOpen(false) {}
    FileManager(const std::string& filename) : currentFilename(filename), isFileOpen(false) {}

    void setFilename(const std::string& filename) { currentFilename = filename; }

    bool checkDatabase(const FilmDatabase& db) {
        return validateDatabaseSize(db);
    }

    void saveToFile(const FilmDatabase& database);
    void loadFromFile(FilmDatabase& database);

    bool isOpen() const { return isFileOpen; }

};
#endif