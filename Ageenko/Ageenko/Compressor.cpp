#pragma once
#include "Compressor.h"
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"

int CompressorStation::Maxid = 0;

double CompressorStation::GetPercentWorkingWorkshops() const
{
	return  100.0*(number_workshops - number_inwork) / number_workshops;
}

int CompressorStation::Getid() const
{
	return id;
}

int CompressorStation::GetMaxid()
{
	return Maxid;
}


std::string CompressorStation::GetName() const
{
	return name;
}


int CompressorStation::GetInWork() const
{
	return number_inwork;
}



int CompressorStation::GetWorkshops() const
{
	return number_workshops;
}



double CompressorStation::GetEfficiency() const
{
	return efficiency;
}



void CompressorStation::StopStation()
{
	if (number_inwork > 0) {
		number_inwork--;
	}
	else {
		std::cout << "Chislo rabot cehov = 0" << std::endl;
	}
}

void CompressorStation::RunStation()
{
	if (number_inwork < number_workshops) {
		number_inwork++;
	}
	else {
		std::cout << "Vse  ceha rabotaut" << std::endl;
	}
}

CompressorStation::CompressorStation()
{
	id = Maxid++;
	name = "Unknown";
	number_workshops = 0;
	number_inwork = 0;
	efficiency = 0.0;
}

std::ostream& operator << (std::ostream& out, const CompressorStation& c) {
	if (c.id >= 0) {
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

std::istream& operator >> (std::istream& in, CompressorStation& c) {
	std::cout << "Vvedite name:" << std::endl;
	std::cin.ignore(256, '\n');
	getline(in, c.name, '\n');
	std::cout << "Vvedite chislo  cehov: " << std::endl;
	c.number_workshops = get_value(1, 100);
	std::cout << "Vvedite chislo rabot cehov: " << std::endl;
	c.number_inwork = get_value(0, c.number_workshops);
	std::cout << "Vvedite effect: " << std::endl;
	c.efficiency = get_value(0.0, 100.0);
	return in;
}

std::ofstream & operator<<(std::ofstream & out, const CompressorStation & c)
{
	out << c.name << std::endl << c.number_workshops << std::endl << c.number_inwork << std::endl << c.efficiency << std::endl;
	return out;
}

std::ifstream & operator>>(std::ifstream & in, CompressorStation & c)
{
	in.ignore(256,'\n');
	std::getline(in, c.name);
	 in >> c.number_workshops >> c.number_inwork >> c.efficiency;
	return in;
}
