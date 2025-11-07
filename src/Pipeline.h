#pragma once
#include "utils.h"

class Pipeline 
{
private:
    std::string name;
    float length;
    int diameter;
    bool status;

public:
    Pipeline();
    Pipeline(std::string name, float length, int diameter, bool status);

    void setStatus(bool new_status);

    const std::string &getName() const;
    const float getLength() const;
    const int getDiameter() const;
    const bool getStatus() const;

    void savePipeline(std::ofstream& outfstream);
    void loadPipeline(std::ifstream& infstream);

    bool checkByName(std::string check_name);
    bool checkByStatus(bool check_status);

    friend std::istream& operator >> (std::istream& instream, Pipeline& pipe);
    friend std::ostream& operator << (std::ostream& outstream, const Pipeline& pipe);
};