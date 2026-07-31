#pragma once
#include <string>
class Duration 
{
private:
	int minutes;
	int seconds;
public:
	Duration(int minutes=0, int seconds=0);
};

class Song
{
private:
	std::string artist;
	std::string title;
	std::string link;
	Duration duration;
public:
	Song(const std::string& artist = "", const std::string& title = "", const std::string& link = "", int minutes = 0, int seconds = 0);

	std::string getArtist() const { return artist; }
	std::string getTitle() const { return title; }
	std::string getLink() const { return link; }
};

