#pragma once
#include "Action.h"
#include "C:\\Users\\irina\\Desktop\\facultate\\OOP\\seminars\\Playlist - polymoprhic undo - stub\\Playlist\\Song.h"
#include "C:\\Users\\irina\\Desktop\\facultate\\OOP\\seminars\\Playlist - polymoprhic undo - stub\\Playlist\\Repository.h"

class ActionRemove : public Action
{
private:
	Song deleteSong; 
	Repository& repo;

public:
	ActionRemove(Song deleteSong, Repository& repo) : deleteSong{ deleteSong }, repo{ repo } {}
	void executeUndo() override;
	void executeRedo() override; 
};

