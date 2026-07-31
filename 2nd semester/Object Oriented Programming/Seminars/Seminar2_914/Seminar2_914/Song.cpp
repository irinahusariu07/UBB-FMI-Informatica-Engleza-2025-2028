#include "Song.h"

Duration::Duration(int minutes, int seconds)
{
	this->minutes = minutes;
	this->seconds = seconds;
}

Song::Song(const std::string& artist, const std::string& title, const std::string& link, int minutes, int seconds)
{
	this->artist = artist;
	this->title = title;
	this->link = link;
	Duration d{ minutes, seconds };
	this->duration = d;
}
