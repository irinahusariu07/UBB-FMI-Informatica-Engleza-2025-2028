#include "Controller.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

void Controller::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->repo.addSong(s);
}

void Controller::addSongToPlaylist(const Song& song)
{
	Song found = this->repo.findByArtistAndTitle(song.getArtist(), song.getTitle());
	this->playlist.push_back(song);
}

void Controller::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	// get all the songs from the repository
	//DynamicVector<Song> songs = this->repo.getSongs();

	// use STL algorithms and lambdas
	std::vector<Song> allSongs = this->repo.getSongs();

	// filter and copy songs by artist 
	// back_inserter ????????????? automatically calls push_back on this->playlist for each match
	std::copy_if(allSongs.begin(), allSongs.end(), std::back_inserter(this->playlist),
		[&artist](const Song& s) {
			return s.getArtist() == artist;
		});
}