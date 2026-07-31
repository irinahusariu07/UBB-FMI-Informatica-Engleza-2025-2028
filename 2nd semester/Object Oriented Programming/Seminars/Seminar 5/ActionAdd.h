#pragma once
#include "Action.h"
#include "C:\\Users\\irina\\Desktop\\facultate\\OOP\\seminars\\Playlist - polymoprhic undo - stub\\Playlist\\Song.h"
#include "C:\\Users\\irina\\Desktop\\facultate\\OOP\\seminars\\Playlist - polymoprhic undo - stub\\Playlist\\Repository.h"
class ActionAdd : public Action
{
private:
	Song addedSong; 
	Repository& repo;

public:
	ActionAdd(Song addedSong, Repository& repo) : addedSong{ addedSong }, repo{ repo } {}
	void executeUndo() override; 
	void executeRedo() override; 
};

