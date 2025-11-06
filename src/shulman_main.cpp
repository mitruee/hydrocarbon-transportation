#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"

using namespace std;
using namespace chrono;

class Metadata
{
private:
    int id = 0;

public:
    void setID(int new_id) { id = new_id; }
    const int &getID() { return id; }
};

void move_terminal()
{
    std::cout << "\033[2J\033[1;1H";
}

void case_break() 
{
	system("pause");
	move_terminal();
}

std::string file_input()
{
	std::string filepath;
    std::regex pattern(R"((^[a-zA-Z]:\\(?:[^\\/:*?"<>|\r\n]+\\)*[^\\/:*?"<>|\r\n]*$)|(^[^\\/:*?"<>|\r\n]*\.txt$))");
    std::smatch match;

    while (true) {
        std::cout << "Enter filepath: ";
        std::cin >> filepath;

        if (std::cin.fail() || !std::regex_match(filepath, match, pattern)) {
            std::cout << "Invalid filepath! Please, enter a full or a relative path to .txt file." << std::endl;
        }
        else {
            break;
        }
    }

    return filepath; 
}

void searchObjects(const std::unordered_map<int, Pipeline>& pls,
                  const std::unordered_map<int, CompressorStation>& css,
                  std::unordered_map<int, Pipeline>& filtered_pls,
                  std::unordered_map<int, CompressorStation>& filtered_css)
{
    
    std::cout << "Select search type (0 if by object type else 1 if by ID): "; bool search_type = getCorrectValue(0, 1);
    
    if (search_type == 0) 
    {
        std::cout << "Select object type (0 if pipeline or 1 if compressor station): ";
        bool type = getCorrectValue(0, 1);
        
        if (type == 0)
        {
            std::cout << "Select the feature by which to search (0 if by name or 1 if by repairment status): ";
            bool feat = getCorrectValue(0, 1);
            
            if (feat == 0) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string cur_name;
                std::cout << "Enter pipeline name: ";  std::getline(std::cin, cur_name);

                filtered_pls.clear();
                for (const auto& [id, pipeline] : pls) 
                {
                    if (pipeline.getName() == cur_name) 
                    {
                        filtered_pls.emplace(id, pipeline);
                    }
                }
            }
            else 
            {
                std::cout << "Enter repairment status (0 if without defects else 1): "; bool cur_rs = getCorrectValue(0, 1);

                filtered_pls.clear();
                for (const auto& [id, pipeline] : pls) 
                {
                    if (pipeline.getStatus() == cur_rs) 
                    {
                        filtered_pls.emplace(id, pipeline);
                    }
                }
            }
            filtered_css.clear();
        }
        else 
        {
            std::cout << "Select the feature by which to search (0 if by name else 1 if by uninvolved workshops percentage): ";
            bool feat = getCorrectValue(0, 1);
            
            if (feat == 0) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string cur_name;
                std::cout << "Enter a station name: "; std::getline(std::cin, cur_name);

                filtered_css.clear();
                for (const auto& [id, station] : css) 
                {
                    if (station.getName() == cur_name) 
                    {
                        filtered_css.emplace(id, station);
                    }
                }
            }
            else 
            {
                std::cout << "Enter uninvolved workshops percentage. "; int percentage = getCorrectValue(0, 100);

                filtered_css.clear();
                for (const auto& [id, station] : css) 
                {
                    int current_percentage = 100 - (int)((float)station.getIW() / station.getWorkshops() * 100);
                    if (current_percentage == percentage) 
                    {
                        filtered_css.emplace(id, station);
                    }
                }
            }
            filtered_pls.clear();
        }
    }
    else {
        std::cout << "Enter object ID. "; int search_id = getCorrectValue(0, 10000);
        
        filtered_pls.clear();
        filtered_css.clear();
        
        if (pls.count(search_id)) 
        {
            filtered_pls[search_id] = pls.at(search_id);
        }
        if (css.count(search_id)) {
            filtered_css[search_id] = css.at(search_id);
        }
    }
}

void displayObjects(const std::unordered_map<int, Pipeline>& pls,
                   const std::unordered_map<int, CompressorStation>& css,
                   const std::unordered_map<int, Pipeline>& filtered_pls,
                   const std::unordered_map<int, CompressorStation>& filtered_css, 
				   Metadata md) {
    
    std::cout << "Objects in format (id; type; type's attributes)" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    if (filtered_pls.empty() && filtered_css.empty()) 
    {
		for (int id = 1; id <= md.getID(); id++) 
        {
			if (pls.count(id)) 
            {
				std::cout << id << " pipeline " << pls.at(id).getName() << " " << pls.at(id).getLength() << " " << pls.at(id).getDiameter() << " " << pls.at(id).getStatus() << std::endl;
			}
			if (css.count(id)) 
            {
				std::cout << id << " compressor station " << css.at(id).getName() << " " << css.at(id).getWorkshops() << " " << css.at(id).getIW() << " " << css.at(id).getRang() << std::endl;
			}
		}
	}
	else {
		for (int id = 1; id <= md.getID(); id++) 
        {
			if (filtered_pls.count(id)) 
            {
				std::cout << id << " pipeline " << filtered_pls.at(id).getName() << " " << filtered_pls.at(id).getLength() << " " << filtered_pls.at(id).getDiameter() << " " << filtered_pls.at(id).getStatus() << std::endl;
			}
			if (filtered_css.count(id)) 
            {
				std::cout << id << " compressor station " << filtered_css.at(id).getName() << " " << filtered_css.at(id).getWorkshops() << " " << filtered_css.at(id).getIW() << " " << filtered_css.at(id).getRang() << std::endl;
			}
		}
	}
    std::cout << "===================================================" << std::endl;
}

void objectManagement(std::unordered_map<int, Pipeline>& pls,
                     std::unordered_map<int, CompressorStation>& css,
                     Metadata& md) {
    
    std::unordered_map<int, Pipeline> filtered_pls;
    std::unordered_map<int, CompressorStation> filtered_css;

    while (true) 
    {
        
        std::cout << "=== OBJECT MANAGEMENT ===" << std::endl;
        displayObjects(pls, css, filtered_pls, filtered_css, md);
        
        std::cout << "1. Search objects" << std::endl;
        std::cout << "2. Edit searched objects" << std::endl;
        std::cout << "3. Delete searched objects" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter a command [0-3]: ";
        
        switch (getCorrectValue(0, 3)) 
        {
            case 0: 
            {
                return;
            }
            case 1: 
            {
                searchObjects(pls, css, filtered_pls, filtered_css);
                
                if (!filtered_pls.empty() || !filtered_css.empty()) 
                {
                    std::cout << "Search completed." << std::endl;
                }
				else 
                {
                    std::cout << "No objects found with specified criteria." << std::endl;
                }
                case_break();
                break;
            }
            case 2: {
                if (filtered_pls.empty() && filtered_css.empty()) 
                {
                    std::cout << "No objects to edit. Please search first." << std::endl;
                    case_break();
                    break;
                }
                
                if (!filtered_pls.empty() && !filtered_css.empty()) 
                {
                    std::cout << "Error: search results contain both pipelines and compressor stations." << std::endl;
                    std::cout << "Please refine your search to include only one type of object." << std::endl;
                    case_break();
                    break;
                }
                
                if (!filtered_pls.empty()) 
                {
                    std::cout << "Editing pipelines..." << std::endl;
                    std::cout << "Enter new repairment status for pipelines (0 - under repair, 1 - working): ";
                    bool new_status = getCorrectValue(0, 1);
                    
                    for (auto& [id, _] : filtered_pls) 
                    {
                        if (pls.count(id)) 
                        {
                            pls[id].setStatus(new_status);
                        }
                    }
                    std::cout << "Repairment status updated for " << filtered_pls.size() << " pipelines." << std::endl;
                    case_break();
                    return;
                }
                else if (!filtered_css.empty()) 
                {
                    std::cout << "Editing compressor stations..." << std::endl;
                    std::cout << "Enter new number of involved workshops. ";
                    int new_iw = getCorrectValue(0, 100);
                    
                    int updated_count = 0;
                    for (auto& [id, station] : filtered_css) 
                    {
                        if (css.count(id)) 
                        {
                            if (new_iw <= station.getWorkshops()) 
                            {
                                css[id].setIW(new_iw);
                                updated_count++;
                            }
							else 
                            {
                                std::cout << "Warning: сannot set involved workshops more than total workshops for station ID " << id << std::endl;
                            }
                        }
                    }
                    std::cout << "Involved workshops updated for " << updated_count << " compressor stations." << std::endl;
                    case_break();
                    return;
                }
                break;
            }
            case 3: 
            {
                if (filtered_pls.empty() && filtered_css.empty()) 
                {
                    std::cout << "No objects to delete. Please search first." << std::endl;
                    case_break();
                    break;
                }
                
                int deleted_pls = 0;
                int deleted_css = 0;
                
                for (const auto& [id, _] : filtered_pls) 
                {
                    if (pls.erase(id)) 
                    {
                        deleted_pls++;
                    }
                }
                
                for (const auto& [id, _] : filtered_css) 
                {
                    if (css.erase(id)) 
                    {
                        deleted_css++;
                    }
                }

                std::cout << "Deleted " << deleted_pls << " pipelines and " << deleted_css << " compressor stations." << std::endl;

                case_break();
                return;
            }
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
    Metadata md;

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
                md.setID(md.getID() + 1);
                pls.emplace(md.getID(), p);
                cout << endl << "Pipeline was created successfully with ID " << md.getID() << endl;
                case_break(); break;
            }
            case 2:
            {
                move_terminal();

                CompressorStation cs;
                cin >> cs;
                md.setID(md.getID() + 1);
                css.emplace(md.getID(), cs);
                cout << endl << "Compressor station was created successfully with ID " << md.getID() << endl;
                case_break(); break;
            }
            case 3:
            {
                move_terminal();
                objectManagement(pls, css, md);
                case_break(); break;
            }
            case 4:
            {
                move_terminal();

                string filepath = file_input();
                ofstream outfile(filepath, ios::app);

                if (outfile.is_open())
                {
                    for (int id = 1; id <= md.getID(); id++)
                    {
                        if (pls.count(id))
                        {
                            outfile << id;
                            pls[id].savePipeline(outfile);
                        }
                        if (css.count(id))
                        {
                            outfile << id;
                            css[id].saveCS(outfile);
                        }
                    }
                }

                case_break(); break;
            }
            case 5:
            {
                std::string filepath = file_input();
				std::ifstream infile(filepath);
				std::smatch match;
				std::string line;
                std::regex line_pattern_cs("^\\s*(\\d+)\\s*;\\s*cs\\s*;\\s*(.+)\\s*;\\s*(\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(A|B|C|D|E)\\s*$");
                std::regex line_pattern_pipeline("^\\s*(\\d+)\\s*;\\s*p\\s*;\\s*(.+)\\s*;\\s*(\\d+\\.\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(0|1)\\s*$");
				int cur_id;
				int max_id;

				if (infile.is_open()) {
					while (getline(infile, line)) {
						if (regex_match(line, match, line_pattern_pipeline)) {
							Pipeline p(stoi(match[1]), match[2], std::stof(match[3]), std::stoi(match[4]), std::stoi(match[5]));
							cur_id = std::stoi(match[1]);
							pls[cur_id] = p;
							if (max_id < cur_id) {
								max_id = cur_id;
							}
						};
						if (regex_match(line, match, line_pattern_cs)) {
							CompressorStation cs(stoi(match[1]), match[2], std::stoi(match[3]), std::stoi(match[4]), match[5].str().c_str()[0]);
							cur_id = std::stoi(match[1]);
							css[cur_id] = cs;
							if (max_id < cur_id) {
								max_id = cur_id;
							}
						};
					}
				}

				md.setID(max_id);
                case_break(); break;
            }
        }
    }
}