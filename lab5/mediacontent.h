#ifndef MEDIACONTENT_H
#define MEDIACONTENT_H
#include <string>
class MediaContent {
protected:
    std::string name;
    std::string country;
    std::string director;
    int year;
public:
    MediaContent() : name(""), country(""), director(""), year(0) {}
    
    virtual ~MediaContent() = default;

    virtual void print() const = 0;
    virtual std::string getType() const = 0;
    
    virtual void readSpecificData(std::istream& file) = 0;
    virtual void writeSpecificData(std::ostream& file) const = 0;
    virtual void inputSpecificData() = 0;
    virtual void setSpecificData(const std::string& data) = 0;

    std::string getName() const { return name; }
    std::string getCountry() const { return country; }
    std::string getDirector() const { return director; }
    int getYear() const { return year; }

    void setName(const std::string& n) { name = n; }
    void setCountry(const std::string& c) { country = c; }
    void setDirector(const std::string& d) { director = d; }
    void setYear(int y) { year = y; }
};
#endif