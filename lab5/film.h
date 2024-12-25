#include "mediacontent.h"
#include <cstring>
#include <fstream>
#include <iostream>

#ifndef FILM_H
#define FILM_H

class Film : public MediaContent {
private:
    std::string actor;
    int duration;
public:
    
    Film() : MediaContent(), actor(""), duration(0) {}
    
    Film(const Film& other) 
        : MediaContent(other), actor(other.actor), duration(other.duration) {}

    Film(const Film& original, const std::string& newDirector) {
        name = original.name + " (Director's Cut)";
        country = original.country;
        director = newDirector;
        actor = original.actor;
        year = original.year;
        duration = original.duration;
    }

    std::string getActor() const { return actor; }
    void setActor(const std::string& a) { actor = a; }

    int getDuration() const { return duration; }
    void setDuration(int d) { duration = d; }

    std::string getType() const override;

    void readSpecificData(std::istream& file) override;
    void writeSpecificData(std::ostream& file) const override;

    void inputSpecificData() override;
    void setSpecificData(const std::string& data) override;
    void print() const override;

    Film operator+(const Film& other) const;
    Film operator*(int count) const;
    Film& operator++();
    Film operator++(int);
    bool operator==(const Film& other) const;
    bool operator!=(const Film& other) const;
    static void clear();


};

#endif