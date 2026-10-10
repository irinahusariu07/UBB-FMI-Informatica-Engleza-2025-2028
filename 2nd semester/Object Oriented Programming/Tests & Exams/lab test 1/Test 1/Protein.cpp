#include "Protein.h"

Protein::Protein(const std::string& organism, const std::string& name, const std::string& sequence)
{
	this->organism = organism;
	this->name = name; 
	this->sequence = sequence; 
}
