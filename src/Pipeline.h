#pragma once
#include "utils.h"

class Pipeline 
{
private:
    std::string name;
    float length;
    int diameter;
    bool status;
    int start_id;
    int end_id;

public:
    Pipeline();
    Pipeline(std::string name, float length, int diameter, bool status, int start_id, int end_id);

    void setStatus(bool new_status);
    void setStartID(int new_id);
    void setEndID(int new_id);

    const std::string &getName() const;
    const float getLength() const;
    const int getDiameter() const;
    const bool getStatus() const;
    const int getStartID() const;
    const int getEndID() const;

    void savePipeline(std::ofstream& outfstream);
    void loadPipeline(std::ifstream& infstream);

    bool checkByName(std::string check_name);
    bool checkByStatus(bool check_status);

    friend std::istream& operator >> (std::istream& instream, Pipeline& pipe);
    friend std::ostream& operator << (std::ostream& outstream, const Pipeline& pipe);
};