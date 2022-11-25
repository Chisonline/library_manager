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
		system("pause");
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
	std::cout << "3.排行榜" << std::endl;
	std::cout << "4.退出登录" << std::endl;
	std::cout << "5.关闭系统" << std::endl;
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
			system("pause");
			break;
		}
		now_usr->op();
		break;
	case 3:
		ranking();
		break;
	case 4:
		now_usr = nullptr;
		welcome();
		break;
	case 5:
		shutdown();
	case 0:
		if (now_usr->get_lev() != 1) {
			std::cout << "您不是本系统的管理员" << std::endl;
			system("pause");
			break;
		}
		admin_opt();
		break;
	default:
		std::cout << "无效的操作" << std::endl;
		system("pause");
	}
}
void Back(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "未找到目标书籍" << std::endl;
		system("pause");
		return;
	}
	if (now_usr->find_borrow(ss) == -1) {
		std::cout << "未借阅目标书籍" << std::endl;
		system("pause");
		return;
	}
	now_usr->back(ss);
	book* ptr = &books[ss];
	ptr->back();
	std::cout << "归还成功！" << std::endl;
	system("pause");
}
void Borrow(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "未找到目标书籍" << std::endl;
		system("pause");
		return;
	}
	book* ptr = &books[ss];
	if (ptr->borrow(now_usr->_name)) {
		now_usr->borrow(*ptr);
		std::cout << "借阅成功！" << std::endl;
		system("pause");
		return;
	}
	else {
		std::cout << "目标书籍已被借阅" << std::endl;
		system("pause");
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
			system("pause");
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
			system("pause");
			break;
		case 2:
			change_usr();
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
void change_usr() {
	usr* targ = nullptr;
	while (true) {
		system("cls");
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.选择用户" << std::endl;
		std::cout << "2.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		bool flag = false;
		std::string s1;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "请输入目标用户名:" << std::endl;
			std::cin >> s1;
			if (user.find(s1) == user.end()) {
				std::cout << "没有找到该用户" << std::endl;
				system("pause");
				break;
			}
			targ = &user[s1];
			flag = true;
			break;
		case 2:
			return;
		default:
			std::cout << "无效的操作！" << std::endl;
			system("pause");
			return;
		}
		if (flag)break;
	}
	while (true) {
		system("cls");
		std::cout << "目前正在修改的用户：" << targ->_name << std::endl;
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
			system("pause");
			break;
		case 2:
			std::cout << "请输入新用户名" << std::endl;
			std::cin >> ss;
			targ->change_name(ss);
			std::cout << "该用户的用户名已经修改为：" << ss << std::endl;
			system("pause");
			break;
		case 3:
			std::cout << "警告！该用户所有信息将被强制删除！" << std::endl;
			std::cout << "该用户所有未归还书籍将被强制重设为已归还！" << std::endl;
			while (true) {
				std::cout << "您确定要继续吗?[y/n]";
				std::cin >> ss;
				if (ss == "y") { 
					del_usr(targ);
					targ = nullptr;
					std::cout << "删除成功" << std::endl;
					return;
				}
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
			system("pause");
			break;
		}
	}
}
void admin_book_opt() {
	book* targ = nullptr;
	while (true) {
		system("cls");
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.查询书籍借阅信息" << std::endl;
		std::cout << "2.修改书籍" << std::endl;
		std::cout << "3.新增书籍" << std::endl;
		std::cout << "4.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::string ss,s1;
		book* tmp;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "请输入目标书籍名称" << std::endl;
			std::cin >> ss;
			if (books.find(ss) == books.end()) {
				std::cout << "未找到目标书籍！" << std::endl;
				system("pause");
				break;
			}
			targ = &books[ss];
			std::cout << "借阅者： " << targ->WhoBorrow() << std::endl;
			targ = nullptr;
			system("pause");
			break;
		case 2:
			change_book(nullptr);
			break;
		case 3:
			std::cout << "请输入新增书籍名称" << std::endl;
			std::cin >> ss;
			tmp = new book(ss, "NULL", "NULL", "NULL", 1, "NULL", 0.00, 0);
			books[ss] = *tmp;
			while (true) {
				std::cout << "是否立即编辑该图书其他信息？[y/n]";
				std::cin >> s1;
				if (s1 == "y") {
					change_book(tmp);
					break;
				}
				else if (s1 == "n")break;
			}
		case 4:
			return;
		default:
			std::cout << "无效的操作！" << std::endl;
			system("pause");
			break;
		}
	}
}
void change_book(book* targ) {
	std::string ss;
	while (targ == nullptr) {
		system("cls");
		std::cout << "请输入目标书籍名称" << std::endl;
		std::cin >> ss;
		if (books.find(ss) == books.end()) {
			std::cout << "未找到该书籍！" << std::endl;
			system("pause");
			continue;
		}
		targ = &books[ss];
	}
	while (true) {
		system("cls");
		std::cout << "目前正在修改的书籍：" <<targ->show_name() << std::endl;
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.修改书籍名称" << std::endl;
		std::cout << "2.修改书籍ISBN" << std::endl;
		std::cout << "3.修改书籍作者" << std::endl;
		std::cout << "4.修改书籍出版社" << std::endl;
		std::cout << "5.修改书籍价格" << std::endl;
		std::cout << "6.删除书籍" << std::endl;
		std::cout << "7.返回上一级" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		double num;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "请输入新的名称" << std::endl;
			std::cin >> ss;
			if (targ->change_name(ss)) {
				std::cout << "名称已经修改为" << targ->show_name() << std::endl;
				system("pause");
			}
			else {
				std::cout << "暂不支持书籍同名" << std::endl;
				system("pause");
				break;
			}
			break;
		case 2:
			std::cout << "请输入新的ISBN" << std::endl;
			std::cin >> ss;
			targ->change_ISBN(ss);
			std::cout << "ISBN已经修改为：" << ss << std::endl;
			system("pause");
			break;
		case 3:
			std::cout << "请输入新的作者" << std::endl;
			std::cin >> ss;
			targ->change_writer(ss);
			std::cout << "作者已经修改为：" << ss << std::endl;
			system("pause");
			break;
		case 4:
			std::cout << "请输入新的出版社" << std::endl;
			std::cin >> ss;
			targ->change_house(ss);
			std::cout << "出版社已经修改为：" << ss << std::endl;
			system("pause");
			break;
		case 5:
			std::cout << "请输入新的价格：" << std::endl;
			std::cin >> num;
			targ->change_price(num);
			std::cout << "价格已经修改为：" << num << std::endl;
			system("pause");
			break;
		case 6:
			std::cout << "警告！本书籍所有信息将被删除！" << std::endl;
			std::cout << "该操作不可撤回！" << std::endl;
			while (true) {
				std::cout << "您确定要继续吗？[y/n]";
				std::cin >> ss;
				if (ss == "y") {
					del_book(targ);
					targ = nullptr;
					std::cout << "删除成功" << std::endl;
					system("pause");
					return;
				}
				else break;
			}
			break;
		case 7:
			return;
		default: 
			std::cout << "无效的操作！" << std::endl;
			system("pause");
			break;
		}
	}
}
void ranking() {
	while (true) {
		std::cout << "请输入操作对应的序号" << std::endl;
		std::cout << "1.图书排名" << std::endl;
		std::cout << "2.用户排名" << std::endl;
		std::cout << "3.返回上一级" << std::endl;
		std::cout << now_usr->_name<<">" << std::endl;
		int opt;
		std::cin >> opt;
		switch (opt) {
		case 1:
			book_ranking();
			break;
		case 2:
			usr_ranking();
			break;
		case 3:
			return;
		default:
			std::cout << "无效的操作" << std::endl;
			system("pause");
			return;
		}
	}
}
void book_ranking() {
	for (std::map<std::string, book>::iterator i = books.begin(); i != books.end(); i++) {

	}
}