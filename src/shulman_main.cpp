#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Graph.h"

using namespace std;
using namespace chrono;

int main()
{
    move_terminal();

    redirect_output_wrapper cerr_out(std::cerr);

    auto now = chrono::system_clock::now();
    auto time_t_now = chrono::system_clock::to_time_t(now);
    tm tm_now;
    localtime_s(&tm_now, &time_t_now);
    
    char time_buffer[80];
    strftime(time_buffer, sizeof(time_buffer), "%d_%m_%Y_%H_%M_%S", &tm_now);
    string time = time_buffer;
    ofstream logfile("log_" + time);
    if (logfile)
    {
        cerr_out.redirect(logfile);
    }

    unordered_map<int, Pipeline> pls;
    unordered_map<int, CompressorStation> css;
    unordered_map<int, unordered_map<int, int>> network;
    
    int max_id = 0;

    while(1)
    {
        printMainMenu();

        switch(getCorrectValue(0, 6))
        {
            case 0:
            {
                return 0;
            }
            
            case 1:
            {
                pipelineCreation(pls);
                break;
            }

            case 2:
            {
                csCreation(css);
                break;
            }

            case 3:
            {
                move_terminal();

                getMaxID(pls, css, max_id);
                objectManagementLogic(network, pls, css, max_id);

                break;
            }

            case 4:
            {
                move_terminal();

                getMaxID(pls, css, max_id);

                cout << "Gas transportation network:" << endl;

                for (int id = 1; id <= max_id; id++)
                {
                    if (pls.count(id))
                    {
                        if ((pls[id].getStartID() != 0) && (pls[id].getEndID() != 0) && (pls[id].getStatus() != 1))
                        {
                            cout << pls[id].getStartID() << " -> " << pls[id].getEndID() << endl;
                        }
                    }
                }

                cout << endl;

                topologicalSortGTN(pls, css, max_id);
                break;
            }

            case 5:
            {
                move_terminal();

                getMaxID(pls, css, max_id);
                saveInFile(pls, css, max_id);

                break;
            }

            case 6:
            {
                move_terminal();

                loadFromFile(pls, css);
                getMaxID(pls, css, max_id);

                break;
            }
        }
    }
}