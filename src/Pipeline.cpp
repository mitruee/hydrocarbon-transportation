#include "Pipeline.h"
#include "utils.h"

Pipeline::Pipeline() : id(0), name("blank"), length(0.0f), diameter(0), status(0) {}
Pipeline::Pipeline(int id, std::string name, float length, int diameter, bool status) : id(id), name(name), length(length), diameter(diameter), status(status) {}

void Pipeline::setID(int new_id) { id = new_id; }
void Pipeline::setStatus(bool new_status) { status = new_status; }

const int &Pipeline::getID() const { return id; }
const std::string &Pipeline::getName() const { return name; }
const float Pipeline::getLength() const { return length; }
const int Pipeline::getDiameter() const { return diameter; }
const bool Pipeline::getStatus() const { return status; }


void Pipeline::savePipeline(std::ofstream& outfstream)
{
    if (outfstream.is_open())
    {
        outfstream << ";p;" << name << ";" << length << ";" << diameter << ";" << status << std::endl;
    }
}


std::istream& operator >> (std::istream& instream, Pipeline& pipeline)
{

    std::cout << "Enter name: ";
    INPUT_LINE(instream, pipeline.name);
    std::cout << "Enter length: ";
    pipeline.length = getCorrectValue(0.1, 1000.0);
    std::cout << "Enter diameter: ";
    pipeline.diameter = getCorrectValue(100, 2000);
    return instream;

}

std::ostream& operator << (std::ostream& outstream, const Pipeline& pipeline)
{
    PRINT_PARAM(outstream, pipeline.id);
    PRINT_PARAM(outstream, pipeline.name);
    PRINT_PARAM(outstream, pipeline.length);
    PRINT_PARAM(outstream, pipeline.diameter);
    PRINT_PARAM(outstream, pipeline.status);
    return outstream;
}