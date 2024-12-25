#include "miniseries.h"
#include <iostream>


using namespace std;


void MiniSeries::readSpecificData(istream& file)  {
        file >> episodes;
        file.ignore();
        file >> limitedRun;
        file.ignore();
    }

void MiniSeries::writeSpecificData(ostream& file) const  {
        file << episodes << "\n" << limitedRun << "\n";
    }

void MiniSeries::inputSpecificData()  {
        cout << "\x1B[5;32mEpisodes: \x1b[0m";
        cin >> episodes;
        cin.ignore();
        cout << "\x1B[5;32mLimited Run (1/0): \x1b[0m";
        cin >> limitedRun;
        cin.ignore();
    }

void MiniSeries::setSpecificData(const string& data)  {
        episodes = stoi(data);
    }

void MiniSeries::print() const  {
        cout << "\x1B[0;32;40m" 
             << "[MiniSeries] "
             << name << " | " 
             << country << " | "
             << director << " | "
             << episodes << " episodes | "
             << (limitedRun ? "Limited Run" : "Ongoing") << " | "
             << year 
             << "\x1b[0m\n";
    }
