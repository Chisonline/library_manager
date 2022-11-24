#include "opt.h"
usr* now_usr=nullptr;
void shutdown() {
	write_database();
	std::cout << "感谢您的使用，再见" << std::endl;
	Sleep(500);
	exit(0);
}
void login() {
	system("cls");
	std::cout << "请输入用户名:" << std::endl;
	std::string usr_name, passwd;
	std::cin >> usr_name;
	if (user.count(usr_name) == 0) {
		std::cout << "无效的用户名！" << std::endl;
		system("pause");
		welcome();
		return;
	}
	now_usr = &user[usr_name];
	std::cout << "请输入密码:" << std::endl;
	passwd = get_pwd();
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
void regist() {
	system("cls");
	std::cout << "请输入用户名:" << std::endl;
	std::string usr_name, pwd1, pwd2;
	std::cin >> usr_name;
	if (user.find(usr_name) != user.end()) {
		std::cout << "用户名已被占用" << std::endl;
		system("pause");
		welcome();
		return;
	}
	std::cout << "请输入密码:" << std::endl;
	pwd1 = get_pwd();
	std::cout << "请重复密码以确认" << std::endl;
	pwd2 = get_pwd();
	if (pwd1 != pwd2) {
		std::cout << "两次密码不一致！" << std::endl;
		system("pause");
		welcome();
		return;
	}
	else {
		AddUsr(usr_name, pwd1, 2);
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
	std::cout << "0.管理员模式" << std::endl;
	std::cout << now_usr->_name << ">";
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
	case 0:
		if (now_usr->get_lev() != 1) {
			std::cout << "您不是本系统的管理员" << std::endl;
			break;
		}
		admin_opt();
	default:
		std::cout << "无效的操作" << std::endl;
	}
}
void Back(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "未找到目标书籍" << std::endl;
		return;
	}
	if (now_usr->find_borrow(ss) == -1) {
		std::cout << "未借阅目标书籍" << std::endl;
		return;
	}
	now_usr->back(ss);
	book* ptr = &books[ss];
	ptr->back();
	std::cout << "归还成功！" << std::endl;
}
void Borrow(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "未找到目标书籍" << std::endl;
		return;
	}
	book* ptr = &books[ss];
	if (ptr->borrow(now_usr->_name)) {
		now_usr->borrow(*ptr);
		std::cout << "借阅成功！" << std::endl;
		return;
	}
	else {
		std::cout << "目标书籍已被借阅" << std::endl;
		return;
	}
}

void op_book() {
	while (true) {
		system("cls");
		std::cout << "请输入操作对应序号" << std::endl;
		std::cout << "1.查询图书" << std::endl;
		std::cout << "2.借阅图书" << std::endl;
		std::cout << "3.归还图书" << std::endl;
		std::cout << "4.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::cin >> opt;
		switch (opt) {
		case 1: {
			std::cout << "您可以输入 题名、ISBN/ISSN、作者、出版社 等任何相关信息：" << std::endl;
			std::string s1;
			std::cin >> s1;
			Search(s1);
			break;
		}
		case 2: {
			std::cout << "请输入要借阅的题名" << std::endl;
			std::string s2;
			std::cin >> s2;
			Borrow(s2);
			break;
		}
		case 3: {
			std::cout << "请输入要归还的题名" << std::endl;
			std::string s3;
			std::cin >> s3;
			Back(s3);
			break;
		}
		case 4: {
			return;
		}
		default: {
			std::cout << "无效的操作！" << std::endl;
			break;
		}
		}
	}
}
void admin_opt() {
	while (true) {
		system("cls");
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.用户管理" << std::endl;
		std::cout << "2.图书管理" << std::endl;
		std::cout << "3.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::cin >> opt;
		switch (opt) {
		case 1:
			admin_usr_opt();
			break;
		case 2:
			admin_book_opt();
			break;
		case 3:
			return;
		default:
			std::cout << "无效的操作！" << std::endl;
			system("pause");
			break;
		}
	}
}
void admin_usr_opt() {
	while (true) {
		system("cls");
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.列举用户列表" << std::endl;
		std::cout << "2.修改用户" << std::endl;
		std::cout << "3.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::cin >> opt;
		switch (opt) {
		case 1:
			PrintUsr();
			break;
		case 2:
			change_usr();
			break;
		case 3:
			return;
		default:
			std::cout << "无效的操作！" << std::endl;
			break;
		}
	}
}
void change_usr() {
	usr* targ = nullptr;
	while (true) {
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.选择用户" << std::endl;
		std::cout << "2.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		bool flag = 0;
		std::string s1;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "请输入目标用户名:" << std::endl;
			std::cin >> s1;
			if (user.find(s1) == user.end()) {
				std::cout << "没有找到该用户" << std::endl;
				break;
			}
			targ = &user[s1];
			break;
		case 2:
			return;
		default:
			std::cout << "无效的操作！" << std::endl;
			break;
		}
		if (flag)break;
	}
	while (true) {
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.重置密码" << std::endl;
		std::cout << "2.更改用户名" << std::endl;
		std::cout << "3.删除用户" << std::endl;
		std::cout << "4.查询该用户借阅列表" << std::endl;
		std::cout << "5.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::string ss;
		std::cin >> opt;
		switch (opt) {
		case 1:
			targ->change_passwd("123456");
			std::cout << targ->_name << " 的密码已经重置为：123456" << std::endl;
			break;
		case 2:
			std::cout << "请输入新用户名" << std::endl;
			std::cin >> ss;
			targ->change_name(ss);
			std::cout << "该用户的用户名已经修改为：" << ss << std::endl;
			break;
		case 3:
			std::cout << "警告！该用户所有信息将被强制删除！" << std::endl;
			std::cout << "该用户所有未归还书籍将被强制重设为已归还！" << std::endl;
			while (true) {
				std::cout << "您确定要继续吗?[y/n]";
				std::cin >> ss;
				if (ss == "y")targ->del();
				else if (ss == "n")break;
			}
			break;
		case 4:
			targ->show_borrow_list();
			break;
		case 5:
			return;
		default:
			std::cout << "无效的操作！" << std::endl;
			break;
		}
	}
}