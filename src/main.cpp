#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <chrono>

class Pipeline {
public:

	std::string kilometer_mark = "empty";
	float length = 0.0;
	int diameter = 0;
	bool repairment_status = 0;

	static Pipeline consoleInput() {
		
		Pipeline pipeline;
		std::string input;

		std::vector<std::string> patterns = {
			"\\d+\\.\\d+", 
			"\\d+"
		};

		std::vector<std::string> outputs = {
			"Enter a length [real number]: ",
			"Enter a diameter [integer]: "
		};

		std::vector<std::string> inputs(2);

		std::cout << "==============================" << std::endl;
		std::cout << "=== PIPELINE CREATION MODE ===" << std::endl;

		std::cout << "Enter a kilometer mark: ";
		std::getline(std::cin, pipeline.kilometer_mark);

		pipeline.repairment_status = false;
		
		for (int i{ 0 }; i < 2; i++) {
			
			while (true) {
				
				std::cout << outputs[i];
				std::cin >> input;

				std::regex pattern(patterns[i]);

				if (std::regex_match(input, pattern)) {
					inputs[i] = input;
					break;
				}
				else {
					std::cout << "Incorrect input! Try again!" << std::endl;
					std::cin.clear();
				}
			}
		}

		std::cout << "==============================" << std::endl;

		pipeline.length = std::stof(inputs[0]);
		pipeline.diameter = std::stoi(inputs[1]);

		std::cout.clear();

		return pipeline;
	}

	 void consoleOutput(Pipeline pipeline) {

		std::cout << "=== PIPELINE ===" << std::endl;
		std::cout << "Kilometer mark: " << pipeline.kilometer_mark << std::endl;
		std::cout << "Length: " << pipeline.length << " km" << std::endl;
		std::cout << "Diameter: " << pipeline.diameter << " mm" << std::endl;
		std::cout << "Repairment status: " << pipeline.repairment_status << std::endl;
		std::cout << "================" << std::endl << std::endl;

	}

	static Pipeline fileInput(std::string filepath) {
		
		Pipeline pipeline;

		std::string line;
		std::ifstream in(filepath);

		std::vector<std::string> patterns = {
			"([Kk]ilometer mark:)\\s*(.+)",
			"([Ll]ength:)\\s*(\\d+\\.\\d+)",
			"([Dd]iameter:)\\s*(\\d+)",
			"([Rr]epairment status:)\\s*(0|1)"
		};

		std::vector<std::string> inputs(4);

		if (in.is_open()) {
			
			while (std::getline(in, line)) {
			
				for (int i{ 0 }; i < 4; i++) {

					std::regex pattern(patterns[i]);
					std::smatch m;

					if (std::regex_match(line, m, pattern)) {
						inputs[i] = m[2];
					}
				}
			}
		}
		
		for (std::string element : inputs) {
			if (element == "") {

				std::cout << "Invalid file format for creating a new pipeline! Check file. It must have the following lines:" << std::endl;
				std::cout << "Kilometer mark: xxx" << std::endl;
				std::cout << "Length: (real number written with a dot!)" << std::endl;
				std::cout << "Diameter: (integer)" << std::endl;
				std::cout << "Repairment status: (0 if in work else 1)" << std::endl << std::endl;

				return pipeline;
			}
		}

		pipeline.kilometer_mark = inputs[0];
		pipeline.length = std::stof(inputs[1]);
		pipeline.diameter = std::stoi(inputs[2]);
		pipeline.repairment_status = std::stoi(inputs[3]);

		in.close();

		return pipeline;
	}

	void fileOutput(Pipeline pipeline, std::string filepath) {
		
		std::ofstream out(filepath, std::ios::app);

		std::vector<std::vector<std::string>> outputs = {
			{"Kilometer mark: ", pipeline.kilometer_mark},
			{"Length: ", std::to_string(pipeline.length), " km"},
			{"Diameter: ", std::to_string(pipeline.diameter), " mm"},
			{"Repairment status: ", std::to_string(pipeline.repairment_status)}
		};
		
		out << "* PIPELINE" << std::endl;

		if (out.is_open()) {
			for (int i{ 0 }; i < 4; i++) {
				
				std::string line;

				for (std::string element: outputs[i]) {
					line += element;
				}

				out << line << std::endl;
			}
		}

		out.close();
	}

	Pipeline repairmentStatusChanging(Pipeline pipeline) {

		std::string input;

		if (pipeline.length == 0.0 && pipeline.diameter == 0) {
			std::cout << "There is no created pipeline! Try again later..." << std::endl;
			return pipeline;
		}

		std::cout << "=============================" << std::endl;
		std::cout << "=== PIPELINE EDITING MODE ===" << std::endl;

		while (true) {
			std::cout << "Enter a new repairment status [0 - in work, 1 - in repair]: ";
			std::cin >> input;

			std::regex pattern("0|1");
			if (std::regex_match(input, pattern)) {
				pipeline.repairment_status = stoi(input);
				break;
			}
			else {
				std::cout << "Incorrect input! Try again!" << std::endl;
			}
		}

		std::cout << "=============================" << std::endl;

		return pipeline;
	}
};

class CompressorStation {
public:

	std::string name = "empty";
	int num_of_workshops = 0;
	int num_of_involved_workshops = 0;
	int station_class = 3;

	static CompressorStation consoleInput() {

		CompressorStation compressor_station;
		std::string input;

		std::vector<std::string> patterns = {
			"\\d+",
			"\\d+",
			"[1-3]"
		};

		std::vector<std::string> outputs = {
			"Enter a number of workshops: ",
			"Enter a number of currently involved workshops: ",
			"Enter a station class [1-3]: "
		};

		std::vector<std::string> inputs(3);

		std::cout << "========================================" << std::endl;
		std::cout << "=== COMPRESSOR STATION CREATION MODE ===" << std::endl;

		std::cout << "Enter station name: ";
		std::getline(std::cin, compressor_station.name);

		for (int i{ 0 }; i < 3; i++) {

			while (true) {

				std::cout << outputs[i];
				std::cin >> input;

				std::regex pattern(patterns[i]);

				if (std::regex_match(input, pattern)) {
					inputs[i] = input;
					break;
				}
				else {
					std::cout << "Incorrect input! Try again!" << std::endl;
					std::cin.clear();
				}
			}
		}

		std::cout << "========================================" << std::endl;

		if (std::stoi(inputs[1]) > std::stoi(inputs[0])) {
			std::cout << "Number of involved workshops can not be more than number of workshops!" << std::endl;
			return compressor_station;
		}

		compressor_station.num_of_workshops = std::stoi(inputs[0]);
		compressor_station.num_of_involved_workshops = std::stoi(inputs[1]);
		compressor_station.station_class = std::stoi(inputs[2]);

		std::cout.clear();

		return compressor_station;
	}

	void consoleOutput(CompressorStation compressor_station) {

		std::cout << "=== COMPRESSOR STATION ===" << std::endl;
		std::cout << "Station name: " << compressor_station.name << std::endl;
		std::cout << "Number of workshops: " << compressor_station.num_of_workshops << std::endl;
		std::cout << "Number of currently involved workshops: " << compressor_station.num_of_involved_workshops << std::endl;
		std::cout << "Station class: " << compressor_station.station_class << std::endl;
		std::cout << "==========================" << std::endl << std::endl;

	}

	static CompressorStation fileInput(std::string filepath) {

		CompressorStation compressor_station;

		std::string line;
		std::ifstream in(filepath);

		std::vector<std::string> patterns = {
			"([Ss]tation name:)\\s*(.+)",
			"([Nn]umber of workshops:)\\s*(\\d+)",
			"([Nn]umber of currently involved workshops:)\\s*(\\d+)",
			"([Ss]tation class:)\\s*([1-3])"
		};

		std::vector<std::string> inputs(4);

		if (in.is_open()) {

			while (std::getline(in, line)) {

				for (int i{ 0 }; i < 4; i++) {

					std::regex pattern(patterns[i]);
					std::smatch m;

					if (std::regex_match(line, m, pattern)) {
						inputs[i] = m[2];
					}
				}
			}
		}

		for (std::string element : inputs) {

			std::cout << element << std::endl;

			if (element == "") {

				std::cout << "Invalid file format for creating a new compressor station! Check file. It must have the following lines:" << std::endl;
				std::cout << "Station name: xxx" << std::endl;
				std::cout << "Number of workshops: (integer)" << std::endl;
				std::cout << "Number of currently involved workshops: (integer, less than number of workshops)" << std::endl;
				std::cout << "Station class: (1-3)" << std::endl << std::endl;

				return compressor_station;
			}
		}

		if (std::stoi(inputs[2]) > std::stoi(inputs[1])){
			std::cout << "Number of involved workshops can not be more than number of workshops" << std::endl;

			return compressor_station;
		}
		

		in.close();

		return compressor_station;
	}

	void fileOutput(CompressorStation compressor_station, std::string filepath) {

		std::ofstream out(filepath, std::ios::app);

		out << "* COMPRESSOR STATION" << std::endl;

		std::vector<std::vector<std::string>> outputs = {
			{"Station name: ", compressor_station.name},
			{"Number of workshops: ", std::to_string(compressor_station.num_of_workshops)},
			{"Number of currently involved workshops: ", std::to_string(compressor_station.num_of_involved_workshops)},
			{"Station class: ", std::to_string(compressor_station.station_class)}
		};

		if (out.is_open()) {
			for (int i{ 0 }; i < 4; i++) {

				std::string line;

				for (std::string element : outputs[i]) {
					line += element;
				}

				out << line << std::endl;
			}
		}

		out.close();
	}

	CompressorStation startStopWorkshop(CompressorStation compressor_station) {

		std::string input;

		if (compressor_station.num_of_involved_workshops == 0 && compressor_station.num_of_workshops == 0) {
			std::cout << "There is no created compressor stations! Try again later..." << std::endl;
			return compressor_station;
		}

		std::cout << "=======================================" << std::endl;
		std::cout << "=== COMPRESSOR STATION EDITING MODE ===" << std::endl;

		while (true) {
			std::cout << "Enter a parameter [0 - stop workshop, 1 - start workshop]: ";
			std::cin >> input;

			std::regex pattern("0|1");
			if (std::regex_match(input, pattern)) {
				if (input == "0") {
					if (compressor_station.num_of_involved_workshops > 0) {
						compressor_station.num_of_involved_workshops -= 1;
						std::cout << "Workshop had been stopped successfully! Total involved workshops: " << compressor_station.num_of_involved_workshops << std::endl;
						break;
					}
					else {
						std::cout << "All workshops are stopped now!";
						return compressor_station;
					}
				}
				else {
					if (compressor_station.num_of_involved_workshops < compressor_station.num_of_workshops) {
						compressor_station.num_of_involved_workshops += 1;
						std::cout << "Workshop had been started successfully! Total involved workshops: " << compressor_station.num_of_involved_workshops << std::endl;
						break;
					}
					else {
						std::cout << "All workshops are involved now!" << std::endl;
						return compressor_station;
					}
				}
			}
			else {
				std::cout << "Incorrect input! Try again!" << std::endl;
			}
		}

		std::cout << "=======================================" << std::endl;

		return compressor_station;
	}
};

void clear() {
	
	// https://ru.stackoverflow.com/questions/471914/%D0%9E%D1%87%D0%B8%D1%81%D1%82%D0%BA%D0%B0-%D0%BA%D0%BE%D0%BD%D1%81%D0%BE%D0%BB%D0%B8

	std::cout << "\033[2J\033[1;1H";

}

void continuing() {

	std::string smthng;

	std::cout << "Enter any key to continue..." << std::endl;
	std::cin >> smthng;

	std::cout << "=================================" << std::endl;
}

int main() {

	Pipeline pipeline;
	CompressorStation compressor_station;

	std::ofstream out("test_output.txt");
	out.close();

	while (true) {
		
		clear();

		std::string input;
		int command;
		std::regex pattern("[0-7]");

		std::cout << "=== HYDROCARBON TRANSPORTATION ===" << std::endl;
		std::cout << "1. Create new pipeline" << std::endl;
		std::cout << "2. Create new compressor station" << std::endl;
		std::cout << "3. Show all objects" << std::endl;
		std::cout << "4. Editing pipeline" << std::endl;
		std::cout << "5. Editing compressor station" << std::endl;
		std::cout << "6. Save in file" << std::endl;
		std::cout << "7. Load from file" << std::endl;
		std::cout << "=================================" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "=================================" << std::endl;
		std::cout << "Enter a command [0-7]: ";
		std::cin >> input;

		if (std::regex_match(input, pattern)) {

			command = std::stoi(input);

		}

		else {

			std::cout << "Invalid command! Try again..." << std::endl;

			continuing();
			continue;
		}
		
		std::cout << "=================================" << std::endl << std::endl;

		clear();

		switch (command) {

		case 0:
			return 0;

		case 1:

			pipeline = pipeline.consoleInput();

			continuing();
			continue;

		case 2:

			compressor_station = compressor_station.consoleInput();

			continuing();
			continue;

		case 3:

			pipeline.consoleOutput(pipeline);
			compressor_station.consoleOutput(compressor_station);

			continuing();
			continue;

		case 4:
			
			pipeline = pipeline.repairmentStatusChanging(pipeline);

			continuing();
			continue;

		case 5:

			compressor_station = compressor_station.startStopWorkshop(compressor_station);

			continuing();
			continue;

		case 6:

			pipeline.fileOutput(pipeline, "test_output.txt");
			compressor_station.fileOutput(compressor_station, "test_output.txt");

			continuing();
			continue;

		case 7:

			pipeline = pipeline.fileInput("test_input.txt");
			compressor_station = compressor_station.fileInput("test_input.txt");

			continuing();
			continue;
		}
	}
}