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

class Metadata {
private:

	int id;

public:

	void setID(int new_id) { id = new_id; }
	const int &getID() const { return id; }
};

class Pipeline {
private:
	
	int id;
	std::string name; // kilometer mark
	float length;
	int diameter;
	bool status; // repairment status

public:

	Pipeline(Metadata md, std::string n, float l, int d, bool s) {

		id = md.getID();
		name = n;
		length = l;
		diameter = d;
		status = s;

	}

	void setStatus(bool new_status) { status = new_status; }

	const int &getID() const { return id; }
	const std::string &getName() const { return name; }
	const float &getLength() const { return length; }
	const int &getDiameter() const { return diameter; }
	const bool &getStatus() const { return status; }

	void pipelineConsoleInput() {

		cin_clear();
		
		std::cout << "=== COMPRESSOR CREATION MODE ===" << std::endl;
		std::cout << "Enter pipeline name: "; std::getline(std::cin>>std::ws, name);
		std::cout << "Pipeline length. "; length = real();
		std::cout << "Pipeline diameter. "; diameter = integer();
		status = 0;
	}

	void pipelineFileInput(std::string filepath) {
		std::regex line_pattern("^\\s*(\\d+)\\s*;\\s*p\\s*;\\s*(.+)\\s*;\\s*(\\d+\\.\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(0|1)\\s*$");
		std::smatch match;
		std::ifstream file(filepath);
		std::string line;

		if (file.is_open()) {
			while (std::getline(file, line)) {
				if (std::regex_match(line, match, line_pattern)) {
					id = std::stoi(match[1]);
					name = match[2];
					length = std::stof(match[3]);
					diameter = std::stoi(match[4]);
					status = std::stoi(match[5]);
				};
			}
		}
	}
};

class CompressorStation {
private:

	int id;
	std::string name;
	int workshops;
	int involved_workshops;
	char rang; // station class

public:

	CompressorStation(Metadata md, std::string n, int w, int iw, char r) {

		id = md.getID();
		name = n;
		workshops = w;
		involved_workshops = iw;
		rang = r;

	}

	void setIW(int new_iw) { involved_workshops = new_iw; }

	const int &getID() const { return id; }
	const std::string &getName() const { return name; }
	const float &getWorkshops() const { return workshops; }
	const int &getIW() const { return involved_workshops; }
	const bool &getRang() const { return rang; }

	void csConsoleInput() {

		cin_clear();

		std::cout << "=== COMPRESSOR CREATION MODE ===" << std::endl;
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

	}

	void csFileInput(std::string filepath) {

		std::regex line_pattern("^\\s*(\\d+)\\s*;\\s*cs\\s*;\\s*(.+)\\s*;\\s*(\\d+)\\s*;\\s*(\\d+)\\s*;\\s*(A|B|C|D|E)\\s*$");
		std::smatch match;
		std::ifstream file(filepath);
		std::string line;

		if (file.is_open()) {
			while (std::getline(file, line)) {
				if (std::regex_match(line, match, line_pattern)) {
					if (0 < std::stoi(match[4]) < std::stoi(match[3])) {
						id = std::stoi(match[1]);
						name = match[2];
						workshops = std::stoi(match[3]);
						involved_workshops = std::stoi(match[4]);
						rang = match[5].str().c_str()[0];
					};
				};
			}
		}
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

			continuing(); continue;
		case 2:
			cs = csConsoleInput();

			continuing(); continue;
		case 3:
		
			continuing(); continue;
		case 4:
			continuing(); continue;
		case 5:
				continuing(); continue;
		case 6:
		case 7:
			continuing(); continue;
		}
	}
}