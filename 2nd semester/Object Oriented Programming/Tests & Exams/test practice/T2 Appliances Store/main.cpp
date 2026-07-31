#include"Appliance.h"
#include"Service.h"
#include"UI.h"
#include<iostream>

int main()
{
	Service s; 
	Appliance* a = new Refrigerator("abc", "a++", false); 
	Appliance* b = new DishWasher("a2", 20);
	Appliance* c = new Refrigerator("mc", "a", true);
	s.addAppliance(a);
	s.addAppliance(b);
	s.addAppliance(c);
	UI ui{ s };
	ui.run();

}