#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"

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
    int max_id = 0;

    while(1)
    {
        printMainMenu();

        switch(getCorrectValue(0, 5))
        {
            case 0:
            {
                return 0;
            }
            
            case 1:
            {
                move_terminal();

                Pipeline p;

                cin >> p;
                pls.emplace(getID(), p);

                cout << "Pipeline was created successfully" << std::endl;

                break;
            }

            case 2:
            {
                move_terminal();

                CompressorStation cs;

                cin >> cs;
                css.emplace(getID(), cs);

                cout << "Compressor station was created successfully" << std::endl;

                break;
            }

            case 3:
            {
                move_terminal();

                getMaxID(pls, css, max_id);
                objectManagementLogic(pls, css, max_id);

                break;
            }

            case 4:
            {
                move_terminal();

                getMaxID(pls, css, max_id);
                saveInFile(pls, css, max_id);

                break;
            }

            case 5:
            {
                move_terminal();

                loadFromFile(pls, css);
                getMaxID(pls, css, max_id);

                break;
            }
        }
    }
}