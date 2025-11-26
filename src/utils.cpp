#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Graph.h"

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
    for (const auto pair : pls)
    {
        if (max_id < pair.first)
        {
            max_id = pair.first;
        }
    }
    for (const auto pair : css)
    {
        if (max_id < pair.first)
        {
            max_id = pair.first;
        }
    }
}

void pipelineCreation(std::unordered_map<int, Pipeline>& pls)
{
    move_terminal();

    Pipeline p;

    std::cin >> p;
    pls.emplace(getID(), p);

    std::cout << "Pipeline was created successfully" << std::endl;
}

void csCreation(std::unordered_map<int, CompressorStation>& css)
{
    move_terminal();

    CompressorStation cs;

    std::cin >> cs;
    css.emplace(getID(), cs);
}

void printMainMenu()
{
    std::cout << "=== HYDROCARBON TRANSPORTATION ===" << std::endl
        << "1. Create new pipeline" << std::endl
        << "2. Create new compressor station" << std::endl
        << "3. Object management" << std::endl
        << "4. Topological sort" << std::endl
        << "5. Dijkstra algorithm" << std::endl
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

int objectManagementLogic(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int max_id)
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
                getMaxID(pls, css, max_id);
                deleteSomething(pls, css, ids, max_id);

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
                getMaxID(pls, css, max_id);
                addConnection(pls, css, max_id);
                return 0;
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

void deleteSomething(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, std::vector<int>& ids, int max_id)
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
            }
            else
            {   
                css.erase(id);
                for (int id_p = 1; id_p <= max_id; id_p++)
                {
                    if (pls.count(id_p))
                    {
                        if ((pls[id_p].getStartID() == id) || (pls[id_p].getEndID() == id))
                        {
                            pls[id_p].setStartID(0);
                            pls[id_p].setEndID(0);
                        }
                    }
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

void addConnection(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation> css, int max_id)
{
    int start_id = 0;
    int end_id = 0; 

    while(1)
    {
        while(1)
        {
            std::cout << "Enter a start CS ID: ";
            start_id = getCorrectValue(1, max_id);
            if (css.count(start_id))
            {
                break;
            }
            else
            {
                std::cout << "Invalid CS ID. Try again!" << std::endl;
            }
        }
        while(1)
        {
            std::cout << "Enter an end CS ID: ";
            end_id = getCorrectValue(1, max_id);
            if (css.count(end_id))
            {
                break;
            }
            else
            {
                std::cout << "Invalid CS ID. Try again!" << std::endl;
            }
        }
        if (start_id == end_id)
        {
            std::cout << "Start and end IDs shouldn't be same. Try again!" << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    int diameter;
    std::cout << "Choose pipeline diameter: ";
    diameter = getCorrectValue(1, 1400);

    for (int id = 1; id <= max_id; id++)
    {
        if (pls.count(id))
        {
            if ((pls[id].getDiameter() == diameter) && (pls[id].getStatus() != 1) && (pls[id].getStartID() == 0))
            {
                pls[id].setStartID(start_id);
                pls[id].setEndID(end_id);
                std::cout << "Connection has been added successfully! Pipeline " << id << " beetween stations " << start_id 
                << " and " << end_id << std::endl;
                return;
            }
        }
    }

    pipelineCreation(pls);
    getMaxID(pls, css, max_id);
    pls[max_id].setStartID(start_id);
    pls[max_id].setEndID(end_id);

    std::cout << "Connection has been added successfully! Pipeline " << max_id << " beetween stations " << start_id 
    << " and " << end_id << std::endl;

}

void topologicalSortGTN(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, int max_id)
{
    std::vector<std::vector<int>> edges;
    std::set<int> used_vertices;
    getMaxID(pls, css, max_id);

    for (int id = 1; id <= max_id; id++)
    {
        if (pls.count(id))
        {
            if ((pls[id].getStartID()) != 0 && (pls[id].getEndID() != 0) && (pls[id].getStatus() != 1))
            {
                std::vector<int> edge = {pls[id].getStartID(), pls[id].getEndID()};
                edges.push_back(edge);
                used_vertices.insert(pls[id].getStartID());
                used_vertices.insert(pls[id].getEndID());
            }
        }
    }

    if (edges.empty()) {
        std::cout << "No available edges in the graph!" << std::endl;
        return;
    }

    std::map<int, int> id_to_index;
    std::map<int, int> index_to_id;
    int index = 0;
    for (int vertex : used_vertices) {
        id_to_index[vertex] = index;
        index_to_id[index] = vertex;
        index++;
    }

    Graph g(used_vertices.size());
    
    for (const std::vector<int>& edge : edges)
    {
        g.addEdge(id_to_index[edge[0]], id_to_index[edge[1]]);
    }

    std::cout << "Following is a Topological Sort of the given graph: ";

    g.topologicalSort(used_vertices, index_to_id);
}

void dijkstraGTN(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, int max_id)
{
    std::vector<std::vector<int>> edges;
    std::vector<float> weights;
    std::set<int> used_vertices;
    std::vector<int> path;
    int start_v = 0;
    int end_v = 0;
    getMaxID(pls, css, max_id);

    for (int id = 1; id <= max_id; id++)
    {
        if (pls.count(id))
        {
            if ((pls[id].getStartID() != 0) && (pls[id].getEndID() != 0) && (pls[id].getStatus() != 1))
            {
                std::vector<int> edge = {pls[id].getStartID(), pls[id].getEndID()};
                edges.push_back(edge);
                weights.push_back(pls[id].getLength());
                used_vertices.insert(pls[id].getStartID());
                used_vertices.insert(pls[id].getEndID());
            }
        }
    }

    if (edges.empty()) {
        std::cout << "No available edges in the graph!" << std::endl;
        return;
    }

    std::map<int, int> id_to_index;
    std::map<int, int> index_to_id;
    int index = 0;
    for (int vertex : used_vertices) {
        id_to_index[vertex] = index;
        index_to_id[index] = vertex;
        index++;
    }

    Graph g(used_vertices.size());
    
    for (size_t i = 0; i < edges.size(); i++)
    {
        int start_index = id_to_index[edges[i][0]];
        int end_index = id_to_index[edges[i][1]];
        g.addEdge(start_index, end_index, weights[i]);
    }

    std::cout << "Choose a start vertex ID: ";
    while(true)
    {
        start_v = getCorrectValue(1, max_id);
        if (used_vertices.count(start_v))
        {
            break;
        }
        else
        {
            std::cout << "There is no vertex with such id. Try again!" << std::endl;
        }
    }

    std::cout << "Choose an end vertex ID: ";
    while(true)
    {
        end_v = getCorrectValue(1, max_id);
        if (used_vertices.count(end_v))
        {
            break;
        }
        else
        {
            std::cout << "There is no vertex with such id. Try again!" << std::endl;
        }
    }

    path = g.dijkstra(id_to_index[start_v], id_to_index[end_v], index_to_id);

    if (path.empty()) {
        std::cout << "No path exists between vertex " << start_v << " and vertex " << end_v << std::endl;
        return;
    }

    std::cout << "The shortest path is: ";
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << index_to_id[path[i]];
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    float total_distance = 0;
    for (size_t i = 1; i < path.size(); i++)
    {
        int start_id = index_to_id[path[i-1]];
        int end_id = index_to_id[path[i]];
        
        for (size_t j = 0; j < edges.size(); j++)
        {
            if (edges[j][0] == start_id && edges[j][1] == end_id)
            {
                total_distance += weights[j];
                break;
            }
        }
    }

    std::cout << "(total distance: " << total_distance << ")" << std::endl;
}

void saveInFile(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, int max_id)
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

void loadFromFile(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int& max_id)
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
                pls.emplace(getID(), p);
            }
            else
            {
                CompressorStation cs;
                cs.loadCS(infile);
                css.emplace(getID(), cs);
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