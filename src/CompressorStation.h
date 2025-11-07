#pragma once
#include "utils.h"

class CompressorStation 
{
private:
    std::string name;
    int workshops;
    int involved_workshops;
    char st_class;

public:
    CompressorStation();
    CompressorStation(std::string name, int workshops, int involved_workshops, char st_class);

    void setIW(int new_iw);

    const std::string &getName() const;
    const int getWorkshops() const;
    const int getIW() const;
    const char getRang() const;

    void saveCS(std::ofstream& outfstream);
    void loadCS(std::ifstream& infstream);

    bool checkByName(std::string check_name);
    bool checkByPercentage(int check_per);

    friend std::istream& operator >> (std::istream& instream, CompressorStation& cs);
    friend std::ostream& operator << (std::ostream& outstream, const CompressorStation& cs);
};