#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>


void process(std::string &line)
{
	std::vector<std::string> split_vector;

	boost::split(split_vector, line, boost::is_any_of("\t "), boost::token_compress_on);

	for(auto &x : split_vector)
	{
		std::cout << x << std::endl;
	}
}

int main() 
{
	for(std::string line; std::getline(std::cin, line); )
	{
		if(line == "quit")
			break;

		process(line);
	}
}