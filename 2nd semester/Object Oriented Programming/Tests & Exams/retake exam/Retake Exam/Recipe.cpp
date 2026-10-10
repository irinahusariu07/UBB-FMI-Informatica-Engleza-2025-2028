#include "Recipe.h"

std::string Recipe::formatIng()
{
    std::string list; 
	for (int i = 0; i < ingredients.size(); i++)
	{
		list += ingredients[i];
		if (i < ingredients.size() - 1) list += ',';
	}
	return list;
}
