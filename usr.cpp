#pragma once
#include "usr.h"
typedef long long ll;
const int mod = 1e9 + 7,B=255;
std::map<std::string, usr>user;
usr::usr(){}
usr::usr(std::string name, std::string _passwd,int lev) {
	this->_name = name;
	this->_passwd = encrypt(_passwd);
	this->_lev = lev;
}
usr::usr(std::string name, int _passwd, int lev, std::vector<std::string>borrow_list) {
	this->_name = name;
	this->_passwd = _passwd;
	this->_lev = lev;
	this->borrow_list = borrow_list;
}
usr::usr(usr* u) {
	this->_name = u->_name;
	this->_passwd = u->_passwd;
	this->_lev = u->_lev;
}
//Hash
int usr::encrypt(std::string s) {
	int res = 0;
	for (int i = 0; i < s.length(); i++){
		res = (1ll*res * B + s[i]) % mod;
	}
	return res;
}
bool usr::checklogin(std::string s) {
	return _passwd == encrypt(s);
}
void usr::change_passwd(std::string s) {
	this->_passwd = encrypt(s);
}
bool usr::change_name(std::string s) {
	if (user.find(s) == user.end())return false;
	usr* tmp = new usr(this);
	tmp->_name = s;
	user[s] = *tmp;
	user.erase(this->_name);
	delete(this);
	return true;
}
void usr::show_borrow_list() {
	if (this->borrow_list.empty()) {
		std::cout << "û�н��ļ�¼" << std::endl;
		return;
	}
	system("cls");
	std::cout << "����" << std::setw(W);
	std::cout << "ISBN" << std::setw(W);
	std::cout << "����" << std::setw(W);
	std::cout << "������" << std::setw(W);
	std::cout << std::endl;
	for (int i = 0; i < this->borrow_list.size(); i++)
		books[this->borrow_list[i]].print();
	system("pause");
	return;
}
void usr::save(std::ostream& ss) {
	ss << this->_name << '\t';
	ss << this->_passwd << '\t';
	ss << this->_lev<<'\t';
	ss << this->borrow_list.size()<<'\t';
	for (int i = 0; i < borrow_list.size(); i++) {
		ss << borrow_list[i] << '\t';
	}
	//std::cout << "�ɹ�д��" << this->_name << std::endl;
}
usr FindUsr(std::string name) {
	return user[name];
}
bool AddUsr(std::string name, std::string _passwd, int lev) {
	if (user.find(name) != user.end())return false;
	usr* tmp = new usr(name, _passwd, lev);
	user[name] = *tmp;
	return true;
}
void EraseUsr(std::string name) {
	delete(&user[name]);
}
void usr::op() {
	std::cout << "�����������Ӧ���" << std::endl;
	std::cout << "1.�ҵĽ����б�" << std::endl;
	std::cout << "2.�޸�����" << std::endl;
	//std::cout << "" << std::endl;
	std::cout << this->_lev << ">";
	int opt;
	std::cin >> opt;
	switch (opt) {
	case 1:
		show_borrow_list();
		break;
	case 2:
		std::string pwd1, pwd2;
		std::cout << "������������" << std::endl;
		pwd1 = get_pwd();
		std::cout << "���ظ�������ȷ��" << std::endl;
		pwd2 = get_pwd();
		if (pwd1 != pwd2) {
			std::cout << "�������벻һ�£�" << std::endl;
			system("pause");
			break;
		}
		else {
			this->change_passwd(pwd1);
			std::cout << "�޸ĳɹ���" << std::endl;
			system("pause");
			break;
		}
	}
}