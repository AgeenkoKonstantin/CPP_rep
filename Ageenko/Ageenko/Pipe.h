#pragma once
#include <string>
#include <iostream>
#include <fstream>



class Pipe
{

	int id;
	double length;
	int diametr;
	bool under_repair;
	std::string name;
	double Weight;
	static int Maxid;

	int start;
	int end;
	bool used;

public:
	

	std::string GetName() const;

	static int GetMaxid();

	int Getid() const;

	double GetWeight() const;

	int GetDiametr() const;


	double GetLength() const;


	bool GetStatus() const;

	void SetStart(int);
	void SetEnd(int);

	int GetStart() const;
	int GetEnd() const;

	void ChangeUsed();

	void change_status();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);

	Pipe(); // стандарт

};

