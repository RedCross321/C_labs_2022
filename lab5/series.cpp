#include "series.h"
#include <iostream>


using namespace std;

string Series::getType() const { return "Series"; }

void Series::readSpecificData(istream& file)  {
    file >> seasons >> episodes >> episodeDuration;
    file.ignore();
}

void Series::writeSpecificData(ostream& file) const  {
    file << seasons << " " << episodes << " " << episodeDuration << "\n";
}

void Series::inputSpecificData()  {
    cout << "\x1B[5;32mSeasons: \x1b[0m";
    cin >> seasons;
    cin.ignore();
    cout << "\x1B[5;32mEpisodes: \x1b[0m";
    cin >> episodes;
    cin.ignore();
    cout << "\x1B[5;32mEpisode Duration (minutes): \x1b[0m";
    cin >> episodeDuration;
    cin.ignore();
}

void Series::setSpecificData(const string& data)  {
    size_t space1 = data.find(' ');
    size_t space2 = data.find(' ', space1 + 1);
    if (space1 != string::npos && space2 != string::npos) {
        seasons = stoi(data.substr(0, space1));
        episodes = stoi(data.substr(space1 + 1, space2 - space1 - 1));
        episodeDuration = stoi(data.substr(space2 + 1));
    }
}

void Series::print() const  {
    cout << "\x1B[0;32;40m" 
            << "[Series] "
            << name << " | " 
            << country << " | "
            << director << " | "
            << seasons << " seasons | "
            << episodes << " episodes | "
            << episodeDuration << " min/ep | "
            << "Total: " << (seasons * episodes * episodeDuration) << " minutes | "
            << year 
            << "\x1b[0m\n";
    }