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
#include <set>
#include <list>
#include <queue>


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
int getID();


