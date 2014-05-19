#include <iostream>
#include <string>

void process(std::string &line)
{
}

int main()
{
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