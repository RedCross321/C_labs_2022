#include "filmdatabase.h"
#include "miniseries.h"
#include "film.h"
#include <iostream>
#include <algorithm>


using namespace std;

void FilmDatabase::addFilm() {
        MediaContent* film;
        string temp;

        Film::clear();
        cout << "\x1B[5;32mName: \x1b[0m";
        string name;
        getline(cin, name);

        cout << "\x1B[5;32mCountry: \x1b[0m";
        string country;
        getline(cin, country);

        cout << "\x1B[5;32mProducer: \x1b[0m";
        string director;
        getline(cin, director);

        cout << "\x1B[5;32mType (Film/f, Series/s, MiniSeries/ms): \x1b[0m";
        string type;
        getline(cin, type);
        
        string lowerType = type;
        transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);

        if (type == "film" || lowerType == "f") {
            film = new Film();
            film->inputSpecificData();
        } else if (type == "series" || lowerType == "s") {
            film = new Series();
            film->inputSpecificData();
        } else if (type == "miniseries" || lowerType == "ms") {
            film = new MiniSeries();
            film->inputSpecificData();
        } else {
            cout << "\x1B[0;32mInvalid type\x1b[0m\n";
            return;
        }

        film->setName(name);
        film->setCountry(country);
        film->setDirector(director);

        cout << "\x1B[5;32mYear: \x1b[0m";
        int year;
        cin >> year;
        film->setYear(year);
        cin.ignore();

        if (size >= capacity) {
            resize(capacity * 2);
        }
        films[size++] = film;

        Film::clear();
        cout << "\x1B[0;32mFilm was add\x1b[0m\n";
        cout << "\x1B[5;32mWant to add more? (y/n): \x1b[0m";
        char answer;
        cin >> answer;
        cin.ignore();
        if (answer == 'y' || answer == 'Y') {
            addFilm();
        }
    }

void FilmDatabase::deleteFilm() {
    Film::clear();
    int index;
    cout << "\x1B[0;32mEnter a number of film what you want delete: \x1b[0m";
    cin >> index;
    cin.ignore();

    if (index <= 0 || index > size) {
        Film::clear();
        cout << "\x1B[0;32mFilm with this number don't exists\x1b[0m\n";
    } else {
        delete films[index - 1];
        for (size_t i = index - 1; i < size - 1; ++i) {
            films[i] = films[i + 1];
        }
        --size;
        Film::clear();
        cout << "\x1B[0;32mFilm was succesfully delete\x1b[0m\n";
    }
}

void FilmDatabase::printFilms() const {
    Film::clear();
    cout << "\x1B[0;32;40m  № | Name                     | Country             | Producer                    | Type                      |Year  \x1b[0m\n";
    cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";
    for (size_t i = 0; i < size; ++i) {
        cout << "\x1B[0;32;40m" << i + 1 << "|\x1b[0m";
        films[i]->print();
    }
}

void FilmDatabase::searchFilmByActor() const {
    Film::clear();
    cout << "\x1B[0;32mEnter a name of actor: \x1b[0m";
    string actor;
    getline(cin, actor);

    Film::clear();
    cout << "\x1B[0;32;40m  № | Name                     | Country             | Producer                    | Type                      |Year  \x1b[0m\n";
    cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";

    bool found = false;
    for (size_t i = 0; i < size; ++i) {
        if (films[i]->getType() == "Film") {
            Film* film = dynamic_cast<Film*>(films[i]);
            if (film->getActor() == actor) {
                cout << "\x1B[0;32;40m" << i + 1 << "|\x1b[0m";
                films[i]->print();
                found = true;
            }
        }
    }

    if (!found) {
        Film::clear();
        cout << "\x1B[0;32mFilm with this name of actor don't exists.\x1b[0m\n";
    }
}
void FilmDatabase::setFilms(MediaContent** newFilms, size_t newSize) {
    for (size_t i = 0; i < size; ++i) {
        delete films[i];
    }
    delete[] films;
    films = new MediaContent*[newSize * 2];
    size = newSize;
    capacity = newSize * 2;
    for (size_t i = 0; i < size; ++i) {
        films[i] = newFilms[i];
    }
}

void FilmDatabase::combineFilms() {
    if (size < 2) {
        cout << "\x1B[0;32mNeed at least 2 films to combine\x1b[0m\n";
        return;
    }

    cout << "Enter first film number: ";
    int idx1;
    cin >> idx1;
    cout << "Enter second film number: ";
    int idx2;
    cin >> idx2;
    cin.ignore();

    if (idx1 <= 0 || idx2 <= 0 || idx1 > size || idx2 > size) {
        cout << "\x1B[0;32mInvalid film numbers\x1b[0m\n";
        return;
    }

    if (films[idx1-1]->getType() == "Film" && films[idx2-1]->getType() == "Film") {
        Film* film1 = dynamic_cast<Film*>(films[idx1-1]);
        Film* film2 = dynamic_cast<Film*>(films[idx2-1]);
        Film combined = *film1 + *film2;
        if (size >= capacity) {
            resize(capacity * 2);
        }
        films[size++] = new Film(combined);
        cout << "\x1B[0;32mFilms combined successfully\x1b[0m\n";
    } else {
        cout << "\x1B[0;32mOnly films can be combined\x1b[0m\n";
    }
}

void FilmDatabase::multiplyFilm() {
    if (size < 1) {
        cout << "\x1B[0;32mNo films to multiply\x1b[0m\n";
        return;
    }

    cout << "Enter film number: ";
    int idx;
    cin >> idx;
    cout << "Enter multiplication factor: ";
    int factor;
    cin >> factor;
    cin.ignore();

    if (idx <= 0 || idx > size || factor <= 0) {
        cout << "\x1B[0;32mInvalid input\x1b[0m\n";
        return;
    }

    if (films[idx-1]->getType() == "Film") {
        Film* film = dynamic_cast<Film*>(films[idx-1]);
        Film multiplied = *film * factor;
        if (size >= capacity) {
            resize(capacity * 2);
        }
        films[size++] = new Film(multiplied);
        cout << "\x1B[0;32mFilm multiplied successfully\x1b[0m\n";
    } else {
        cout << "\x1B[0;32mOnly films can be multiplied\x1b[0m\n";
    }
}

void FilmDatabase::incrementFilm() {
    if (size < 1) {
        cout << "\x1B[0;32mNo films to increment\x1b[0m\n";
        return;
    }

    cout << "Enter film number: ";
    int idx;
    cin >> idx;
    cin.ignore();

    if (idx <= 0 || idx > size) {
        cout << "\x1B[0;32mInvalid film number\x1b[0m\n";
        return;
    }

    if (films[idx-1]->getType() == "Film") {
        Film* film = dynamic_cast<Film*>(films[idx-1]);
        cout << "Choose increment type:\n";
        cout << "1. Prefix (++film) - increase year\n";
        cout << "2. Postfix (film++) - create sequel\n";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            ++(*film);
            cout << "\x1B[0;32mFilm year increased\x1b[0m\n";
        } else if (choice == 2) {
            if (size >= capacity) {
                resize(capacity * 2);
            }
            films[size++] = new Film((*film)++);
            cout << "\x1B[0;32mSequel created\x1b[0m\n";
        } else {
            cout << "\x1B[0;32mInvalid choice\x1b[0m\n";
        }
    } else {
        cout << "\x1B[0;32mOnly films can be incremented\x1b[0m\n";
    }
}

void FilmDatabase::compareFilms() {
    if (size < 2) {
        cout << "\x1B[0;32mNeed at least 2 films to compare\x1b[0m\n";
        return;
    }

    cout << "Enter first film number: ";
    int idx1;
    cin >> idx1;
    cout << "Enter second film number: ";
    int idx2;
    cin >> idx2;
    cin.ignore();

    if (idx1 <= 0 || idx2 <= 0 || idx1 > size || idx2 > size) {
        cout << "\x1B[0;32mInvalid film numbers\x1b[0m\n";
        return;
    }

    if (films[idx1-1]->getType() == "Film" && films[idx2-1]->getType() == "Film") {
        Film* film1 = dynamic_cast<Film*>(films[idx1-1]);
        Film* film2 = dynamic_cast<Film*>(films[idx2-1]);
        if (*film1 == *film2) {
            cout << "\x1B[0;32mFilms are the same (same year and name)\x1b[0m\n";
        } else {
            cout << "\x1B[0;32mFilms are different\x1b[0m\n";
        }
    } else {
        cout << "\x1B[0;32mOnly films can be compared\x1b[0m\n";
    }
}

void FilmDatabase::createSpecialVersion() {
    if (size < 1) {
        cout << "\x1B[0;32mNo films to create version from\x1b[0m\n";
        return;
    }

    cout << "Enter film number: ";
    int idx;
    cin >> idx;
    cin.ignore();

    if (idx <= 0 || idx > size) {
        cout << "\x1B[0;32mInvalid film number\x1b[0m\n";
        return;
    }

    if (films[idx-1]->getType() == "Film") {
        Film* film = dynamic_cast<Film*>(films[idx-1]);
        if (size >= capacity) {
            resize(capacity * 2);
        }

        cout << "Enter new director name: ";
        string director;
        getline(cin, director);
        films[size++] = new Film(*film, director);
        cout << "\x1B[0;32mDirector's Cut created\x1b[0m\n";
    } else {
        cout << "\x1B[0;32mOnly films can be used to create a Director's Cut\x1b[0m\n";
    }
}

int FilmDatabase::calculateTotalDuration(const Series& series1, const Series& series2) {
    return (series1.episodes * series1.episodeDuration * series1.seasons) +
            (series2.episodes * series2.episodeDuration * series2.seasons);
}

void FilmDatabase::compareTotalDuration() {
    Film::clear();
    cout << "\x1B[5;32mEnter first series number: \x1b[0m";
    size_t idx1;
    cin >> idx1;
    cin.ignore();

    cout << "\x1B[5;32mEnter second series number: \x1b[0m";
    size_t idx2;
    cin >> idx2;
    cin.ignore();

    if (idx1 < 1 || idx1 > size || idx2 < 1 || idx2 > size) {
        cout << "\x1B[0;32mInvalid series numbers\x1b[0m\n";
        return;
    }

    Series* series1 = dynamic_cast<Series*>(films[idx1-1]);
    Series* series2 = dynamic_cast<Series*>(films[idx2-1]);

    if (!series1 || !series2) {
        cout << "\x1B[0;32mBoth items must be series\x1b[0m\n";
        return;
    }

    int totalEpisodes = series1->episodes + series2->episodes;
    int totalDuration = calculateTotalDuration(*series1, *series2);

    cout << "\x1B[0;32mTotal episodes: " << totalEpisodes << "\n";
    cout << "Total duration: " << totalDuration << " minutes (" 
            << (totalDuration / 60) << " hours " << (totalDuration % 60) << " minutes)\x1b[0m\n";
}


