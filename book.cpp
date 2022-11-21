#include "book.h"
std::map<std::string, book>books;
book::book(){}
book::book(std::string name, std::string ISBN, std::string writer, std::string house, bool available, std::string borrower, double price,int borrowed_times) {
	this->name = name;
	this->ISBN = ISBN;
	this->writer = writer;
	this->house = house;
	this->available = available;
	this->borrower = borrower;
	this->price = price;
	this->borrowed_times = borrowed_times;
}
void book::print() {
	std::cout << this->name << std::setw(W);
	std::cout << this->ISBN << std::setw(W);
	std::cout << this->writer << std::setw(W);
	std::cout << this->house << std::setw(W);
	std::cout << this->borrowed_times << std::setw(W);
	std::cout << std::endl;
}
void book::save(std::ostream& ss) {
	ss << this->name << '\t';
	ss << this->ISBN << '\t';
	ss << this->writer << '\t';
	ss << this->house << '\t';
	ss << this->available << '\t';
	ss << this->borrower << '\t';
	ss << this->price << '\t';
	ss << this->borrowed_times << '\t';
}
bool book::borrow(std::string borrower) {
	if (!this->available)return false;
	this->available = false;
	this->borrower = borrower;
	return true;
}