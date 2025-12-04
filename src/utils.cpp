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