#pragma once
#include "utils.h"

class CompressorStation 
{
private:
    int id;
    std::string name;
    int workshops;
    int involved_workshops;
    char st_class;

public:
    CompressorStation();
    CompressorStation(int id, std::string name, int workshops, int involved_workshops, char st_class);


    void setID(int new_id);
    void setIW(int new_iw);

    const int &getID() const;
    const std::string &getName() const;
    const int getWorkshops() const;
    const int getIW() const;
    const char getRang() const;

    void saveCS(std::ofstream& outfstream);

    bool checkByID();
    bool checkByPercentage();

    friend std::istream& operator >> (std::istream& instream, CompressorStation& cs);
    friend std::ostream& operator << (std::ostream& outstream, const CompressorStation& cs);
};