#include "Repository.h"
#include <string>
#include <algorithm>

using namespace std;

void Repository::addSong(const Song& s)
{
	//this->songs.add(s);
	this->songs.push_back(s);
}

Song Repository::findByArtistAndTitle(const std::string& artist, const std::string& title)
{
    //return an iterator to the first element that matches the condition
    auto it = std::find_if(this->songs.begin(), this->songs.end(), 
        [&](const Song& s) {
            return s.getArtist() == artist && s.getTitle() == title;
        });

    //if the iterator reaches the end => no match 
    if (it != this->songs.end())
    {
        return *it; //dereference the iterator to get the Song object
    }

    return Song{}; //return empty song if not found
}