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

        switch(getCorrectValue(0, 7))
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
                csCreation(css, pls, network, max_id);

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
                getMaxID(pls, css, max_id);

                for (int id = 1; id <= max_id; id++)
                {
                    if (network.count(id))
                    {
                        cout << id << ": ";
                        for (int id1 = 1; id1 <= max_id; id1++)
                        {
                            if (network[id].count(id1))
                            {
                                cout << id1 << "," << network[id][id1] << "; ";
                            }
                        }
                        cout << endl;
                    }
                }

                break;
            }

            case 5:
            {
                vector<vector<int>> edges;
                set<int> used_vertices;
                getMaxID(pls, css, max_id);

                for (int id = 1; id <= max_id; id++)
                {
                    if (css.count(id) && network.count(id))
                    {
                        for (int id1 = 1; id1 <= max_id; id1++)
                        {
                            if (network[id].count(id1) && network[id][id1] != 0)
                            {
                                vector<int> edge = {id, id1};
                                edges.push_back(edge);
                                used_vertices.insert(id);
                                used_vertices.insert(id1);
                            }
                        }
                    }
                }

                map<int, int> id_to_index;
                map<int, int> index_to_id;
                int index = 0;
                for (int vertex : used_vertices) {
                    id_to_index[vertex] = index;
                    index_to_id[index] = vertex;
                    index++;
                }

                Graph g(used_vertices.size());
                
                for (const vector<int>& edge : edges)
                {
                    g.addEdge(id_to_index[edge[0]], id_to_index[edge[1]]);
                }

                cout << "Following is a Topological Sort of the given graph: ";

                g.topologicalSort(used_vertices, index_to_id);

                break;
            }

            case 6:
            {
                move_terminal();

                getMaxID(pls, css, max_id);
                saveInFile(pls, css, max_id);

                break;
            }

            case 7:
            {
                move_terminal();

                getMaxID(pls, css, max_id);
                loadFromFile(network, pls, css, max_id);

                break;
            }
        }
    }
}