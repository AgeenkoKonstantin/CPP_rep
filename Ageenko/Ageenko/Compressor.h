#pragma once
#include <string>
#include <iostream>
#include <fstream>


class CompressorStation
{
	int id;
	std::string name;
	int number_workshops;
	int number_inwork;
	double efficiency;
	static int Maxid;

public:
	
	double GetPercentWorkingWorkshops() const;

	int Getid() const;

	static int GetMaxid();

	std::string GetName() const;


	int GetInWork() const;


	int GetWorkshops() const;


	double GetEfficiency() const;


	friend std::ostream& operator << (std::ostream& out, const CompressorStation& c);
	friend std::istream& operator >> (std::istream& in, CompressorStation& c);
	friend std::ofstream& operator << (std::ofstream& out, const CompressorStation& c);
	friend std::ifstream& operator >> (std::ifstream& in, CompressorStation& c);

	void StopStation();
	void RunStation();

	CompressorStation();
};


