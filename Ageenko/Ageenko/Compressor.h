#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"

class Compressor
{
	
	int id;
	std::string name;
	int number_workshops;
	int number_inwork;
	double efficiency;

public:
	static int Maxid;
	int Getid() const;


	std::string GetName() const;


	int GetInWork() const;


	int GetWorkshops() const;


	double GetEfficiency() const;


	friend std::ostream& operator << (std::ostream& out, const Compressor& c);
	friend std::istream& operator >> (std::istream& in, Compressor& c);
	friend std::ofstream& operator << (std::ofstream& out, const Compressor& c);
	friend std::ifstream& operator >> (std::ifstream& in, Compressor& c);

	void stop_work();
	void continue_work();

	Compressor();
};


