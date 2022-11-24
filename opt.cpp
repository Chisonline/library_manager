#include "opt.h"
usr* now_usr=nullptr;
void shutdown() {
	write_database();
	std::cout << "��л����ʹ�ã��ټ�" << std::endl;
	Sleep(500);
	exit(0);
}
void login() {
	system("cls");
	std::cout << "�������û���:" << std::endl;
	std::string usr_name, passwd;
	std::cin >> usr_name;
	if (user.count(usr_name) == 0) {
		std::cout << "��Ч���û�����" << std::endl;
		system("pause");
		welcome();
		return;
	}
	now_usr = &user[usr_name];
	std::cout << "����������:" << std::endl;
	passwd = get_pwd();
	if (now_usr->checklogin(passwd)) {
		std::cout << "��¼�ɹ���" << std::endl;
		std::cout << "��ӭ " << usr_name << std::endl;
		return;
	}
	else {
		std::cout << "�������" << std::endl;
		now_usr = nullptr;
		welcome();
		return;
	}
}
void welcome() {
	system("cls");
	std::cout << "��ӭ����H��ѧͼ�����Ϣ����ϵͳ" << std::endl;
	std::cout << "�����������Ӧ���" << std::endl;
	std::cout << "1.��¼" << std::endl;
	std::cout << "2.ע��" << std::endl;
	std::cout << "3.��Ϊ�ÿͽ���" << std::endl;
	std::cout << "4.�ر�ϵͳ" << std::endl;
	std::cout << ">";
	int op;
	std::cin >> op;
	if (op < 1 || op>4) {
		std::cout << "��Ч�Ĳ���" << std::endl;
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
	std::cout << "�������û���:" << std::endl;
	std::string usr_name, pwd1, pwd2;
	std::cin >> usr_name;
	if (user.find(usr_name) != user.end()) {
		std::cout << "�û����ѱ�ռ��" << std::endl;
		system("pause");
		welcome();
		return;
	}
	std::cout << "����������:" << std::endl;
	pwd1 = get_pwd();
	std::cout << "���ظ�������ȷ��" << std::endl;
	pwd2 = get_pwd();
	if (pwd1 != pwd2) {
		std::cout << "�������벻һ�£�" << std::endl;
		system("pause");
		welcome();
		return;
	}
	else {
		AddUsr(usr_name, pwd1, 2);
		now_usr = &user[usr_name];
		std::cout << "��¼�ɹ���" << std::endl;
		std::cout << "��ӭ " << now_usr->_name << std::endl;
		Sleep(500);
		return;
	}
}
void operat() {
	//Sleep(500);
	system("cls");
	std::cout << "�����������Ӧ���" << std::endl;
	std::cout << "1.ͼ�����" << std::endl;
	std::cout << "2.�û�����" << std::endl;
	std::cout << "3.�˳���¼" << std::endl;
	std::cout << "4.�ر�ϵͳ" << std::endl;
	std::cout << "0.����Աģʽ" << std::endl;
	std::cout << now_usr->_name << ">";
	int op;
	std::cin >> op;
	switch (op) {
	case 1:
		op_book();
		break;
	case 2:
		if (now_usr->_name == "visitor") {
			std::cout << "�ÿͲ����и�Ȩ��" << std::endl;
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
			std::cout << "�����Ǳ�ϵͳ�Ĺ���Ա" << std::endl;
			break;
		}
		admin_opt();
	default:
		std::cout << "��Ч�Ĳ���" << std::endl;
	}
}
void Back(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "δ�ҵ�Ŀ���鼮" << std::endl;
		return;
	}
	if (now_usr->find_borrow(ss) == -1) {
		std::cout << "δ����Ŀ���鼮" << std::endl;
		return;
	}
	now_usr->back(ss);
	book* ptr = &books[ss];
	ptr->back();
	std::cout << "�黹�ɹ���" << std::endl;
}
void Borrow(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "δ�ҵ�Ŀ���鼮" << std::endl;
		return;
	}
	book* ptr = &books[ss];
	if (ptr->borrow(now_usr->_name)) {
		now_usr->borrow(*ptr);
		std::cout << "���ĳɹ���" << std::endl;
		return;
	}
	else {
		std::cout << "Ŀ���鼮�ѱ�����" << std::endl;
		return;
	}
}

void op_book() {
	while (true) {
		system("cls");
		std::cout << "�����������Ӧ���" << std::endl;
		std::cout << "1.��ѯͼ��" << std::endl;
		std::cout << "2.����ͼ��" << std::endl;
		std::cout << "3.�黹ͼ��" << std::endl;
		std::cout << "4.������һ��" << std::endl;
		int opt;
		std::cin >> opt;
		switch (opt) {
		case 1: {
			std::cout << "���������� ������ISBN/ISSN�����ߡ������� ���κ������Ϣ��" << std::endl;
			std::string s1;
			std::cin >> s1;
			Search(s1);
			break;
		}
		case 2: {
			std::cout << "������Ҫ���ĵ�����" << std::endl;
			std::string s2;
			std::cin >> s2;
			Borrow(s2);
			break;
		}
		case 3: {
			std::cout << "������Ҫ�黹������" << std::endl;
			std::string s3;
			std::cin >> s3;
			Back(s3);
			break;
		}
		case 4: {
			return;
		}
		default: {
			std::cout << "��Ч�Ĳ�����" << std::endl;
			break;
		}
		}
	}
}
void admin_opt() {

}