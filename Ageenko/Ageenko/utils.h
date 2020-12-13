#pragma once
#include <iostream>


template <typename T>
T get_value(T left_border, T right_border) {
	T i;
	while ((std::cin >> i).fail() || i > right_border || i < left_border) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Vvedite udovl znachenie " << "(" << left_border << " - " << right_border << ")" << std::endl;
	}
	return i;
}
