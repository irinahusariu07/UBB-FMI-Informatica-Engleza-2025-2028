#include<iostream>
#include"DynamicVector.h"
#include"Repository.h"
#include"Service.h"
#include"UI.h"
#include"Weather.h"

int main()
{
	Repository r;
	Service s{ r };
	s.addDefault();
	UI u{ s };
	u.run();
}