#include <iostream>
#include <string>
#include "LinkedList.h"
#include <list>
void test()
{
    std::list<int> lst;
    lst.insert(lst.end(), 1);
    lst.insert(lst.end(), 2);
    lst.insert(lst.begin(), 3);

    for(auto x : lst)
        std::cout << x << std::endl;
}

void process(std::string &line)
{
}

int main()
{
    test();

    for(std::string line; std::getline(std::cin, line); )
    {
        if(line == "quit")
            break;

        try
        {
            process(line);
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}