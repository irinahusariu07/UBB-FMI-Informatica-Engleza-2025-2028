#include "ActionRemove.h"

void ActionRemove::executeUndo()
{
	this->repo.addSong(deleteSong);
}

void ActionRemove::executeRedo()
{
	this->repo.removeSong(deleteSong);
}