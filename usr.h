# pragma once
#include "book.h"
#include <iostream>
#include <map>
#include <vector>
class usr {
public:
	usr(std::string name, std::string _passwd,int lev);
	bool checklogin(std::string s);
	void change_passwd(std::string s);
	bool change_name(std::string s);
	void show_borrow_list();
	usr(usr* u);
private:
	int _lev;
	std::string _name;
	int _passwd;
	std::vector<book>borrow_list;
	int encrypt(std::string s);
};
std::map<std::string,usr>user;
usr FindUsr(std::string name) {
	return user[name];
}
bool AddUsr(std::string name,std::string _passwd,int lev) {
	if (user.find(name) == user.end())return false;
	usr *tmp=new usr(name,_passwd,lev);
	user[name] = *tmp;
	return true;
}
void EraseUsr(std::string name) {
	delete(&user.find(name));
}