#pragma once
#include <iostream>
#include <iomanip>
const int W = 5;
class book {
public:
	std::string name;
	std::string ISBN;
	std::string writer;
	std::string house;
	bool available;
	std::string borrower;
	double price;

	void print();
	bool borrow(std::string borrower);
};