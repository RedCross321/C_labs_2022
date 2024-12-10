#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Film {
private:
    string name;
    string country;
    string director;
    string actor;
    int year;
public:
    Film() : name(""), country(""), director(""), actor(""), year(0) {}

    Film(const Film& other) 
        : name(other.name), country(other.country),
          director(other.director), actor(other.actor),
          year(other.year) {}

    Film(const Film& original, const string& newDirector) 
        : name(original.name + " (Director's Cut)"),
          country(original.country), director(newDirector),
          actor(original.actor), year(original.year) {}

    string getName() const { return name; }
    string getCountry() const { return country; }
    string getDirector() const { return director; }
    string getActor() const { return actor; }
    int getYear() const { return year; }

    void setName(const string& n) { name = n; }
    void setCountry(const string& c) { country = c; }
    void setDirector(const string& d) { director = d; }
    void setActor(const string& a) { actor = a; }
    void setYear(int y) { year = y; }

    Film operator+(const Film& other) const {
        Film result;
        result.name = this->name + " & " + other.name;
        result.country = this->country + "/" + other.country;
        result.director = this->director + " & " + other.director;
        result.actor = this->actor + " & " + other.actor;
        result.year = max(this->year, other.year) + 1;
        return result;
    }

    Film operator*(int count) const {
        Film result;
        result.name = this->name + " x" + to_string(count);
        result.country = this->country;
        result.director = this->director;
        result.actor = this->actor;
        result.year = this->year + (2 * count);
        return result;
    }

    Film& operator++() {
        ++year;
        return *this;
    }

    Film operator++(int) {
        Film temp = *this;
        temp.name += " 2";
        temp.year++;
        return temp;
    }

    bool operator==(const Film& other) const {
        return (year == other.year) && (name == other.name);
    }

    bool operator!=(const Film& other) const {
        return !(*this == other);
    }

    void print() const {
        cout << "\x1B[0;32;40m" 
                  << name << " | " 
                  << country << " | "
                  << director << " | "
                  << actor << " | "
                  << year 
                  << "\x1b[0m\n";
    }

    static void clear() {
        system("clear");
    }
};

class FilmDatabase {
private:
    Film* films;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        Film* newFilms = new Film[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newFilms[i] = films[i];
        }
        delete[] films;
        films = newFilms;
        capacity = newCapacity;
    }

public:
    FilmDatabase() : films(new Film[10]), size(0), capacity(10) {}
    
    ~FilmDatabase() {
        delete[] films;
    }

    void addFilm() {
        Film film;
        string temp;

        Film::clear();
        cout << "\x1B[5;32mName: \x1b[0m";
        string name;
        getline(cin, name);
        film.setName(name);

        cout << "\x1B[5;32mCountry: \x1b[0m";
        string country;
        getline(cin, country);
        film.setCountry(country);

        cout << "\x1B[5;32mProducer: \x1b[0m";
        string director;
        getline(cin, director);
        film.setDirector(director);

        cout << "\x1B[5;32mMain actor: \x1b[0m";
        string actor;
        getline(cin, actor);
        film.setActor(actor);

        cout << "\x1B[5;32mYear: \x1b[0m";
        int year;
        cin >> year;
        film.setYear(year);
        cin.ignore();

        if (size >= capacity) {
            resize(capacity * 2);
        }
        films[size++] = film;

        Film::clear();
        cout << "\x1B[5;32mFilm was add\x1b[0m\n";
        cout << "\x1B[5;32mWant to add more? (y/n): \x1b[0m";
        char answer;
        cin >> answer;
        cin.ignore();
        if (answer == 'y' || answer == 'Y') {
            addFilm();
        }
    }

    void deleteFilm() {
        Film::clear();
        int index;
        cout << "\x1B[0;32mEnter a number of film what you want delete: \x1b[0m";
        cin >> index;
        cin.ignore();

        if (index <= 0 || index > size) {
            Film::clear();
            cout << "\x1B[0;32mFilm with this number don't exists\x1b[0m\n";
        } else {
            for (size_t i = index - 1; i < size - 1; ++i) {
                films[i] = films[i + 1];
            }
            --size;
            Film::clear();
            cout << "\x1B[0;32mFilm was succesfully delete\x1b[0m\n";
        }
    }

    void printFilms() const {
        Film::clear();
        cout << "\x1B[0;32;40m  № | Name                     | Country             | Producer                    | Main actor                |Year  \x1b[0m\n";
        cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";
        for (size_t i = 0; i < size; ++i) {
            cout << "\x1B[0;32;40m" << i + 1 << "|\x1b[0m";
            films[i].print();
        }
    }

    void searchFilmByActor() const {
        Film::clear();
        cout << "\x1B[0;32mEnter a name of actor: \x1b[0m";
        string actor;
        getline(cin, actor);

        Film::clear();
        cout << "\x1B[0;32;40m  № | Name                     | Country             | Producer                    | Main actor                |Year  \x1b[0m\n";
        cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";

        bool found = false;
        for (size_t i = 0; i < size; ++i) {
            if (films[i].getActor() == actor) {
                cout << "\x1B[0;32;40m" << i + 1 << "|\x1b[0m";
                films[i].print();
                found = true;
            }
        }

        if (!found) {
            Film::clear();
            cout << "\x1B[0;32mFilm with this name of actor don't exists.\x1b[0m\n";
        }
    }

    size_t getFilmCount() const {
        return size;
    }

    const Film* getFilms() const {
        return films;
    }

    size_t getSize() const {
        return size;
    }

    void setFilms(const Film* newFilms, size_t newSize) {
        delete[] films;
        films = new Film[newSize * 2];
        size = newSize;
        capacity = newSize * 2;
        for (size_t i = 0; i < size; ++i) {
            films[i] = newFilms[i];
        }
    }

    void combineFilms() {
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

        Film combined = films[idx1-1] + films[idx2-1];
        if (size >= capacity) {
            resize(capacity * 2);
        }
        films[size++] = combined;
        cout << "\x1B[0;32mFilms combined successfully\x1b[0m\n";
    }

    void multiplyFilm() {
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

        Film multiplied = films[idx-1] * factor;
        if (size >= capacity) {
            resize(capacity * 2);
        }
        films[size++] = multiplied;
        cout << "\x1B[0;32mFilm multiplied successfully\x1b[0m\n";
    }

    void incrementFilm() {
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

        cout << "Choose increment type:\n";
        cout << "1. Prefix (++film) - increase year\n";
        cout << "2. Postfix (film++) - create sequel\n";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            ++films[idx-1];
            cout << "\x1B[0;32mFilm year increased\x1b[0m\n";
        } else if (choice == 2) {
            if (size >= capacity) {
                resize(capacity * 2);
            }
            films[size++] = films[idx-1]++;
            cout << "\x1B[0;32mSequel created\x1b[0m\n";
        } else {
            cout << "\x1B[0;32mInvalid choice\x1b[0m\n";
        }
    }

    void compareFilms() {
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

        if (films[idx1-1] == films[idx2-1]) {
            cout << "\x1B[0;32mFilms are the same (same year and name)\x1b[0m\n";
        } else {
            cout << "\x1B[0;32mFilms are different\x1b[0m\n";
        }
    }

    void createSpecialVersion() {
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


        if (size >= capacity) {
            resize(capacity * 2);
        }

        cout << "Enter new director name: ";
        string director;
        getline(cin, director);
        films[size++] = Film(films[idx-1], director);
        cout << "\x1B[0;32mDirector's Cut created\x1b[0m\n";
    }
};

class FileManager {
private:
    string currentFilename;
    bool isFileOpen;

    void writeFilm(ofstream& file, const Film& film) {
        file << film.getName() << "\n"
             << film.getCountry() << "\n"
             << film.getDirector() << "\n"
             << film.getActor() << "\n"
             << film.getYear() << "\n";
    }

    void readFilm(ifstream& file, Film& film) {
        string name, country, director, actor;
        int year;

        getline(file, name);
        getline(file, country);
        getline(file, director);
        getline(file, actor);
        file >> year;
        file.ignore();

        film.setName(name);
        film.setCountry(country);
        film.setDirector(director);
        film.setActor(actor);
        film.setYear(year);
    }

public:

    FileManager() : currentFilename(""), isFileOpen(false) {}
    FileManager(const string& filename) : currentFilename(filename), isFileOpen(false) {}
    void setFilename(const string& filename) { currentFilename = filename; }

    void saveToFile(const FilmDatabase& database) {
        ofstream file(currentFilename);

        if (!file) {
            cout << "\x1B[0;32mFailed to open file for writing\x1b[0m\n";
            isFileOpen = false;
            return;
        }

        isFileOpen = true;
        size_t size = database.getSize();
        const Film* films = database.getFilms();
        file << size << endl;
        for (size_t i = 0; i < size; ++i) {
            writeFilm(file, films[i]);
        }

        file.close();
        isFileOpen = false;
        Film::clear();
        cout << "\x1B[0;32;40mData saved succesfully\x1b[0m\n";
    }

    void loadFromFile(FilmDatabase& database) {
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

        Film* films = new Film[filmCount];
        for (size_t i = 0; i < filmCount; ++i) {
            readFilm(file, films[i]);
        }

        database.setFilms(films, filmCount);
        delete[] films;
        file.close();
        isFileOpen = false;
    }

    bool isOpen() const { return isFileOpen; }
};

int main() {

    string filename;
    FileManager fileManager;
    FilmDatabase database;

    int choice;
    do {
        cout << "\n1. Add film\n"
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
            case 0:
                cout << "Exit...\n";
                break;
            default:
                cout << "Try again.\n";
        }
    } while (choice != 0);

    return 0;
}