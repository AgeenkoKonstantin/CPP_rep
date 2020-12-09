#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "utils.h"


class Pipe
{

	int id;
	double length;
	int diametr;
	bool under_repair;
	std::string name;

public:
	static int Maxid;

	std::string GetName() const;


	int Getid() const;


	int GetDiametr() const;


	double GetLength() const;


	bool GetStatus() const;


	void change_status();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);

	Pipe(); // стандарт

};

