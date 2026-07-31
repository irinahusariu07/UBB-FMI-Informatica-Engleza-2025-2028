#pragma once
#include "Song.h"
#include "DynamicVector.h"
#include <vector>
//replace with stl vector and change every function accordingly 

class Repository
{
private:
	//DynamicVector<Song> songs;
	std::vector<Song> songs;

public:
	/*
		Default constructor.
	*/
	Repository() {}

	/*
		Adds a song to the repository.
		Input: s - Song.
		Output: the song is added to the repository.
	*/
	void addSong(const Song& s);

	/*
		Finds a song, by artist and title.
		Input: artist, title - string
		Output: the song that was found, or an "empty" song (all fields empty and duration 0), if nothing was found.
	*/
	Song findByArtistAndTitle(const std::string& artist, const std::string& title);

	//DynamicVector<Song> getSongs() const { return songs; }
	const std::vector<Song> getSongs() const { return songs; }
};