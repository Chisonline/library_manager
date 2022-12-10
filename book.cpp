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
book::book(book* ptr) {
	this->name = ptr->name;
	this->ISBN = ptr->ISBN;
	this->writer = ptr->writer;
	this->house = ptr->house;
	this->available = ptr->available;
	this->borrower = ptr->borrower;
	this->price = ptr->price;
	this->borrowed_times = ptr->borrowed_times;
}
void book::print(int maxW) {
	std::cout << std::setw(maxW+5) << std::left << this->name;
	std::cout << std::setw(15) << std::left << this->ISBN;
	std::cout << std::setw(W) << std::left << this->writer;
	std::cout << std::setw(15) << std::left << this->house;
	std::cout << this->borrowed_times;
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
	this->borrowed_times++;
	return true;
}
bool book::founded(std::string ss) {
	if (ISBN == ss)return true;
	if (writer == ss)return true;
	if (house == ss)return true;
	return false;
}
std::string book::show_name() {
	return this->name;
}
void book::back() {
	this->available = 1;
	this->borrower = "NULL";
}
std::string book::WhoBorrow() {
	return this->borrower;
}
bool book::change_name(std::string ss) {
	if (books.find(ss) == books.end())return false;
	book* tmp = new book(this);
	tmp->name = ss;
	books[ss] = *tmp;
	books.erase(this->name);
	delete(this);
	return true;
}
void book::change_ISBN(std::string ss) {
	this->ISBN = ss;
}
void book::change_writer(std::string ss) {
	this->writer = ss;
}
void book::change_price(double num) {
	this->price = num;
}
void book::change_house(std::string ss) {
	this->house = ss;
}
void book::del() {
	books.erase(this->show_name());
	//delete(this);
}
bool cmp_book(book x, book y) {
	return x.show_name() < y.show_name();
}
void Search(std::string ss) {
	system("cls");
	std::vector<book> li;
	int maxW = 0;
	if (books.find(ss) != books.end()) {
		li.push_back(books[ss]);
		maxW = max(ss.length(), maxW);
	}
	for (std::map<std::string, book>::iterator i = books.begin(); i != books.end(); i++)
		if (i->second.founded(ss)) {
			li.push_back(i->second);
			maxW = max(i->second.show_name().length(), maxW);
		}
	if (li.empty()) {
		std::cout << "没有找到相关书籍" << std::endl;
		system("pause");
		return;
	}
	std::sort(li.begin(),li.end(),cmp_book);
	std::cout << std::setw(maxW+5) << std::left << "题名";
	std::cout << std::setw(15) << std::left << "ISBN";
	std::cout << std::setw(W) << std::left << "作者";
	std::cout << std::setw(15) << std::left << "出版社";
	std::cout<< "借阅次数";
	std::cout << std::endl;
	for (int i = 0; i < li.size(); i++)
		li[i].print(maxW);
	system("pause");

}
