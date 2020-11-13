#pragma once
#include <iostream>
#include <string>
#include "utils.h"


class Pipe
{
	static int Maxid;
	int id;
	double length;
	int diametr;
	bool under_repair;
	std::string name;

public:
	std::string GetName() const;
	void SetName(std::string);

	int Getid() const;
	void Setid(int);

	int GetDiametr() const;
	void SetDiametr(int);

	double GetLength() const;
	void SetLength(double);

	bool GetStatus() const;
	void SetStatus(bool);

	void change_status();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);


	Pipe(); // стандарт

};

