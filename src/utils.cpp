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

void pipelineCreation(std::unordered_map<int, Pipeline>& pls)
{
    move_terminal();

            Pipeline p;

            std::cin >> p;
            pls.emplace(getID(), p);

            std::cout << "Pipeline was created successfully" << std::endl;
}

void csCreation(std::unordered_map<int, CompressorStation>& css, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, std::unordered_map<int, int>>& network, int& max_id)
{
    move_terminal();

    CompressorStation cs;

    std::cin >> cs;
    css.emplace(getID(), cs);
    getMaxID(pls, css, max_id);

    std::cout << "Compressor station was created successfully" << std::endl;

    update_network(network, css, max_id);
}

void update_network(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, CompressorStation> css, int max_id)
{
    if (network.find(max_id) == network.end()) {
        network[max_id] = std::unordered_map<int, int>();
        network[max_id].emplace(max_id, 0);
    }
    
    for (int id = 1; id < max_id; id++) {
        if (css.count(id)) {
            network[id].emplace(max_id, 0);
            network[max_id].emplace(id, 0);
        }
    }

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
        << "4. Gas transportation network" << std::endl
        << "5. Topological sort" << std::endl
        << "6. Save in file" << std::endl
        << "7. Load from file" << std::endl
        << "0. Exit" << std::endl
        << "=================================" << std::endl
        << "Enter a command [0-7]: ";
}

void printObjectManagementMenu(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::vector<int> ids)
{
    std::cout << "=== OBJECT MANAGER ===" << std::endl;
    for (int id : ids)
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
        << "2. Delete searched" << std::endl
        << "3. Edit searched" << std::endl
        << "4. Back to all existing objects" << std::endl
        << "5. Connect in gas transportation network" << std::endl
        << "0. Back to main menu" << std::endl
        << "Enter a command [0-5]: ";
}

int objectManagementLogic(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int max_id)
{
    std::vector<int> ids;
    
    for (int id = 0; id <= max_id; id++)
    {
        if (pls.count(id))
        {
            ids.push_back(id);
        }
        if (css.count(id))
        {
            ids.push_back(id);
        }
    }

    while (true)
    {
        move_terminal();
        printObjectManagementMenu(pls, css, ids);
        switch (getCorrectValue(0, 5))
        {
            case 0:
            {
                return 0;
            }
            case 1:
            {
                searchSomething(pls, css, ids);
                
                break;
            }
            case 2:
            {
                deleteSomething(pls, css, network, ids);

                break;
            }
            case 3:
            {
                editSomething(pls, css, ids, max_id);

                break;
            }
            case 4:
            {
                for (int id = 0; id <= max_id; id++)
                {
                    if (pls.count(id))
                    {
                        ids.push_back(id);
                    }
                    if (css.count(id))
                    {
                        ids.push_back(id);
                    }
                }

                break;
            }
            case 5:
            {
                connectGTN(network, pls, css, max_id);
            }
        }
    }
}

void searchSomething(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::vector<int>& ids)
{
    if (ids.size() == 0)
    {
        std::cout << "Firstly create/add something!" << std::endl;
        return;
    }
    else
    {
        std::cout << "Choose an object you want to find" << std::endl
            << "0 - pipeline" << std::endl
            << "1 - compressor station" << std::endl
            << "Enter value here: ";
        switch (getCorrectValue(0, 1))
        {
        case 0:
        {
            plsFilter(pls, ids);
            break;
        }
        case 1:
        {
            cssFilter(css, ids);
            break;
        }
        }
    }
}

void deleteSomething(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, std::unordered_map<int, std::unordered_map<int, int>>& network, std::vector<int>& ids)
{
    if (pls.size() + css.size() == ids.size() || ids.size() == 0)
    {
        std::cout << "Firstly search for something!" << std::endl;
        return;
    }
    else
    {
        for (int id : ids)
        {
            if (pls.count(id))
            {
                pls.erase(id);
                for (int id1 : ids)
                {
                    if (css.count(id1))
                    {
                        for (int id2 : ids)
                        {
                            if (css.count(id2))
                            {
                                if (network[id1][id2] == id)
                                {
                                    network[id1][id2] = 0;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                css.erase(id);
                network.erase(id);
                for (int id1 : ids)
                {
                    network[id1].erase(id);
                }
            }
        }
    }
}

void editSomething(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, std::vector<int>& ids, int max_id)
{
    if (pls.size() + css.size() == ids.size() || ids.size() == 0)
    {
        std::cout << "Firstly search for something!" << std::endl;
        return;
    }
    std::cout << "Continue searching or choose IDs?" << std::endl
    << "0 - continue searching" << std::endl
    << "1 - choose IDs" << std::endl;
    switch(getCorrectValue(0, 1))
    {
        case 0:
        {
            if (pls.count(ids[0]))
            {
                std::cout << "Choose a new repairment status for this set of pipelines." << std::endl;
                bool new_st = getCorrectValue(0, 1);
                for (int id : ids)
                {
                    pls[id].setStatus(new_st);
                }
            }
            else
            {
                std::cout << "What do you want to do?" << std::endl
                    << "0 - stop one workshop in each compressor station" << std::endl
                    << "1 - run one workshop in each compressor station" << std::endl
                    << "Note: if number of involved workshops equals zero or number of workshops nothing will change" << std::endl;
                bool mode = getCorrectValue(0, 1);
                for (int id : ids)
                {
                    if (mode) { css[id].runIW(); }
                    else { css[id].stopIW(); }
                }
            }
        }
        case 1:
        {
            bool flag;
            bool new_rs;
            bool mode;

            if (pls.count(ids[0]))
            {
                std::cout << "Enter new repairment status: ";
                new_rs = getCorrectValue(0,1);
                flag = 0;
            }
            else
            {
                std::cout << "What do you want to do?" << std::endl
                    << "0 - stop one workshop in each compressor station" << std::endl
                    << "1 - run one workshop in each compressor station" << std::endl
                    << "Note: if number of involved workshops equals zero or number of workshops nothing will change" << std::endl;

                mode = getCorrectValue(0, 1);
                flag = 1;
            }
            
            std::cout << "Enter IDs (enter 0 if you want to break)" << std::endl;

            while(true)
            {
                int temp = getCorrectValue(0, max_id);

                auto id_checker = std::find(ids.begin(), ids.end(), temp);

                if (temp == 0)
                {
                    break;
                }
                else if (id_checker == ids.end())
                {
                    std::cout << "Not in searched IDs, try another" << std::endl;
                }
                else
                {
                    if (!flag)
                    {
                        pls[temp].setStatus(new_rs);
                    }
                    else
                    {
                        if (!mode) { css[temp].stopIW(); }
                        else { css[temp].runIW(); }
                    }
                }
            }
        }
    }
}

void connectGTN(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation> css, int max_id)
{
    static std::set<int> used_pipelines;

    if (pls.size() + css.size() == 0)
    {
        std::cout << "Firstly create/add something!" << std::endl;
        return;
    }
    else
    {
        int id_s = 0;
        int id_e = 0;

        while(true)
        {
            while (true)
            {
                std::cout << "Choose ID of starting CS: ";
                id_s = getCorrectValue(1, max_id);
                if (css.count(id_s))
                {
                    break;
                }
                else
                {
                    std::cout << "There is no CS with such ID. Try again!" << std::endl;
                }
            }
            while (true)
            {
                std::cout << "Choose ID of ending CS: ";
                id_e = getCorrectValue(1, max_id);
                if (css.count(id_e))
                {
                    break;
                }
                else
                {
                    std::cout << "There is no CS with such ID. Try again!" << std::endl;
                }
            }
            if (id_s == id_e)
            {
                std::cout << id_s << " " << id_e << std::endl;
                std::cout << "Starting and ending CS are match. Try again" << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }

        std::cout << "Choose pipeline diameter: ";
        int diameter = getCorrectValue(1, 1400);
        bool flag = 0;
        int id_p = 0;

        for (int id = 1; id <= max_id; id++)
        {
            if (pls.count(id) && !used_pipelines.count(id))
            {
                if (pls[id].getDiameter() == diameter)
                {
                    id_p = id;
                    used_pipelines.insert(id);
                    flag = 1;
                    break;
                }
            }
        }

        if (flag)
        {
            network[id_s][id_e] = id_p;
        }
        else
        {
            pipelineCreation(pls);
            getMaxID(pls, css, max_id);
            network[id_s][id_e] = max_id;
        }
    }
}

void plsFilter(std::unordered_map<int, Pipeline> pls, std::vector<int>& ids)
{
    std::cout << "Choose a filter attribute" << std::endl
        << "0 - by name" << std::endl
        << "1 - by repairment status" << std::endl
        << "Enter value here: ";
    switch (getCorrectValue(0, 1))
    {
        case 0:
        {
            std::cout << "Enter pipeline name: ";
            std::string name;
            INPUT_LINE(std::cin, name);

            for (int i = 0; i < ids.size(); i++)
            {
                if (pls.count(ids[i]) && pls[ids[i]].checkByName(name))
                {
                    continue;
                }
                else
                {
                    ids.erase(ids.begin() + i);
                    i -= 1;
                }
            }
            break;
        }
        case 1:
        {
            std::cout << "Enter repairment status: ";
            bool rs = getCorrectValue(0, 1);

            for (int i = 0; i < ids.size(); i++)
            {
                if (pls.count(ids[i]) && pls[ids[i]].checkByStatus(rs))
                {
                    continue;
                }
                else
                {
                    ids.erase(ids.begin() + i);
                    i -= 1;
                }
            }
            break;
        }
    }
}

void cssFilter(std::unordered_map<int, CompressorStation> css, std::vector<int>& ids)
{
    std::cout << "Choose a filter attribute" << std::endl
        << "0 - by name" << std::endl
        << "1 - by uninvolved workshops percentage" << std::endl
        << "Enter value here: ";
    switch (getCorrectValue(0, 1))
    {
    case 0:
    {
        std::cout << "Enter compressor station name: ";
        std::string name;
        INPUT_LINE(std::cin, name);

        for (int i = 0; i < ids.size(); i++)
        {
            if (css.count(ids[i]) && css[ids[i]].checkByName(name))
            {
                continue;
            }
            else
            {
                ids.erase(ids.begin() + i);
                i -= 1;
            }
        }
        break;
    }
    case 1:
    {
        std::cout << "Enter uninvolved workshops percentage: ";
        int percentage = getCorrectValue(0, 100);

        for (int i = 0; i < ids.size(); i++)
        {
            if (css.count(ids[i]) && css[ids[i]].checkByPercentage(percentage))
            {
                continue;
            }
            else
            {
                ids.erase(ids.begin() + i);
                i -= 1;
            }
        }
        break;
    }
    }
}

void saveInFile(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::unordered_map<int, std::unordered_map<int, int>> network, int max_id)
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

        int size = network.size();
        outfile << std::endl << size << std::endl;
        for (int id1 = 1; id1 <= max_id; id1++)
        {
            if (network.count(id1))
            {   
                outfile << id1 << std::endl;
                for (int id2 = 1; id2 <= max_id; id2++)
                {
                    if (network[id1].count(id2))
                    {
                        outfile << id2 << std::endl;
                        outfile << network[id1][id2] << std::endl;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "There is some troubles with specified file. Check it!" << std::endl;
    }
}

void loadFromFile(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int& max_id)
{
    std::string filepath;

    std::cout << "Enter a filepath: ";
    INPUT_LINE(std::cin, filepath);

    getMaxID(pls, css, max_id);

    std::ifstream infile(filepath);
    std::string type;
    std::string str;
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
                pls.emplace(getID(), p);
                max_id++;
            }
            else
            {
                CompressorStation cs;
                cs.loadCS(infile);
                css.emplace(getID(), cs);
                max_id++;
                update_network(network, css, max_id);
            }
        }

        infile >> str;
        if (str == "/")
        {
            int size;
            infile >> size;
            int cur_id1;
            int cur_id2;
            int cur_p;
            while (std::getline(infile, str))
            {
                cur_id1 = std::stoi(str);
                for (int id = 1; id <= max_id; id++)
                {
                    infile >> cur_id2;
                    infile >> cur_p;
                    network[cur_id1][cur_id2] = cur_p;
                }
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