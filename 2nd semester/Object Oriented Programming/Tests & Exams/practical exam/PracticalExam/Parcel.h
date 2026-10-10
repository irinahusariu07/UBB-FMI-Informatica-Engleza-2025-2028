#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

class Parcel
{
	std::string recipient; 
	std::string street; 
	int number; 
	int locx, locy; 
	bool delivered; 

public:
	Parcel(const std::string& rec, const std::string& str, int number, int locx, int locy, bool del) :
		recipient{ rec }, street{ str }, number{ number }, locx{ locx }, locy{ locy }, delivered{ del } {
	}
	std::string getRecipient() const { return recipient; }
	std::string getStreet() const { return street; }
	int getNumber() const { return number; }
	int getLocX() const { return locx; }
	int getLocY() const { return locy; }
	bool getStatus() const { return delivered; }
	void setStatus(bool stat) { delivered = stat; }
};