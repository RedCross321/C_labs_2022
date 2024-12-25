#include "series.h"
#include <cstring>
#include <ostream>
#include <istream>
#include <iostream>

#ifndef MINISERIES_H
#define MINISERIES_H

class MiniSeries : public Series {
private:
    bool limitedRun;
public:
    MiniSeries() : Series(), limitedRun(true) {
        seasons = 1;
    }

    void setLimitedRun(bool limited) { limitedRun = limited; }
    bool isLimitedRun() const { return limitedRun; }

    std::string getType() const override { return "MiniSeries"; }

    void readSpecificData(std::istream& file);
    void writeSpecificData(std::ostream& file) const ;
    void inputSpecificData() override;

    void setSpecificData(const std::string& data);

    void print() const override;
};

#endif