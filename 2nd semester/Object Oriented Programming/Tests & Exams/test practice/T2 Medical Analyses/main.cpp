#include <iostream>
#include "UI.h"

int main()
{
	std::string patient; 
	std::cout << "\n Patient name: ";
	std::getline(std::cin, patient); 
	std::cout << "\n\n"; 
	Person p{ patient };
	MedicalAnalysis* a = new BP("2025.03.31", 12, 6);
	MedicalAnalysis* b = new BMI("2025.03.21", 20.56); 
	p.addAnalysis(a); 
	p.addAnalysis(b); 
	UI ui{ p }; 
	ui.run(); 

}