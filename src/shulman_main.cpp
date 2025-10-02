#include <iostream>
#include <fstream>
#include <vector>
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
};

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

		if (std::cin.fail() || rang < 'A' || rang > 'E') {
			std::cout << "Invalid value! Please, try again." << std::endl;
			cin_clear();
		}
		else {
			break;
		}
	}
	cin_clear();

	return rang;
}

int boolean() {
	int boolean;

	while (true) {
		std::cout << "Enter boolean: ";
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

struct Pipeline {
	std::string name = ""; // kilometer mark
	float length = 0;
	int diameter = 0;
	bool status = -1; // repairment status
};

struct CompressorStation {
	std::string name = "";
	int workshops = 0;
	int involved_workshops = 0;
	char rang = 0; // station class
};

Pipeline pipelineConsoleInput() {
	Pipeline p;

	//cin_clear();

	std::cout << "=== COMPRESSOR CREATION MODE ===" << std::endl << "Enter pipeline name: ";
	std::getline(std::cin>>std::ws, p.name);
	std::cout << "Pipeline length. ";
	p.length = real();
	std::cout << "Pipeline diameter. ";
	p.diameter = integer();
	p.status = 0;

	return p;
}

void pipelineConsoleOutput(Pipeline pipeline) {
	std::cout << "=== PIPELINE ===" << std::endl
	<< "Kilometer mark: " << pipeline.name << std::endl
	<< "Length: " << pipeline.length << " km" << std::endl
	<< "Diameter: " << pipeline.diameter << " mm" << std::endl
	<< "Repairment status: " << pipeline.status << std::endl;

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

	std::cout << "There is some troubles with specified file! There is no pipeline! Check it";
	return pipeline;
}

void pipelineFileOutput(std::string filepath, Pipeline pipeline) {
	std::ofstream file(filepath, std::ios::app);

	if (file.is_open()) {
		file << "p;" << pipeline.name << ";" << pipeline.length << ";" << pipeline.diameter << ";" << pipeline.status << std::endl;
	}
}

void pipelineStatusChanging(Pipeline& pipeline) {
	int status;

	std::cout << "Change repairment status [0 if not in repair else 1]: ";

	status = boolean();
	pipeline.status = status;

}

CompressorStation csConsoleInput() {
	CompressorStation cs;

	cin_clear();

	std::cout << "=== COMPRESSOR CREATION MODE ===" << std::endl << "Enter a station name: ";
	std::getline(std::cin, cs.name);
	std::cout << "Number of workshops. ";
	cs.workshops = integer();
	std::cout << "Number of involved workshops. ";
	while (true) {
		cs.involved_workshops = integer();
		if (cs.involved_workshops > cs.workshops) {
			std::cout << "Number of involved workshops cannot be more than total workshops! ";
		}
		else {
			break;
		}
	}
	std::cout << "Station class. ";
	cs.rang = rang();

	return cs;
}

void csConsoleOutput(CompressorStation cs) {
	std::cout << "=== COMPRESSOR STATION ===" << std::endl
	<< "Station name: " << cs.name << std::endl
	<< "Number of workshops: " << cs.workshops << std::endl
	<< "Number of involved workshops: " << cs.involved_workshops << std::endl
	<< "Station class: " << cs.rang << std::endl;
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

	std::cout << "There is some troubles with specified file! There is no comperessor station! Check it";
	return cs;
}

void csFileOutput(std::string filepath, CompressorStation cs) {
	std::ofstream file(filepath, std::ios::app);

	if (file.is_open()) {
		file << "cs;" << cs.name << ";" << cs.workshops << ";" << cs.involved_workshops << ";" << cs.rang << std::endl;
	}
}

void csInvolvedWorkshopsChanging(CompressorStation& cs) {
	bool flag;

	std::cout << "What do you want to do?\n1 - start one workshop, 0 - stop one workshop" << std::endl;

	std::cout << "What do you want to do? ";
	flag = boolean();
	if (flag == 1) {
		cs.involved_workshops++;
		if (cs.involved_workshops > cs.workshops) { std::cout<<"Number of involved workshops cannot be more than total workshops"<<std::endl; cs.involved_workshops--; }
	}
	else {
		cs.involved_workshops--;
		if (cs.involved_workshops < 0) { std::cout<<"Number of involved workshops cannot be less than 0"<<std::endl; cs.involved_workshops++; }
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

int main() {
	Pipeline pipeline;
	CompressorStation cs;
	std::string path = "test.txt";

	while (true) {
		clear();

		std::string input;
		int command;
		std::regex pattern("[0-7]");

		std::cout << "=== HYDROCARBON TRANSPORTATION ===" << std::endl
			<< "1. Create new pipeline" << std::endl
			<< "2. Create new compressor station" << std::endl
			<< "3. Show all objects" << std::endl
			<< "4. Editing pipeline" << std::endl
			<< "5. Editing compressor station" << std::endl
			<< "6. Save in file" << std::endl
			<< "7. Load from file" << std::endl
			<< "0. Exit" << std::endl
			<< "=================================" << std::endl;

		std::cout << "Enter a command [0-7]: ";
		std::cin >> input;

		if (std::regex_match(input, pattern)) {
			command = std::stoi(input);
		}

		else {
			std::cout << "Invalid command! Try again!" << std::endl;

			continuing(); continue;
		}

		clear();

		switch (command) {
		case 0:
			return 0;
		case 1:
			pipeline = pipelineConsoleInput();

			continuing(); continue;
		case 2:
			cs = csConsoleInput();

			continuing(); continue;
		case 3:
			if (pipeline.diameter != 0) { pipelineConsoleOutput(pipeline); }
			else { std::cout << "There is no created pipeline!" << std::endl; }
			if (cs.workshops != 0) { csConsoleOutput(cs); }
			else { std::cout << "There is no created compressor station!" << std::endl; }

			continuing(); continue;
		case 4:
			if (pipeline.diameter != 0) { pipelineStatusChanging(pipeline); }
			else { std::cout << "There is no created pipeline!" << std::endl; }

			continuing(); continue;
		case 5:
			if (cs.workshops != 0) { csInvolvedWorkshopsChanging(cs); continuing(); continue; }
			else {
				std::cout << "There is no created compressor station!" << std::endl;

				continuing(); continue;
		case 6:
		{
			std::ofstream file(path);
			file.close();

			if (pipeline.diameter != 0) { pipelineFileOutput(path, pipeline); }
			else { std::cout << "There is no created pipeline!" << std::endl; }
			if (cs.workshops != 0) { csFileOutput(path, cs); }
			else { std::cout << "There is no created compressor station!" << std::endl; }

			std::cout << "Loading in file process had ended" << std::endl;

			continuing(); continue;
		}
		case 7:
			pipeline = pipelineFileInput(path);
			cs = csFileInput(path);

			std::cout << "Loading from file process had ended" << std::endl;

			continuing(); continue;
			}
		}
	}
}