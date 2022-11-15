#include "book.h"
void book::print() {
	std::cout << this->name << std::setw(W);
	std::cout << this->ISBN << std::setw(W);
	std::cout << this->writer << std::setw(W);
	std::cout << this->house << std::setw(W);
	std::cout << std::endl;
}
bool book::borrow(std::string borrower) {
	if (!this->available)return false;
	this->available = false;
	this->borrower = borrower;
}