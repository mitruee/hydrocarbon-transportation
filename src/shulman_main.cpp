#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Graph.h"
#include "System.h"

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

    System systema;

    while(1)
    {
        systema.printMainMenu();

        switch(getCorrectValue(0, 7))
        {
            case 0:
            {
                return 0;
            }
            
            case 1:
            {
                systema.pipelineCreation();
                break;
            }

            case 2:
            {
                systema.csCreation();
                break;
            }

            case 3:
            {
                move_terminal();

                systema.getMaxID();
                systema.objectManagementLogic();

                break;
            }

            case 4:
            {
                move_terminal();

                systema.printGTN();
                systema.topologicalSortGTN();
                break;
            }

            case 5:
            {
                move_terminal();

                systema.printGTN();
                systema.dijkstraGTN();

                break;
            }

            case 6:
            {
                move_terminal();

                systema.getMaxID();
                systema.saveInFile();

                break;
            }

            case 7:
            {
                move_terminal();

                systema.loadFromFile();
                systema.getMaxID();

                break;
            }
        }
    }
}