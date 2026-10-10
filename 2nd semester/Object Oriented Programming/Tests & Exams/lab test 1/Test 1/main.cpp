#include<iostream>
#include"Repo.h"
#include"DynamicVector.h"
#include"Service.h"
#include"UI.h"
#include"tests.h"
#include"Protein.h"

int main()
{
	testAll();
	Repo r; 
	Service s{ r };
	s.addDefault();
	UI u{ s };
	u.run();
}