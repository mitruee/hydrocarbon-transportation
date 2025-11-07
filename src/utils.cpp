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

void getMaxID(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, int& max_id)
{
    for (const auto& pair : pls)
    {
        if (max_id < pair.first)
        {
            max_id = pair.first;
        }
    }
    for (const auto& pair : css)
    {
        if (max_id < pair.first)
        {
            max_id = pair.first;
        }
    }
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

void printObjectManagementMenu(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int max_id)
{
    std::cout << "=== OBJECT MANAGER ===" << std::endl;
    for (int id = 1; id <= max_id; id++)
    {
        if (pls.count(id))
        {
            std::cout << std::endl << "id=" << id << std::endl << pls[id];
        }
        if (css.count(id))
        {
            std::cout << std::endl << "id=" << id << std::endl << css[id];
        }
    }
    std::cout << "======================" << std::endl
        << "1. Search" << std::endl
        << "2. Delete" << std::endl
        << "3. Edit" << std::endl
        << "0. Back to main menu" << std::endl
        << "Enter a command [0-3]: ";
}

int objectManagementLogic(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int max_id)
{
    std::vector<int> ids;

    printObjectManagementMenu(pls, css, max_id);
    while (true)
    {
        switch (getCorrectValue(0, 3))
        {
            case 0:
            {
                return 0;
            }
            case 1:
            {
                std::cout << "Choose object type." << std::endl
                    << "0 - pipeline" << std::endl
                    << "1 - compressor station" << std::endl
                    << "Enter value: ";
                bool object_type = getCorrectValue(0, 1);
                search(pls, css, ids, object_type, max_id);
                break;
            }
        }
    }
}

void search(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::vector<int>& ids, bool object_type, int max_id)
{
    if (!object_type)
    {
        if (ids.size() != 0)
        {
            plsFilter(pls, ids);
        }
        else
        {
            for (int id = 1; id <= max_id; id++)
            {
                ids.push_back(id);
            }

            plsFilter(pls, ids);

        }
    }

    else
    {
        if (ids.size() != 0)
        {
            cssFilter(css, ids);
        }
        else
        {
            for (int id = 1; id <= max_id; id++)
            {
                ids.push_back(id);
            }

            cssFilter(css, ids);

        }
    }
}

void plsFilter(std::unordered_map<int, Pipeline> pls, std::vector<int>& ids)
{
    std::cout << "Choose an attribute for searching." << std::endl
        << "0 - name" << std::endl
        << "1 - repairment status" << std::endl
        << "Enter value: ";

    switch (getCorrectValue(0, 1))
    {
        case 0:
        {
            std::string name;
            INPUT_LINE(std::cin, name);

            for (int id : ids)
            {
                if (pls[id].checkByName(name))
                {
                    ids.erase(ids.begin() + id);
                }
            }
        }
        case 1:
        {
            bool rs = getCorrectValue(0, 1);

            for (int id : ids)
            {
                if (pls[id].checkByStatus(rs))
                {
                    ids.erase(ids.begin() + id);
                }
            }
        }
    }

    for (int id : ids)
    {
        std::cout << std::endl << "id=" << id << std::endl << pls[id];
    }
}

void cssFilter(std::unordered_map<int, CompressorStation> css, std::vector<int>& ids)
{
    std::cout << "Choose an attribute for searching." << std::endl
        << "0 - name" << std::endl
        << "1 - percentage of uninvolved workshops" << std::endl
        << "Enter value: ";

    switch (getCorrectValue(0, 1))
    {
        case 0:
        {
            std::string name;
            INPUT_LINE(std::cin, name);

            for (int id : ids)
            {
                if (css[id].checkByName(name))
                {
                    ids.erase(ids.begin() + id);
                }
            }
        }
        case 1:
        {
            bool perc = getCorrectValue(0, 100);

            for (int id : ids)
            {
                if (css[id].checkByPercentage(perc))
                {
                    ids.erase(ids.begin() + id);
                }
            }
        }
    }

    for (int id : ids)
    {
        std::cout << std::endl << "id=" << id << std::endl << css[id];
    }
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