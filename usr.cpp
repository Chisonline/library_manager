#include "usr.h"
typedef long long ll;
const int mod = 1e9 + 7,B=255;
usr::usr(std::string name, std::string _passwd,int lev) {
	this->_name = name;
	this->_passwd = encrypt(_passwd);
	this->_lev = lev;
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
		res = (ll)(res * B + s[i]) % mod;
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
}
void usr::show_borrow_list() {
	if (this->borrow_list.empty()) {
		std::cout << "没有借阅记录" << std::endl;
		return;
	}
	system("cls");
	std::cout << "题名" << std::setw(W);
	std::cout << "ISBN" << std::setw(W);
	std::cout << "作者" << std::setw(W);
	std::cout << "出版社" << std::setw(W);
	std::cout << std::endl;
	for (int i = 0; i < this->borrow_list.size(); i++)
		this->borrow_list[i].print();
	system("pause");
	return;
}