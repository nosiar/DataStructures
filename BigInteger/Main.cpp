#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>


bool is_operator(std::string token)
{
	return token.find_first_of("+-*/") != std::string::npos;
}

void process(std::string &line)
{
	// Alias templates are not supported in VC11
	// using tokenizer = boost::tokenizer<boost::char_separator<char>>;
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

	boost::char_separator<char> sep("\t ", "+-*/");

	tokenizer tokens(line, sep);

	for(auto &x : tokens)
	{
		std::cout << "<" << x << "> " << is_operator(x) << std::endl;
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