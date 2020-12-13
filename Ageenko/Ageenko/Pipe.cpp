#pragma once
#include "Pipe.h"
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"



int Pipe::Maxid = 0;

std::string Pipe::GetName() const
{
	return name;
}

int Pipe::GetMaxid()
{
	return Maxid;
}

int Pipe::Getid() const
{
	return id;
}

double Pipe::GetWeight() const
{
	return length;
}

int Pipe::GetDiametr() const
{
	return diametr;
}

double Pipe::GetLength() const
{
	return length;
}

bool Pipe::GetStatus() const
{
	return under_repair;
}

void Pipe::SetStart(int new_start)
{
	start = new_start;
}

void Pipe::SetEnd(int new_end)
{
	end = new_end;
}

int Pipe::GetStart() const
{
	return start;
}

int Pipe::GetEnd() const
{
	return end;
}

void Pipe::ChangeUsed()
{
	used = !used;
}

void Pipe::change_status()
{
	under_repair = !under_repair;
}

std::ostream& operator << (std::ostream& out, const Pipe& p) {
	if (p.id >= 0) {
		out << "\t PIPE info: " << std::endl;
		out << "Name: " << p.name << std::endl;
		out << "Diameter: " << p.diametr << std::endl;
		out << "Length: " << p.length << std::endl;
		out << "id: " << p.id << std::endl;
		out << (p.under_repair ? "V remonte" : "Ne v remonte") << std::endl;
	}
	else {
		std::cout << "Pipe doesnt exist" << std::endl;
	}
	return out;
}

std::istream& operator >> (std::istream& in, Pipe& p) {
	std::cout << "Vvedite name:" << std::endl;
	std::cin.ignore(256, '\n');
	getline(in, p.name, '\n');
	std::cout << "Vvedite diametr: " << std::endl;
	p.diametr = get_value(1, 3000);
	std::cout << "Vvedite dlinny: " << std::endl;
	p.length = get_value(1.0, 10000.0);
	p.under_repair = false;
	return in;
}

std::ofstream & operator << (std::ofstream& out, const Pipe & p)
{
	out <<  p.name << std::endl << p.diametr << std::endl << p.length << std::endl << p.under_repair << std::endl;
	return out;
}


std::ifstream & operator >> (std::ifstream& in, Pipe & p)
{
		in.ignore(256, '\n');
		std::getline(in, p.name);
		in >> p.diametr >> p.length >> p.under_repair;
		return in;
}

Pipe::Pipe() 
{
	id = Maxid++; 
	length = 0.0;
	diametr = 0;
	under_repair = false;
	name = "Unknown";
	used = false;
	start = -1;
	end = -1;
}

