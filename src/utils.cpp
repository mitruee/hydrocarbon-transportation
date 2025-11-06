#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"

void move_terminal()
{
    std::cout << "\033[2J\033[1;1H";
}

int getID()
{
    static int id = 0;
    return ++id;
}

void printMainMenu()
{
    std::cout << "=== HYDROCARBON TRANSPORTATION ===" << std::endl
        << "1. Create new pipeline" << std::endl
        << "2. Create new compressor station" << std::endl
        << "3. Object management" << std::endl
        << "4. Save in file" << std::endl
        << "5. Load from file" << std::endl
        << "0. Exit" << std::endl
        << "=================================" << std::endl
        << "Enter a command [0-5]: ";
}

void printObjectManagementMenu(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css)
{

}

void saveInFile(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int max_id)
{
    std::string filepath;

    std::cout << "Enter a filepath: ";
    INPUT_LINE(std::cin, filepath);

    std::ofstream outfile(filepath);

    if (outfile.is_open())
    {
        if (max_id != 0)
        {
            for (int id = 1; id <= max_id; id++)
            {
                outfile << id << std::endl;
                if (pls.count(id))
                {
                    pls[id].savePipeline(outfile);
                }
                if (css.count(id))
                {
                    css[id].saveCS(outfile);
                }
            }
            std::cout << "All objectes were successfully saved into specified file!" << std::endl;
        }
        else
        {
            std::cout << "There is no objects to save." << std::endl;
        }
    }
    else
    {
        std::cout << "There is some troubles with specified file. Check it!" << std::endl;
    }
}

void loadFromFile(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css)
{
    std::string filepath;

    std::cout << "Enter a filepath: ";
    INPUT_LINE(std::cin, filepath);

    std::ifstream infile(filepath);
    std::string type;
    int id = 0;

    if (infile.is_open())
    {
        while (infile >> id)
        {
            infile >> type;
            if (type == "p")
            {
                Pipeline p;
                p.loadPipeline(infile);
                pls.emplace(id, p);
            }
            else
            {
                CompressorStation cs;
                cs.loadCS(infile);
                css.emplace(id, cs);
            }
        }

        if (id != 0)
        {
            std::cout << "File was read succesfully!" << std::endl;
        }

        else
        {
            std::cout << "There is no objects with correct format in specified file!" << std::endl;
        }

    }
    else
    {
        std::cout << "There is some troubles with specified file. Check it!" << std::endl;
    }
}