#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "MovieDatabase.h"

#include <list>
#include <forward_list>

template<class It>
void f(It a, It b)
{
    std::cout << (a==b) << std::endl;
}


void movie_database_test()
{
    MovieDatabase md;

    md.insert("ACTION", "THE MATRIX");
    md.insert("ACTION", "BATMAN BEGINS");
    md.insert("ACTION", "BATMAN BEGINS");
    md.insert("DRAMA", "THE AVIATOR");
    md.insert("DRAMA", "MILLION DOLLAR BABY");
    md.insert("HORROR", "HELLRAISER");

    md.print(); std::cout << '\n';
    md.search("AT"); std::cout << '\n';

    md.remove("HORROR", "HELLRAISER");
    md.print(); std::cout << '\n';
}

void test()
{
    //using List = LinkedList < std::string > ;
    using List = std::forward_list < std::string > ;
    
    List l;
    
    l.begin() == l.end();
    
    auto i = l.insert_after(l.before_begin(), "haha");
    i = l.insert_after(i, "haha2");
    i = l.insert_after(i, "haha3");
    l.push_front("front?");

    for (auto& x : l)
        std::cout << x << std::endl;
    std::cout << l.empty() << std::endl;
}

MovieDatabase database;

void process(std::string& line)
{
    std::vector<std::string> temp_tokens;
    boost::split(temp_tokens, line, boost::is_any_of("%"));
    std::for_each(temp_tokens.begin(), temp_tokens.end(),
        [](std::string& x){ boost::trim(x); });

    std::vector<std::string> tokens;
    std::copy_if(temp_tokens.begin(), temp_tokens.end(), std::back_inserter(tokens),
        [](std::string& x){ return !x.empty(); });


    if (tokens[0] == "INSERT")
    {
        if (tokens.size() != 3) throw std::invalid_argument("invalid input.");
        database.insert(tokens[1], tokens[2]);
    }
    else if (tokens[0] == "DELETE")
    {
        if (tokens.size() != 3) throw std::invalid_argument("invalid input.");
        database.remove(tokens[1], tokens[2]);
    }
    else if (tokens[0] == "SEARCH")
    {
        if (tokens.size() != 2) throw std::invalid_argument("invalid input.");
        database.search(tokens[1]);
    }
    else if (tokens[0] == "PRINT")
    {
        if (tokens.size() != 1) throw std::invalid_argument("invalid input.");
        database.print();
    }
    else
    {
        throw std::invalid_argument("invalid input.");
    }
}

int main()
{
    test();

    for (std::string line; std::getline(std::cin, line);)
    {
        if (line == "QUIT")
            break;

        try
        {
            process(line);
        }
        catch (std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}