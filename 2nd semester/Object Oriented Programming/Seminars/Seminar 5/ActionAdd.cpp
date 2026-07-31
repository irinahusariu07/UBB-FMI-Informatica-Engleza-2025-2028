#include "ActionAdd.h"

void ActionAdd::executeUndo()
{
	this->repo.removeSong(addedSong); 
}

void ActionAdd::executeRedo()
{
	this->repo.addSong(addedSong);
}

