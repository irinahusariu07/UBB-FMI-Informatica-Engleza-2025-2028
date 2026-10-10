#include <iostream>
#include <string>
#include "UI.h"
int main()
{
	Service s; 
	UI u{ s }; 
	u.run(); 

}