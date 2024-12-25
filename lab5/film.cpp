#include "film.h"
#include <iostream>


using namespace std;


Film Film::operator+(const Film& other) const {
    Film result;
    result.name = this->name + " & " + other.name;
    result.country = this->country + "/" + other.country;
    result.director = this->director + " & " + other.director;
    result.actor = this->actor + " & " + other.actor;
    result.year = max(this->year, other.year) + 1;
    result.duration = this->duration + other.duration;
    return result;
}

Film Film::operator*(int count) const {
        Film result;
        result.name = this->name + " x" + to_string(count);
        result.country = this->country;
        result.director = this->director;
        result.actor = this->actor;
        result.year = this->year + (2 * count);
        result.duration = this->duration * count;
        return result;
    }

Film& Film::operator++() {
        ++year;
        return *this;
    }

Film Film::operator++(int) {
        Film temp = *this;
        temp.name += " 2";
        temp.year++;
        return temp;
    }

bool Film::operator==(const Film& other) const {
        return (year == other.year) && (name == other.name);
    }

bool Film::operator!=(const Film& other) const {
        return !(*this == other);
    }

void Film::clear() {
        system("clear");
    }

string Film::getType() const { return "Film"; }

void Film::readSpecificData(std::istream& file) {
    getline(file, actor);
}

void Film::writeSpecificData(std::ostream& file) const {
    file << actor << "\n";
}

void Film::inputSpecificData() {
    cout << "\x1B[5;32mMain actor: \x1b[0m";
    getline(cin, actor);
}

void Film::setSpecificData(const string& data) {
        actor = data;
    }

void Film::print() const
{
    cout << "\x1B[0;32;40m" 
    << "[Film] "
    << name << " | " 
    << country << " | "
    << director << " | "
    << actor << " | "
    << year 
    << "\x1b[0m\n";
}
