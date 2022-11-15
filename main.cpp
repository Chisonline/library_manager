#include "usr.h"
#include "admin.h"
#include "book.h"
#include <cstdlib>
#include <conio.h>
#include "db.h"
usr *now_usr;
void shutdown() {
	std::cout << "感谢您的使用，再见" << std::endl;
	exit(0);
}
void login() {
	system("cls");
	std::cout << "请输入用户名:" << std::endl;
	std::string usr_name,passwd;
	std::cin >> usr_name;
	if (user.find(usr_name) == user.end()) {
		std::cout << "无效的用户名！" << std::endl;
		system("pause");
		welcome();
		return;
	}
	now_usr = &user[usr_name];
	std::cout << "请输入密码:" << std::endl;
	while (true) {
		char ch = getch();
		if (ch == 'r') {
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
		welcome();
		return;
	}
	std::cout << "请输入密码:" << std::endl;
	while (true) {
		char ch = getch();
		if (ch == 'r') {
			putchar('\r');
			break;
		}
		passwd1 += ch;
		putchar('*');
	}
	std::cout << "请再次输入密码以确认" << std::endl;
	while (true) {
		char ch = getch();
		if (ch == 'r') {
			putchar('\r');
			break;
		}
		passwd2 += ch;
		putchar('*');
	}
	if (passwd1 != passwd2) {
		std::cout << "两次密码不一致！" << std::endl;
		welcome();
		return;
	}
	else {
		AddUsr(usr_name, passwd1,2);
		now_usr = &user[usr_name];
		std::cout << "登录成功！" << std::endl;
		std::cout << "欢迎 " << usr_name << std::endl;
		return;
	}
}
void welcome() {
	system("cls");
	std::cout << "欢迎来到H大学图书馆信息管理系统" << std::endl;
	std::cout << "请输入操作对应序号" << std::endl;
	std::cout << "1.登录" << std::endl;
	std::cout << "2.注册" << std::endl;
	std::cout << "3.作为访客进入" << std::endl;
	std::cout << "4.退出" << std::endl;
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
int main() {
	load_database();
	welcome();


}