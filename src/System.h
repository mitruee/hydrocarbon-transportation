#pragma once
#include "utils.h"

using namespace std;

class System
{
private:
    
    unordered_map<int, Pipeline> pls;
    unordered_map<int, CompressorStation> css;
    int max_id;
    vector<int> output_ids;
    
public:

    System();

    void getMaxID();

    void pipelineCreation();
    void csCreation();

    void printMainMenu();

    void printObjectManagementMenu();
    int objectManagementLogic();
    void searchSomething();
    void deleteSomething();
    void editSomething();
    void plsFilter();
    void cssFilter();
    void addConnection();

    void printGTN();
    void topologicalSortGTN();
    void dijkstraGTN();

    void saveInFile();
    void loadFromFile();

};