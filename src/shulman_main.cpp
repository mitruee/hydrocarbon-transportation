#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
#include <limits>

void cin_clear() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int integer() {
    int number;

    while (true) {
        std::cout << "Enter integer: ";
        std::cin >> number;

        if (std::cin.fail() || number < 0) {
            std::cout << "Invalid value! Please, try again." << std::endl;
            cin_clear();
        }
        else {
            break;
        }
    }
    cin_clear();

    return number;
}

float real() {
    float number;

    while (true) {
        std::cout << "Enter real number: ";
        std::cin >> number;

        if (std::cin.fail() || number < 0) {
            std::cout << "Invalid value! Please, try again." << std::endl;
            cin_clear();
        }
        else {
            break;
        }
    }
    cin_clear();

    return number;
}

char rang() {
    char rang;

    while (true) {
        std::cout << "Enter [A-E]: ";
        std::cin >> rang;

        if (('A' <= rang <= 'E') || ('a' <= rang <= 'e')) {
            break;
        }
        else {
			std::cout << "Invalid value! Please, try again." << std::endl;
            cin_clear();
        }
    }
    cin_clear();

	if (rang < 97) {
    	return rang;
	}
	else {
		return rang - 32;
	}
}

int boolean() {
    int boolean;

    while (true) {
        std::cout << "Enter boolean (0 or 1): ";
        std::cin >> boolean;

        if (std::cin.fail() || boolean < 0 || boolean > 1) {
            std::cout << "Invalid value! Please, try again." << std::endl;
            cin_clear();
        }
        else {
            break;
        }
    }
    cin_clear();

    return boolean;            
}

std::string fp() {
    std::string filepath;
    std::regex pattern(R"((^[a-zA-Z]:\\(?:[^\\/:*?"<>|\r\n]+\\)*[^\\/:*?"<>|\r\n]*$)|(^[^\\/:*?"<>|\r\n]*\.txt$))");
    std::smatch match;

    while (true) {
        std::cout << "Enter filepath: ";
        std::cin >> filepath;

        if (std::cin.fail() || !std::regex_match(filepath, match, pattern)) {
            std::cout << "Invalid filepath! Please, try again." << std::endl;
            cin_clear();
        }
        else {
            break;
        }
    }
    cin_clear();

    return filepath;  
}

class Metadata {
private:
    int id = 0;

public:
    void setID(int new_id) { id = new_id; }
    const int &getID() const { return id; }
};

class Pipeline {
private:
    std::string name;
    float length;
    int diameter;
    bool status;

public:
    Pipeline() : name(""), length(0.0f), diameter(0), status(false) {}
	Pipeline(std::string name, float length, int diameter, bool status) : name(name), length(length), diameter(diameter), status(status) {}

    void setStatus(bool new_status) { status = new_status; }

    const std::string &getName() const { return name; }
    const float getLength() const { return length; }
    const int getDiameter() const { return diameter; }
    const bool getStatus() const { return status; }

    void consoleInput() {
        cin_clear();
        
        std::cout << "=== PIPELINE CREATION MODE ===" << std::endl;
        std::cout << "Enter pipeline name: "; std::getline(std::cin, name);
        std::cout << "Pipeline length. "; length = real();
        std::cout << "Pipeline diameter. "; diameter = integer();
        status = 0;
    }
};

class CompressorStation {
private:
    std::string name;
    int workshops;
    int involved_workshops;
    char st_class;

public:
    CompressorStation() : name(""), workshops(0), involved_workshops(0), st_class(0) {}
	CompressorStation(std::string name, int workshops, int involved_workshops, char st_class) : name(name), workshops(workshops), involved_workshops(involved_workshops), st_class(st_class) {}

    void setIW(int new_iw) { involved_workshops = new_iw; }

    const std::string &getName() const { return name; }
    const int getWorkshops() const { return workshops; }
    const int getIW() const { return involved_workshops; }
    const char getRang() const { return st_class; }

    void consoleInput() {
        cin_clear();

        std::cout << "=== COMPRESSOR STATION CREATION MODE ===" << std::endl;
        std::cout << "Enter a station name: "; std::getline(std::cin, name);
        std::cout << "Number of workshops. "; workshops = integer();
        std::cout << "Number of involved workshops. ";
        while (true) {
            involved_workshops = integer();
            if (involved_workshops > workshops) {
                std::cout << "Number of involved workshops cannot be more than total workshops! ";
            }
            else {
                break;
            }
        }
        std::cout << "Station class. "; st_class = rang();
    }
};

void clear() {
    std::cout << "\033[2J\033[1;1H";
}

void continuing() {
    std::string smthng;
    std::cout << "Enter any key to continue..." << std::endl;
    std::cin >> smthng;
    cin_clear();
}

void searchObjects(const std::unordered_map<int, Pipeline>& pls,
                  const std::unordered_map<int, CompressorStation>& css,
                  std::unordered_map<int, Pipeline>& filtered_pls,
                  std::unordered_map<int, CompressorStation>& filtered_css) {
    
    std::cout << "Select search type (0 if by object type else 1 if by ID)."; bool search_type = boolean();
    
    if (search_type == 0) {
        std::cout << "Select object type (0 if pipeline or 1 if compressor station). ";
        bool type = boolean();
        
        if (type == 0) {
            std::cout << "Select the feature by which to search (0 if by name or 1 if by repairment status). ";
            bool feat = boolean();
            
            if (feat == 0) {
                std::string cur_name;
                std::cout << "Enter pipeline name: ";  std::getline(std::cin, cur_name);

                filtered_pls.clear();
                for (const auto& [id, pipeline] : pls) {
                    if (pipeline.getName() == cur_name) {
                        filtered_pls[id] = pipeline;
                    }
                }
            }
            else {
                std::cout << "Enter repairment status (0 if without defects else 1). "; bool cur_rs = boolean();

                filtered_pls.clear();
                for (const auto& [id, pipeline] : pls) {
                    if (pipeline.getStatus() == cur_rs) {
                        filtered_pls[id] = pipeline;
                    }
                }
            }
            filtered_css.clear();
        }
        else {
            std::cout << "Select the feature by which to search (0 if by name else 1 if by uninvolved workshops percentage): ";
            bool feat = boolean();
            
            if (feat == 0) {
                std::string cur_name;
                std::cout << "Enter a station name: "; std::getline(std::cin, cur_name);

                filtered_css.clear();
                for (const auto& [id, station] : css) {
                    if (station.getName() == cur_name) {
                        filtered_css[id] = station;
                    }
                }
            }
            else {
                std::cout << "Enter uninvolved workshops percentage. "; int percentage = integer();

                filtered_css.clear();
                for (const auto& [id, station] : css) {
                    int current_percentage = 100 - (int)((float)station.getIW() / station.getWorkshops() * 100);
                    if (current_percentage == percentage) {
                        filtered_css[id] = station;
                    }
                }
            }
            filtered_pls.clear();
        }
    }
    else {
        std::cout << "Enter object ID. "; int search_id = integer();
        
        filtered_pls.clear();
        filtered_css.clear();
        
        if (pls.count(search_id)) {
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
				   const Metadata md) {
    
    std::cout << "Objects in format (id; type; type's attributes)" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    if (filtered_pls.empty() && filtered_css.empty()) {
		for (int id = 1; id <= md.getID(); id++) {
			if (pls.count(id)) {
				std::cout << id << " pipeline " << pls.at(id).getName() << " " << pls.at(id).getLength() << " " << pls.at(id).getDiameter() << " " << pls.at(id).getStatus() << std::endl;
			}
			if (css.count(id)) {
				std::cout << id << " compressor station " << css.at(id).getName() << " " << css.at(id).getWorkshops() << " " << css.at(id).getIW() << " " << css.at(id).getRang() << std::endl;
			}
		}
	}
	else {
		for (int id = 1; id <= md.getID(); id++) {
			if (filtered_pls.count(id)) {
				std::cout << id << " pipeline " << filtered_pls.at(id).getName() << " " << filtered_pls.at(id).getLength() << " " << filtered_pls.at(id).getDiameter() << " " << filtered_pls.at(id).getStatus() << std::endl;
			}
			if (filtered_css.count(id)) {
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
    
    while (true) {
        clear();
        
        std::cout << "=== OBJECT MANAGEMENT ===" << std::endl;
        displayObjects(pls, css, filtered_pls, filtered_css, md);
        
        std::cout << "1. Search objects" << std::endl;
        std::cout << "2. Edit searched objects" << std::endl;
        std::cout << "3. Delete searched objects" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter a command [0-3]: ";
        
        std::string input;
        std::cin >> input;
        std::regex pattern("[0-3]");
        
        if (!std::regex_match(input, pattern)) {
            std::cout << "Invalid command! Try again!" << std::endl;
            continuing();
            continue;
        }
        
        int command = std::stoi(input);
        
        switch (command) {
            case 0: {
                return;
            }
            case 1: {
                searchObjects(pls, css, filtered_pls, filtered_css);
                
                if (!filtered_pls.empty() || !filtered_css.empty()) {
                    std::cout << "Search completed." << std::endl;
                } else {
                    std::cout << "No objects found with specified criteria." << std::endl;
                }
                continuing();
                break;
            }
            case 2: {
                if (filtered_pls.empty() && filtered_css.empty()) {
                    std::cout << "No objects to edit. Please search first." << std::endl;
                    continuing();
                    break;
                }
                
                if (!filtered_pls.empty() && !filtered_css.empty()) {
                    std::cout << "Error: Search results contain both pipelines and compressor stations." << std::endl;
                    std::cout << "Please refine your search to include only one type of object." << std::endl;
                    continuing();
                    break;
                }
                
                if (!filtered_pls.empty()) {
                    std::cout << "Editing pipelines..." << std::endl;
                    std::cout << "Enter new repairment status for pipelines (0 - under repair, 1 - working): ";
                    bool new_status = boolean();
                    
                    for (auto& [id, _] : filtered_pls) {
                        if (pls.count(id)) {
                            pls[id].setStatus(new_status);
                        }
                    }
                    std::cout << "Repairment status updated for " << filtered_pls.size() << " pipelines." << std::endl;
                    
                    continuing();
                    return;
                }
                else if (!filtered_css.empty()) {
                    std::cout << "Editing compressor stations..." << std::endl;
                    std::cout << "Enter new number of involved workshops: ";
                    int new_iw = integer();
                    
                    int updated_count = 0;
                    for (auto& [id, station] : filtered_css) {
                        if (css.count(id)) {
                            if (new_iw <= station.getWorkshops()) {
                                css[id].setIW(new_iw);
                                updated_count++;
                            } else {
                                std::cout << "Warning: Cannot set involved workshops more than total workshops for station ID " << id << std::endl;
                            }
                        }
                    }
                    std::cout << "Involved workshops updated for " << updated_count << " compressor stations." << std::endl;
                    
                    continuing();
                    return;
                }
                break;
            }
            case 3: {
                if (filtered_pls.empty() && filtered_css.empty()) {
                    std::cout << "No objects to delete. Please search first." << std::endl;
                    continuing();
                    break;
                }
                
                int deleted_pls = 0;
                int deleted_css = 0;
                
                for (const auto& [id, _] : filtered_pls) {
                    if (pls.erase(id)) {
                        deleted_pls++;
                    }
                }
                
                for (const auto& [id, _] : filtered_css) {
                    if (css.erase(id)) {
                        deleted_css++;
                    }
                }
                
                std::cout << "Deleted " << deleted_pls << " pipelines and " << deleted_css << " compressor stations." << std::endl;
                
                continuing();
                return;
            }
        }
    }
}

int main() {
    std::unordered_map<int, Pipeline> pls = {};
    std::unordered_map<int, CompressorStation> css = {};
    Metadata md;
	std::regex line_pattern1("^\\s*(\\d+)\\s*;\\s*p\\s*;\\s*(.+)\\s*;\\s*(\\d+\\.\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(0|1)\\s*$");
	std::regex line_pattern2("^\\s*(\\d+)\\s*;\\s*cs\\s*;\\s*(.+)\\s*;\\s*(\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(A|B|C|D|E)\\s*$");
 

    while (true) {
        clear();

        std::string input;
        int command;
        std::regex pattern1("[0-5]");

        std::cout << "=== HYDROCARBON TRANSPORTATION ===" << std::endl
            << "1. Create new pipeline" << std::endl
            << "2. Create new compressor station" << std::endl
            << "3. Object management" << std::endl
            << "4. Save in file" << std::endl
            << "5. Load from file" << std::endl
            << "0. Exit" << std::endl
            << "=================================" << std::endl;

        std::cout << "Enter a command [0-5]: ";
        std::cin >> input;

        if (std::regex_match(input, pattern1)) {
            command = std::stoi(input);
        } else {
            std::cout << "Invalid command! Try again!" << std::endl;
            continuing(); 
            continue;
        }

        clear();

        switch (command) {
            case 0: {
                return 0;
            }
            case 1: {
                Pipeline pl;
                pl.consoleInput();
                md.setID(md.getID() + 1);
                pls[md.getID()] = pl;
                std::cout << "Pipeline created with ID: " << md.getID() << std::endl;
                continuing(); 
                break;
            }
            case 2: {
                CompressorStation cs;
                cs.consoleInput();
                md.setID(md.getID() + 1);
                css[md.getID()] = cs;
                std::cout << "Compressor station created with ID: " << md.getID() << std::endl;
                continuing(); break;
            }
            case 3: {
                objectManagement(pls, css, md);
                break;
            }
            case 4: {
                std::string filepath = fp();
				std::ofstream file(filepath);

				if (file.is_open() && md.getID() != 0) {
					for (int i = 1; i <= md.getID(); i++) {
						if (pls.count(i)) {
							file << i << ";p;" << pls[i].getName() << ";" << pls[i].getLength() << ";" << pls[i].getDiameter() << ";" << pls[i].getStatus() << std::endl;
						}
						else if (css.count(i)) {
							file << i << ";cs;" << css[i].getName() << ";" << css[i].getWorkshops() << ";" << css[i].getIW() << ";" << css[i].getRang() << std::endl;
						}
					}
				}
				else {
					std::cout << "Some troubles with specified files or there is no data to save!";
				}

                continuing(); break;
            }
            case 5: {
                std::string filepath = fp();
				std::ifstream file(filepath);
				std::smatch match;
				std::string line;
				int cur_id;
				int max_id;

				if (file.is_open()) {
					while (std::getline(file, line)) {
						if (std::regex_match(line, match, line_pattern1)) {
							Pipeline p(match[2], std::stof(match[3]), std::stoi(match[4]), std::stoi(match[5]));
							cur_id = std::stoi(match[1]);
							pls[cur_id] = p;
							if (max_id < cur_id) {
								max_id = cur_id;
							}
						};
						if (std::regex_match(line, match, line_pattern2)) {
							CompressorStation cs(match[2], std::stoi(match[3]), std::stoi(match[4]), match[5].str().c_str()[0]);
							cur_id = std::stoi(match[1]);
							css[cur_id] = cs;
							if (max_id < cur_id) {
								max_id = cur_id;
							}
						};
					}
				}

				md.setID(max_id);

                continuing(); break;
            }
        }
    }
}