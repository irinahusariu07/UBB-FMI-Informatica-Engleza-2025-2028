#include<iostream>
#include<string>
#include"Car.h"
#include"DynamicVector.h"
#include"Repo.h"
#include"Service.h"
#include"UI.h"
#include"tests.h"

int main()
{
	{
		testAll();
		Repo r; 
		Service s( r );
		s.addDefault();
		UI u( s );
		u.run();
	}
}