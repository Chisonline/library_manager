#include "admin.h"
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "db.h"
static usr* now_usr;
void welcome();
void shutdown() {
	write_database();
	std::cout << "��л����ʹ�ã��ټ�" << std::endl;
	Sleep(500);
	exit(0);
}
void login() {
	system("cls");
	std::cout << "�������û���:" << std::endl;
	std::string usr_name,passwd;
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
void regist() {
	system("cls");
	std::cout << "�������û���:" << std::endl;
	std::string usr_name, pwd1,pwd2;
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
		AddUsr(usr_name, pwd1,2);
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
	std::cout << now_usr->_name << ">" ;
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
			std::cout <<"�����Ǳ�ϵͳ�Ĺ���Ա" << std::endl;
			break;
		}
		//now_usr = new admin;
	default:
		std::cout << "��Ч�Ĳ���" << std::endl;
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