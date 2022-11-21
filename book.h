#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#define W 5
class book {
public:
	book(std::string name, std::string ISBN, std::string writer, std::string house, bool available, std::string borrower, double price,int borrowed_times);
	void print();
	void save(std::ostream &ss);
	bool borrow(std::string borrower);
	book();
private:
	int borrowed_times;
	std::string name;
	std::string ISBN;
	std::string writer;
	std::string house;
	bool available;
	std::string borrower;
	double price;
};
extern std::map<std::string, book>books;
void op_book();
