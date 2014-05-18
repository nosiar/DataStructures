#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include "BigInteger.h"

void test()
{
    std::cout << BigInteger("23367") + BigInteger("11748") << '\n';
    std::cout << BigInteger("23367") + BigInteger("+11748") << '\n';
    std::cout << BigInteger("23367") + BigInteger("-11748") << '\n';

    std::cout << BigInteger("+23367") + BigInteger("11748") << '\n';
    std::cout << BigInteger("+23367") + BigInteger("+11748") << '\n';
    std::cout << BigInteger("+23367") + BigInteger("-11748") << '\n';

    std::cout << BigInteger("-23367") + BigInteger("11748") << '\n';
    std::cout << BigInteger("-23367") + BigInteger("+11748") << '\n';
    std::cout << BigInteger("-23367") + BigInteger("-11748") << "\n\n";

    std::cout << BigInteger("23367") - BigInteger("11748") << '\n';
    std::cout << BigInteger("23367") - BigInteger("+11748") << '\n';
    std::cout << BigInteger("23367") - BigInteger("-11748") << '\n';

    std::cout << BigInteger("+23367") - BigInteger("11748") << '\n';
    std::cout << BigInteger("+23367") - BigInteger("+11748") << '\n';
    std::cout << BigInteger("+23367") - BigInteger("-11748") << '\n';

    std::cout << BigInteger("-23367") - BigInteger("11748") << '\n';
    std::cout << BigInteger("-23367") - BigInteger("+11748") << '\n';
    std::cout << BigInteger("-23367") - BigInteger("-11748") << "\n\n";

    std::cout << BigInteger("123456") - BigInteger("123456") << '\n';
    std::cout << BigInteger("999999") - BigInteger("-1") << '\n';
    std::cout << BigInteger("0") - BigInteger("0") << "\n\n";

    std::cout << +BigInteger("123") << '\n';
    std::cout << -BigInteger("123") << '\n';
    std::cout << BigInteger("1") + BigInteger("2") + BigInteger("3") << '\n';
}

bool is_operator(std::string token)
{
    return token.find_first_of("+-*/") != std::string::npos;
}

void process(std::string &line)
{
    // Type alias are not supported in VC11
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
    test();

    for(std::string line; std::getline(std::cin, line); )
    {
        if(line == "quit")
            break;

        process(line);
    }
}