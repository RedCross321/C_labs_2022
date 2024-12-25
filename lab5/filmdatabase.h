#include <cstring>
#include <iostream>
#include "mediacontent.h"
#include "series.h"
#ifndef FILMDATABASE_H
#define FILMDATABASE_H

class FilmDatabase {
private:
    MediaContent** films;
    size_t size;
    size_t capacity;
    friend bool validateDatabaseSize(const FilmDatabase& db);

public:
    FilmDatabase() : films(nullptr), size(0), capacity(0) {}
    
    ~FilmDatabase() {
        for (size_t i = 0; i < size; ++i) {
            delete films[i];
        }
        delete[] films;
    }

    void addFilm();
    void deleteFilm();
    void printFilms() const;
    void searchFilmByActor() const;

    size_t getFilmCount() const {
        return size;
    }

    const MediaContent* const* getFilms() const {
        return films;
    }

    size_t getSize() const {
        return size;
    }

    void setFilms(MediaContent** newFilms, size_t newSize);
    void combineFilms();
    void multiplyFilm();
    void incrementFilm();
    void compareFilms();
    void createSpecialVersion();
    int calculateTotalDuration(const Series& series1, const Series& series2);
    void compareTotalDuration();


    void resize(size_t newCapacity) {
        MediaContent** newFilms = new MediaContent*[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newFilms[i] = films[i];
        }
        delete[] films;
        films = newFilms;
        capacity = newCapacity;
    }
};



#endif