#include "admin.h"
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "db.h"
static usr* now_usr;
void welcome();
void shutdown() {
	write_database();
	std::cout << "感谢您的使用，再见" << std::endl;
	Sleep(500);
	exit(0);
}
void login() {
	system("cls");
	std::cout << "请输入用户名:" << std::endl;
	std::string usr_name,passwd;
	std::cin >> usr_name;
	if (user.count(usr_name) == 0) {
		std::cout << "无效的用户名！" << std::endl;
		system("pause");
		welcome();
		return;
	}
	now_usr = &user[usr_name];
	std::cout << "请输入密码:" << std::endl;
	while (true) {
		char ch = _getch();
		if (ch == '\r') {
			putchar('\r');
			break;
		}
		passwd += ch;
		putchar('*');
	}
	if (now_usr->checklogin(passwd)) {
		std::cout << "登录成功！" << std::endl;
		std::cout << "欢迎 " << usr_name << std::endl;
		return;
	}
	else {
		std::cout << "密码错误" << std::endl;
		now_usr = nullptr;
		welcome();
		return;
	}
}
void regist() {
	system("cls");
	std::cout << "请输入用户名:" << std::endl;
	std::string usr_name, passwd1,passwd2;
	std::cin >> usr_name;
	if (user.find(usr_name) != user.end()) {
		std::cout << "用户名已被占用" << std::endl;
		system("pause");
		welcome();
		return;
	}
	std::cout << "请输入密码:" << std::endl;
	while (true) {
		char ch = _getch();
		if (ch == '\r') {
			putchar('\r');
			break;
		}
		passwd1 += ch;
		putchar('*');
	}
	std::cout << "请再次输入密码以确认" << std::endl;
	while (true) {
		char ch = _getch();
		if (ch == '\r') {
			putchar('\r');
			break;
		}
		passwd2 += ch;
		putchar('*');
	}
	if (passwd1 != passwd2) {
		std::cout << "两次密码不一致！" << std::endl;
		system("pause");
		welcome();
		return;
	}
	else {
		AddUsr(usr_name, passwd1,2);
		now_usr = &user[usr_name];
		std::cout << "登录成功！" << std::endl;
		std::cout << "欢迎 " << now_usr->_name << std::endl;
		Sleep(500);
		return;
	}
}

void operat() {
	//Sleep(500);
	system("cls");
	std::cout << "请输入操作对应序号" << std::endl;
	std::cout << "1.图书操作" << std::endl;
	std::cout << "2.用户操作" << std::endl;
	std::cout << "3.退出登录" << std::endl;
	std::cout << "4.关闭系统" << std::endl;
	std::cout << now_usr->_name << ">" ;
	int op;
	std::cin >> op;
	switch (op) {
	case 1:
		op_book();
		break;
	case 2:
		if (now_usr->_name == "visitor") {
			std::cout << "访客不具有该权限" << std::endl;
			break;
		}
		now_usr->op();
		break;
	case 3:
		now_usr = nullptr;
		welcome();
		break;
	case 4:
		shutdown();
	default:
		std::cout << "无效的操作" << std::endl;
	}
}
int main() {
	load_database();
	welcome();
	while(true)
		operat();
	return 0;
}
void welcome() {
	system("cls");
	std::cout << "欢迎来到H大学图书馆信息管理系统" << std::endl;
	std::cout << "请输入操作对应序号" << std::endl;
	std::cout << "1.登录" << std::endl;
	std::cout << "2.注册" << std::endl;
	std::cout << "3.作为访客进入" << std::endl;
	std::cout << "4.关闭系统" << std::endl;
	std::cout << ">";
	int op;
	std::cin >> op;
	if (op < 1 || op>4) {
		std::cout << "无效的操作" << std::endl;
		system("pause");
		welcome();
	}
	else {
		switch (op) {
		case 1:
			login();
			break;
		case 2:
			regist();
			break;
		case 3:
			now_usr = &user["visitor"];
			break;
		case 4:
			shutdown();
		}
	}
}