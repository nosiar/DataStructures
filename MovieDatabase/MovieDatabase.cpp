#include "MovieDatabase.h"
#include <iostream>
#include <algorithm>

void MovieDatabase::insert(const std::string& genre, const std::string& title)
{
    auto genre_it = std::find_if(genre_list.begin(), genre_list.end(),
        [&genre](LinkedList<std::string> const & x){ return *x.begin() > genre; });
    --genre_it;

    if (genre_it != genre_list.before_begin() && *genre_it->cbegin() == genre)
    {
        auto movie_it = std::find_if(++genre_it->cbegin(), genre_it->cend(),
            [&title](std::string const & x){ return x > title; });
        --movie_it;

        if (movie_it == genre_it->begin() || *movie_it != title)
        {
            genre_it->insert_after(movie_it, std::move(title));
        }
    }
    else
    {
        LinkedList<std::string> new_movie_list;
        auto movie_it = new_movie_list.before_begin();
        movie_it = new_movie_list.insert_after(movie_it, genre);
        new_movie_list.insert_after(movie_it, title);

        genre_list.insert_after(genre_it, std::move(new_movie_list));
    }
}
void MovieDatabase::remove(const std::string& genre, const std::string& title)
{
    auto genre_it = std::find_if(genre_list.begin(), genre_list.end(),
        [&genre](LinkedList<std::string> const & x){ return *x.begin() == genre; });

    if (genre_it != genre_list.end())
    {
        auto movie_it = std::find_if(++genre_it->cbegin(), genre_it->cend(),
            [&title](std::string const & x){ return x == title; });

        if (movie_it != genre_it->end())
        {
            genre_it->erase_after(--movie_it);
        }

        if (genre_it->size() == 1)
        {
            genre_list.erase_after(--genre_it);
        }
    }
}
void MovieDatabase::search(const std::string& keyword) const
{
    for (auto& x : genre_list)
    {
        auto it = x.begin();
        auto end_it = x.end();

        std::string genre = *it++;

        while (it != end_it)
        {
            if (it->find(keyword) != std::string::npos)
            {
                std::cout << '(' << genre << ", " << *it << ")\n";
            }
            ++it;
        }
    }
}
void MovieDatabase::print() const
{
    for (auto& x : genre_list)
    {
        auto it = x.begin();
        auto end_it = x.end();

        std::string genre = *it++;

        while (it != end_it)
        {
            std::cout << '(' << genre << ", " << *it++ << ")\n";
        }

    }
}