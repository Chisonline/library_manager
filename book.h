#pragma once
#include "tools.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#define max(a,b) (a>b?a:b)
constexpr int W = 45;
class book {
public:
	book(std::string name, std::string ISBN, std::string writer, std::string house, bool available, std::string borrower, double price,int borrowed_times);
	void print(int);
	void save(std::ostream &ss);
	bool borrow(std::string borrower);
	bool founded(std::string ss);
	bool change_name(std::string ss);
	std::string show_name();
	void back();
	std::string WhoBorrow();
	book();
	book(book* ptr);
	void change_ISBN(std::string ss);
	void change_writer(std::string ss);
	void change_price(double num);
	void change_house(std::string ss);
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
void Search(std::string ss);
bool cmp_book(book x, book y);
void del_book(book* ptr);