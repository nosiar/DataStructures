#pragma once

#include <string>
#include "LinkedList.h"

class MovieDatabase
{
public:
    void insert(const std::string& genre, const std::string& title);
    void remove(const std::string& genre, const std::string& title);
    void search(const std::string& keyword) const;
    void print() const;

private:
    LinkedList<LinkedList<std::string>> genre_list;
};