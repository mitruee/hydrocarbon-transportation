#pragma once
#include "utils.h"

class Pipeline 
{
private:
    int id;
    std::string name;
    float length;
    int diameter;
    bool status;

public:
    Pipeline();
    Pipeline(int id, std::string name, float length, int diameter, bool status);

    void setID(int new_id);
    void setStatus(bool new_status);

    const int &getID() const;
    const std::string &getName() const;
    const float getLength() const;
    const int getDiameter() const;
    const bool getStatus() const;

    void savePipeline(std::ofstream& outstream);

    bool checkByID();
    bool checkByStatus();

    friend std::istream& operator >> (std::istream& instream, Pipeline& pipe);
    friend std::ostream& operator << (std::ostream& outstream, const Pipeline& pipe);
};