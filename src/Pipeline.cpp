#include "Pipeline.h"
#include "utils.h"

Pipeline::Pipeline() : name("blank"), length(0.0f), diameter(0), status(0) {}
Pipeline::Pipeline(std::string name, float length, int diameter, bool status) : name(name), length(length), diameter(diameter), status(status) {}

void Pipeline::setStatus(bool new_status) { status = new_status; }

const std::string &Pipeline::getName() const { return name; }
const float Pipeline::getLength() const { return length; }
const int Pipeline::getDiameter() const { return diameter; }
const bool Pipeline::getStatus() const { return status; }

void Pipeline::savePipeline(std::ofstream& outfstream)
{
    if (outfstream.is_open())
    {
        outfstream << "p" << std::endl
            << name << std::endl
            << length << std::endl
            << diameter << std::endl
            << status << std::endl;
    }
}

void Pipeline::loadPipeline(std::ifstream& infstream)
{
    if (infstream.is_open())
    {
        infstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        getline(infstream, name);
        infstream >> length;
        infstream >> diameter;
        infstream >> status;
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
    PRINT_PARAM(outstream, pipeline.name);
    PRINT_PARAM(outstream, pipeline.length);
    PRINT_PARAM(outstream, pipeline.diameter);
    PRINT_PARAM(outstream, pipeline.status);
    return outstream;
}