#include "mediacontent.h"
#include <cstring>
#include <fstream>
#include <iostream>

#ifndef SERIES_H
#define SERIES_H

class Series : public MediaContent {
protected:
    int episodes;
    int seasons;
    int episodeDuration;
public:
    friend class FilmDatabase;
    Series() : MediaContent(), episodes(0), seasons(0), episodeDuration(0) {}

    void setEpisodes(int e) { episodes = e; }
    void setSeasons(int s) { seasons = s; }
    void setEpisodeDuration(int d) { episodeDuration = d; }
    int getEpisodes() const { return episodes; }
    int getSeasons() const { return seasons; }
    int getEpisodeDuration() const { return episodeDuration; }
    
    std::string getType() const override;
    
    void readSpecificData(std::istream& file) ;
    void writeSpecificData(std::ostream& file) const ;

    void inputSpecificData() override;
    void setSpecificData(const std::string& data) override;
    void print() const override;

};

#endif