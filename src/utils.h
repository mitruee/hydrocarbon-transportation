#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <list>
#include <stack>
#include <set>


class Pipeline;
class CompressorStation;

#define INPUT_LINE(in, str) getline(in>>std::ws, str); std::cerr << str << std::endl

#define PRINT_PARAM(out, x) out << #x << "=" << x << std::endl

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
    }
	void redirect (std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename T>
T getCorrectValue(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()
		|| std::cin.peek() != '\n'
		|| x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Enter value (" << min << "-" << max << "): ";
	}
	std::cerr << x << std::endl;
	return x;
}

void move_terminal();
void update_network(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, CompressorStation> css, int max_id);
int getID();
void getMaxID(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, int& max_id);

void pipelineCreation(std::unordered_map<int, Pipeline>& pls);
void csCreation(std::unordered_map<int, CompressorStation>& css, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, std::unordered_map<int, int>>& network, int& max_id);

void printMainMenu();

void printObjectManagementMenu(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::vector<int> ids);
int objectManagementLogic(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int max_id);
void searchSomething(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::vector<int>& ids);
void deleteSomething(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, std::unordered_map<int, std::unordered_map<int, int>>& network, std::vector<int>& ids);
void editSomething(std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, std::vector<int>& ids, int max_id);
void connectGTN(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation> css, int max_id);
void plsFilter(std::unordered_map<int, Pipeline> pls, std::vector<int>& ids);
void cssFilter(std::unordered_map<int, CompressorStation> css, std::vector<int>& ids);

void saveInFile(std::unordered_map<int, Pipeline> pls, std::unordered_map<int, CompressorStation> css, std::unordered_map<int, std::unordered_map<int, int>> network, int max_id);
void loadFromFile(std::unordered_map<int, std::unordered_map<int, int>>& network, std::unordered_map<int, Pipeline>& pls, std::unordered_map<int, CompressorStation>& css, int& max_id);

