#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

struct Pipeline {
	
	std::string name; // kilometer mark
	float length;
	int diameter;
	bool status; // repairment status

};

struct CompressorStation {

	std::string name;
	int workshops;
	int involved_workshops;
	char rang; // station class

};

Pipeline pipelineConsoleInput() {

	Pipeline pipeline;

	std::cout << "Enter a kilometer mark: " << std::endl;
	std::cin >> pipeline.name;
	pipeline.status = 0;

	std::vector<std::string> outputs = {"Enter a length [real number]: ", "Enter a diameter [integer]: "};
	std::vector<std::string> patterns = {"\\d+\\.\\d+", "\\d+"};
	std::vector<std::string> inputs(2);
	std::string input;

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
				std::cout << "Invalid value! Try again!" << std::endl;
			}
		}
	}

	pipeline.length = std::stof(inputs[0]);
	pipeline.diameter = std::stoi(inputs[1]);

	return pipeline;
}

void pipelineConsoleOutput(Pipeline pipeline) {

	std::cout << "Kilometer mark: " << pipeline.name << std::endl;
	std::cout << "Length: " << pipeline.length << " km" << std::endl;
	std::cout << "Diameter: " << pipeline.diameter << " mm" << std::endl;
	std::cout << "Repairment status: " << pipeline.status << std::endl;

}

Pipeline pipelineFileInput(std::string filepath) {

	Pipeline pipeline;

	std::regex line_pattern("^\\s*p\\s*;\\s*(.+)\\s*;\\s*(\\d+\\.\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(0|1)\\s*$");
	std::smatch match;
	std::ifstream file(filepath);
	std::string line;

	if (file.is_open()) {

		while (std::getline(file, line)) {

			if (std::regex_match(line, match, line_pattern)) {

				pipeline.name = match[1];
				pipeline.length = std::stof(match[2]);
				pipeline.diameter = std::stoi(match[3]);
				pipeline.status = std::stoi(match[4]);

				return pipeline;
			};
		}
	}

	std::cout << "There is some troubles with specified file! Check it";
	return;
}

void pipelineFileOutput(std::string filepath, Pipeline pipeline) {

	std::ofstream file(filepath, std::ios::app);

	if (file.is_open()) {

		file << "p;" << pipeline.name << ";" << pipeline.length << ";" << pipeline.diameter << ";" << pipeline.status << std::endl;
	}
}

Pipeline pipelineStatusChanging(Pipeline pipeline) {

	std::regex pattern("0|1");
	std::string input;

	while (true) {

		std::cin >> input;

		if (std::regex_match(input, pattern)) {

			pipeline.status = std::stoi(input);
			break;
		}
	}
}

CompressorStation csConsoleInput() {

	CompressorStation cs;

	std::cout << "Enter a station name: ";
	std::cin >> cs.name;

	std::vector<std::string> outputs = { "Enter a number of workshops: ", "Enter a number of involved workshops: " };
	std::vector<std::string> patterns = { "\\d+", "\\d+", "A|B|C|D|E"};
	std::vector<std::string> inputs(3);
	std::string input;

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
				std::cout << "Invalid value! Try again!" << std::endl;
			}
		}
	}

	cs.workshops = std::stof(inputs[0]);
	cs.involved_workshops = std::stoi(inputs[1]);
	cs.rang = inputs[2].c_str()[0];

	return cs;
}

void csConsoleOutput(CompressorStation cs) {

	std::cout << "Station name: " << cs.name << std::endl;
	std::cout << "Number of workshops: " << cs.workshops << " km" << std::endl;
	std::cout << "Number of involved workshops: " << cs.involved_workshops << " mm" << std::endl;
	std::cout << "Station class: " << cs.rang << std::endl;

}

CompressorStation csFileInput(std::string filepath) {

	CompressorStation cs;

	std::regex line_pattern("^\\s*cs\\s*;\\s*(.+)\\s*;\\s*(\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(A|B|C|D|E)\\s*$");
	std::smatch match;
	std::ifstream file(filepath);
	std::string line;

	if (file.is_open()) {

		while (std::getline(file, line)) {

			if (std::regex_match(line, match, line_pattern)) {

				cs.name = match[1];
				cs.workshops = std::stoi(match[2]);
				cs.involved_workshops = std::stoi(match[3]);
				cs.rang = match[4].str().c_str()[0];

				return cs;
			};
		}
	}

	std::cout << "There is some troubles with specified file! Check it";
	return;
}

void pipelineFileOutput(std::string filepath, CompressorStation cs) {

	std::ofstream file(filepath, std::ios::app);

	if (file.is_open()) {

		file << "cs;" << cs.name << ";" << cs.workshops << ";" << cs.involved_workshops << ";" << cs.rang << std::endl;
	}
}

CompressorStation csInvolvedWorkshopsChanging(CompressorStation cs) {

	std::regex pattern("R|S");
	std::string input;

	std::cout << "What do you want to do?\nR - start one workshop, S - stop one workshop\nEnter your choice here: ";
	int current = cs.workshops - cs.involved_workshops;

	if (0 <= current <= cs.workshops) {
		while (true) {

			std::cin >> input;

			if (std::regex_match(input, pattern)) {

				if (input == "R") {

					cs.workshops++;
				}
				else {
					cs.workshops--;
				}
			}

			std::cout << "Invalid value! Try again!" << std::endl;
		}
	}
	else {
		std::cout << "Something goes wrong! Check number of involved workshops!";
	}
}

void clear() {

	// https://ru.stackoverflow.com/questions/471914/%D0%9E%D1%87%D0%B8%D1%81%D1%82%D0%BA%D0%B0-%D0%BA%D0%BE%D0%BD%D1%81%D0%BE%D0%BB%D0%B8

	std::cout << "\033[2J\033[1;1H";

}

void continuing() {

	std::string smthng;

	std::cout << "Enter any key to continue..." << std::endl;
	std::cin >> smthng;

}

void main() {

	Pipeline pipeline;
	CompressorStation compressor_station;

	while (true) {

		clear();

		std::string input;
		int command;
		std::regex pattern("[0-7]");

		std::cout << "=== HYDROCARBON TRANSPORTATION ===" << std::endl << "1. Create new pipeline" << std::endl << "2. Create new compressor station" << std::endl;
		std::cout << "3. Show all objects" << std::endl << "4. Editing pipeline" << std::endl << "5. Editing compressor station" << std::endl;
		std::cout << "6. Save in file" << std::endl << "7. Load from file" << std::endl << "0. Exit" << std::endl << "=================================" << std::endl;

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

		clear();
}