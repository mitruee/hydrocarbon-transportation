#include <iostream>
#include <regex>

struct Pipeline {

    std::string kilometer_mark;
    float length;
    float diameter;
    bool repair_status;

};

struct  CompressorStation {

    std::string station_name;
    int number_of_workshops;
    int number_of_operational_workshops;
    int station_class;

};

Pipeline consoleInputPipeline() {
    
    Pipeline p;
    std::string input;
    std::regex real_number_regex();

    std::cout << "PIPELINE CREATION MODE" << std::endl;

    std::cout << "Enter a kilometer mark: ";
    std::cin >> p.kilometer_mark;

    for(;;) {

    }

}

int main() {
    consoleInputPipeline();
}