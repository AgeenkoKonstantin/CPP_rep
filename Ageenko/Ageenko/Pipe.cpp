#include "Pipe.h"
#include <iostream>
#include "utils.h"

int Pipe::Maxid = 0;

std::string Pipe::GetName() const
{
	return name;
}

void Pipe::SetName(std::string new_name)
{
	name = new_name;
}

int Pipe::Getid() const
{
	return id;
}

void Pipe::Setid(int new_id)
{
	id = new_id;
}

int Pipe::GetDiametr() const
{
	return diametr;
}

void Pipe::SetDiametr(int new_diametr)
{
	diametr = new_diametr;
}

double Pipe::GetLength() const
{
	return length;
}

void Pipe::SetLength(double new_length)
{
	length = new_length;
}

bool Pipe::GetStatus() const
{
	return under_repair;
}

void Pipe::SetStatus(bool Status)
{
	under_repair = Status;
}

void Pipe::change_status()
{
	under_repair = !under_repair;
}

std::ostream& operator << (std::ostream& out, const Pipe& p) {
	if (p.id == -1) {
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
	p.id = -1;
	return in;
}

Pipe::Pipe() //конструктор по умолчанию
{
	id = Maxid++; //сделать через статическую переменную
	length = 0;
	diametr = 0;
	under_repair = false;
	name = "Unknown";
}

//Pipe::Pipe(std::string name)
//{
//	this->name = name;
//}
//
//Pipe::Pipe(const Pipe & p)
//{
//
//}
//
//Pipe::Pipe(Pipe && p)
//{
//
//}
//
//Pipe::~Pipe()
//{
//}
