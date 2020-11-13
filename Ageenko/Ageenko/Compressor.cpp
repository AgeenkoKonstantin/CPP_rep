#include "Compressor.h"
#include <iostream>
#include "utils.h"

int Compressor::Maxid = 0;

int Compressor::Getid() const
{
	return id;
}

void Compressor::Setid(int new_id)
{
	id = new_id;
}

std::string Compressor::GetName() const
{
	return name;
}

void Compressor::SetName(std::string new_name)
{
	name = new_name;
}

int Compressor::GetInWork() const
{
	return number_inwork;
}

void Compressor::SetInWork(int number)
{
	number_inwork = number;
}

int Compressor::GetWorkshops() const
{
	return number_workshops;
}

void Compressor::SetWorkshops(int number)
{
	number_workshops = number;
}

double Compressor::GetEfficiency() const
{
	return efficiency;
}

void Compressor::SetEfficiency(double new_efficienty)
{
	efficiency = new_efficienty;
}

void Compressor::stop_work()
{
	if (number_inwork > 0) {
		number_inwork--;
	}
	else {
		std::cout << "Chislo rabot cehov = 0" << std::endl;
	}
}

void Compressor::continue_work()
{
	if (number_inwork < number_workshops) {
		number_inwork++;
	}
	else {
		std::cout << "Vse  ceha rabotaut" << std::endl;
	}
}

Compressor::Compressor()
{
	id = Maxid++;
	name = "Unknown";
	number_workshops = 0;
	number_inwork = 0;
	efficiency = 0.0;
}

std::ostream& operator << (std::ostream& out, const Compressor& c) {
	if (c.id == -1) {
		out << "\t COMPRESSOR info: " << std::endl;
		out << "Name: " << c.name << std::endl;
		out << "id: " << c.id << std::endl;
		out << "Number of workshops: " << c.number_workshops << std::endl;
		out << "Number of working workshops: " << c.number_inwork << std::endl;
		out << "Efficienty: " << c.efficiency << std::endl;
	}
	else {
		out << "Compressor doesnt exist" << std::endl;
	}
	return out;
}

std::istream& operator >> (std::istream& in, Compressor& c) {
	std::cout << "Vvedite name:" << std::endl;
	std::cin.ignore(256, '\n');
	getline(in, c.name, '\n');
	std::cout << "Vvedite chislo  cehov: " << std::endl;
	c.number_workshops = get_value(1, 100);
	std::cout << "Vvedite chislo rabot cehov: " << std::endl;
	c.number_inwork = get_value(0, c.number_workshops);
	std::cout << "Vvedite effect: " << std::endl;
	c.efficiency = get_value(0.0, 100.0);
	c.id = -1;
	return in;
}
