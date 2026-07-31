#pragma once
#include "Song.h"
#include "DynamicArray.h"

class Repo
{
private:
	DynamicArray da;
public:
	void add(const Song& s);
	int get_size() const;
};

