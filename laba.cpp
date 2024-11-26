#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class Film {
public:
    std::string name;
    std::string country;
    std::string director;
    std::string actor;
    int year;

    void print() const {
        std::cout << "\x1B[0;32;40m" 
                  << name << " | " 
                  << country << " | "
                  << director << " | "
                  << actor << " | "
                  << year 
                  << "\x1b[0m\n";
    }

    static void clear() {
        std::system("clear");
    }
};

class FilmDatabase {
private:
    std::vector<Film> films;

public:
    void addFilm() {
        Film film;
        std::string temp;

        Film::clear();
        std::cout << "\x1B[5;32mВведите название: \x1b[0m";
        std::getline(std::cin, film.name);

        std::cout << "\x1B[5;32mВведите страну: \x1b[0m";
        std::getline(std::cin, film.country);

        std::cout << "\x1B[5;32mВведите режиссера: \x1b[0m";
        std::getline(std::cin, film.director);

        std::cout << "\x1B[5;32mВведите главного актера: \x1b[0m";
        std::getline(std::cin, film.actor);

        std::cout << "\x1B[5;32mВведите год: \x1b[0m";
        std::cin >> film.year;
        std::cin.ignore();  

        films.push_back(film);

        Film::clear();
        std::cout << "\x1B[5;32mФильм внесен в список\x1b[0m\n";
        std::cout << "\x1B[5;32mХотите добавить ещё один? (y/n): \x1b[0m";
        char answer;
        std::cin >> answer;
        std::cin.ignore();  
        if (answer == 'y' || answer == 'Y') {
            addFilm();
        }
    }

    void deleteFilm() {
        Film::clear();
        int index;
        std::cout << "\x1B[0;32mВведите номер фильма для удаления: \x1b[0m";
        std::cin >> index;
        std::cin.ignore();  

        if (index <= 0 || index > films.size()) {
            Film::clear();
            std::cout << "\x1B[0;32mНет фильма с таким номером\x1b[0m\n";
        } else {
            films.erase(films.begin() + index - 1);
            Film::clear();
            std::cout << "\x1B[0;32mФильм успешно удален\x1b[0m\n";
        }
    }

    void printFilms() const {
        Film::clear();
        std::cout << "\x1B[0;32;40m  № | Название                     | Страна             | Режиссер                    | Главный актер                |Год  \x1b[0m\n";
        std::cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";
        for (size_t i = 0; i < films.size(); ++i) {
            std::cout << "\x1B[0;32;40m" << i + 1 << "|\x1b[0m";
            films[i].print();
        }
    }

    void searchFilmByActor() const {
        Film::clear();
        std::cout << "\x1B[0;32mВведите имя актера: \x1b[0m";
        std::string actor;
        std::getline(std::cin, actor);

        Film::clear();
        std::cout << "\x1B[0;32;40m  № | Название                     | Страна             | Режиссер                    | Главный актер                |Год  \x1b[0m\n";
        std::cout << "\x1B[0;32;40m-------------------------------------------------------------------------------------------------------------------------- \x1b[0m\n";

        bool found = false;
        for (size_t i = 0; i < films.size(); ++i) {
            if (films[i].actor == actor) {
                std::cout << "\x1B[0;32;40m" << i + 1 << "|\x1b[0m";
                films[i].print();
                found = true;
            }
        }

        if (!found) {
            Film::clear();
            std::cout << "\x1B[0;32mНе найдено фильмов с данным актером или его имя введено неверно.\x1b[0m\n";
        }
    }

    size_t getFilmCount() const {
        return films.size();
    }

    const std::vector<Film>& getFilms() const {
        return films;
    }
};

class FileManager {
public:
    static void saveToFile(const FilmDatabase& database, const std::string& filename) {
        std::ofstream file(filename);

        if (!file) {
            std::cout << "\x1B[0;32mНе удалось открыть файл для записи\x1b[0m\n";
            return;
        }

        const auto& films = database.getFilms();
        file << films.size() << std::endl;
        for (const auto& film : films) {
            file << film.name << "\n"
                 << film.country << "\n"
                 << film.director << "\n"
                 << film.actor << "\n"
                 << film.year << "\n";
        }

        file.close();
        Film::clear();
        std::cout << "\x1B[0;32;40mДанные успешно сохранены\x1b[0m\n";
    }

    static void loadFromFile(FilmDatabase& database, const std::string& filename) {
        std::ifstream file(filename);

        if (!file) {
            std::cout << "\x1B[0;32mНе удалось открыть файл для чтения\x1b[0m\n";
            return;
        }

        size_t filmCount;
        file >> filmCount;
        file.ignore();

        std::vector<Film> films;
        for (size_t i = 0; i < filmCount; ++i) {
            Film film;
            std::getline(file, film.name);
            std::getline(file, film.country);
            std::getline(file, film.director);
            std::getline(file, film.actor);
            file >> film.year;
            file.ignore(); 

            films.push_back(film);
        }

        file.close();
    }
};

int main() {
    FilmDatabase database;

    FileManager::loadFromFile(database, "films.txt");

    int choice;
    do {
        std::cout << "\n1. Добавить фильм\n"
                  << "2. Удалить фильм\n"
                  << "3. Печать всех фильмов\n"
                  << "4. Сохранить данные\n"
                  << "5. Загрузить данные\n"
                  << "6. Поиск по актеру\n"
                  << "0. Выход\n";
        std::cout << "Введите выбор: ";
        std::cin >> choice;
        std::cin.ignore(); 

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
                FileManager::saveToFile(database, "films.txt");
                break;
            case 5:
                FileManager::loadFromFile(database, "films.txt");
                break;
            case 6:
                database.searchFilmByActor();
                break;
            case 0:
                std::cout << "Выход из программы...\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
