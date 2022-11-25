#pragma once
#include "book.h"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <conio.h>
class usr {
public:
	usr(std::string name, std::string _passwd,int lev);
	usr(std::string name, int _passwd, int lev,std::vector<std::string> borrow_list);
	bool checklogin(std::string s);
	void change_passwd(std::string s);
	bool change_name(std::string s);
	void show_borrow_list();
	void save(std::ostream& ss);
	void borrow(book targ);
	void op();
	int get_lev() { return this->_lev; }
	int find_borrow(std::string);
	void back(std::string);
	void del();
	usr(usr* u);
	usr();
	std::string _name;
private:
	int _lev;
	int _passwd;
	std::vector<std::string>borrow_list;
	int encrypt(std::string s);
};
extern std::map<std::string, usr>user;
usr FindUsr(std::string name);
bool AddUsr(std::string name, std::string _passwd, int lev);
void PrintUsr();
void del_usr(usr* ptr);