#pragma once
#include <string>
#include <iostream>
#include "utils.h"

class Compressor
{
	static int Maxid;
	int id;
	std::string name;
	int number_workshops;
	int number_inwork;
	double efficiency;

public:
	int Getid() const;
	void Setid(int);

	std::string GetName() const;
	void SetName(std::string);

	int GetInWork() const;
	void SetInWork(int);

	int GetWorkshops() const;
	void SetWorkshops(int);

	double GetEfficiency() const;
	void SetEfficiency(double);

	friend std::ostream& operator << (std::ostream& out, const Compressor& c);
	friend std::istream& operator >> (std::istream& in, Compressor& c);

	void stop_work();
	void continue_work();

	Compressor();
};


