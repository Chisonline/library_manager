#include "db.h"
void load_database() {
	inFile.open("book.libdb");
	if (!inFile.is_open()) {
		std::cout << "图书数据导入失败!" << std::endl;
		system("pause");
		exit(-1);
	}
	std::string book_name, book_ISBN, book_writer, book_house, book_borrower;
	bool book_available;
	double book_price;
	while (1) {
		inFile >> book_name;
		if (inFile.eof())break;
		inFile >> book_ISBN >> book_writer >> book_house >> book_available >> book_borrower >> book_price;
		book* tmp = new book(book_name, book_ISBN, book_writer, book_house, book_available, book_borrower, book_price);
		books[book_name] = *tmp;
		std::cout << "成功导入 \"" << book_name <<"\"" <<std::endl;
	}
	inFile.close();
	std::cout << "图书数据导入成功!" << std::endl;
	inFile.open("usr.libdb");
	if (!inFile.is_open()) {
		std::cout << "用户数据导入失败!" << std::endl;
		system("pause");
		exit(-1);
	}
	std::string usr_name;
	int usr_lev, usr_passwd;
	while (1) {
		std::vector<std::string>borrow_list;
		inFile >> usr_name;
		if (inFile.eof())break;
		inFile >> usr_passwd >> usr_lev;
		int len;
		inFile >> len;
		for (int i = 0; i < len; i++) {
			std::string stmp;
			inFile >> stmp;
			borrow_list.push_back(stmp);
		}
		usr* tmp = new usr(usr_name, usr_passwd, usr_lev,borrow_list);
		user[usr_name] = *tmp;
		std::cout << "成功导入 \"" << usr_name <<"\""<< std::endl;
	}
	inFile.close();
	std::cout << "用户数据导入成功!" << std::endl;
}
void write_database() {
	outFile.open("book.libdb");
	for (std::map<std::string, book>::iterator i = books.begin(); i != books.end(); i++) {
		book *tmp = &i->second;
		tmp->save(outFile);
	}
	outFile.close();
	outFile.open("usr.libdb");
	for (std::map<std::string, usr>::iterator i = user.begin(); i != user.end(); i++) {
		usr *tmp = &i->second;
		tmp->save(outFile);
	}
	outFile.close();
}