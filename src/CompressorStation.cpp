#include "CompressorStation.h"
#include "utils.h"

CompressorStation::CompressorStation() : name("blank"), workshops(0), involved_workshops(0), st_class(65) {}
CompressorStation::CompressorStation(std::string name, int workshops, int involved_workshops, char st_class) : name(name), workshops(workshops), involved_workshops(involved_workshops), st_class(st_class) {}

void CompressorStation::setIW(int new_iw) { involved_workshops = new_iw; }

const std::string &CompressorStation::getName() const { return name; }
const int CompressorStation::getWorkshops() const { return workshops; }
const int CompressorStation::getIW() const { return involved_workshops; }
const char CompressorStation::getRang() const { return st_class; }

void CompressorStation::saveCS(std::ofstream& outfstream)
{
    if (outfstream.is_open())
    {
        outfstream << ";cs;" << name << ";" << workshops << ";" << involved_workshops << ";" << st_class << std::endl;
    }
}

void CompressorStation::loadCS(std::ifstream& infstream)
{
    if (infstream.is_open())
    {
        infstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        getline(infstream, name);
        infstream >> workshops;
        infstream >> involved_workshops;
        infstream >> st_class;
    }
}

std::istream& operator >> (std::istream& instream, CompressorStation& cs)
{

    std::cout << "Enter name: ";
    INPUT_LINE(instream, cs.name);
    std::cout << "Enter number of workshops: ";
    cs.workshops = getCorrectValue(1, 100);
    std::cout << "Enter number of involved workshops: ";
    int input_iw;
    while (true) 
    {
        input_iw = getCorrectValue(1, 100);
        if (input_iw <= cs.workshops) 
        {
            cs.involved_workshops = input_iw;
            break;
        }
        else
        {
            std::cout << "Number of involved workshops cannot be more than number of workshops. Try again: ";
        }
    }
    std::cout << "Enter station class: ";
    cs.st_class = getCorrectValue('A', 'E');
    return instream;

}

std::ostream& operator << (std::ostream& outstream, const CompressorStation& cs)
{
    PRINT_PARAM(outstream, cs.name);
    PRINT_PARAM(outstream, cs.workshops);
    PRINT_PARAM(outstream, cs.involved_workshops);
    PRINT_PARAM(outstream, cs.st_class);
    return outstream;
}