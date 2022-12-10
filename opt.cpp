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
		system("pause");
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
	std::cout << "3.���а�" << std::endl;
	std::cout << "4.�˳���¼" << std::endl;
	std::cout << "5.�ر�ϵͳ" << std::endl;
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
			std::cout << "�����Ǳ�ϵͳ�Ĺ���Ա" << std::endl;
			system("pause");
			break;
		}
		admin_opt();
		break;
	default:
		std::cout << "��Ч�Ĳ���" << std::endl;
		system("pause");
	}
}
void Back(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "δ�ҵ�Ŀ���鼮" << std::endl;
		system("pause");
		return;
	}
	if (now_usr->find_borrow(ss) == -1) {
		std::cout << "δ����Ŀ���鼮" << std::endl;
		system("pause");
		return;
	}
	now_usr->back(ss);
	book* ptr = &books[ss];
	ptr->back();
	std::cout << "�黹�ɹ���" << std::endl;
	system("pause");
}
void Borrow(std::string ss) {
	if (books.find(ss) == books.end()) {
		std::cout << "δ�ҵ�Ŀ���鼮" << std::endl;
		system("pause");
		return;
	}
	book* ptr = &books[ss];
	if (ptr->borrow(now_usr->_name)) {
		now_usr->borrow(*ptr);
		std::cout << "���ĳɹ���" << std::endl;
		system("pause");
		return;
	}
	else {
		std::cout << "Ŀ���鼮�ѱ�����" << std::endl;
		system("pause");
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
		std::cout << now_usr->_name << ">";
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
			system("pause");
			break;
		}
		}
	}
}
void admin_opt() {
	while (true) {
		system("cls");
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.�û�����" << std::endl;
		std::cout << "2.ͼ�����" << std::endl;
		std::cout << "3.������һ��" << std::endl;
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
			std::cout << "��Ч�Ĳ�����" << std::endl;
			system("pause");
			break;
		}
	}
}
void admin_usr_opt() {
	while (true) {
		system("cls");
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.�о��û��б�" << std::endl;
		std::cout << "2.�޸��û�" << std::endl;
		std::cout << "3.������һ��" << std::endl;
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
			std::cout << "��Ч�Ĳ�����" << std::endl;
			system("pause");
			break;
		}
	}
}
void change_usr() {
	usr* targ = nullptr;
	while (true) {
		system("cls");
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.ѡ���û�" << std::endl;
		std::cout << "2.������һ��" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		bool flag = false;
		std::string s1;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "������Ŀ���û���:" << std::endl;
			std::cin >> s1;
			if (user.find(s1) == user.end()) {
				std::cout << "û���ҵ����û�" << std::endl;
				system("pause");
				break;
			}
			targ = &user[s1];
			flag = true;
			break;
		case 2:
			return;
		default:
			std::cout << "��Ч�Ĳ�����" << std::endl;
			system("pause");
			return;
		}
		if (flag)break;
	}
	while (true) {
		system("cls");
		std::cout << "Ŀǰ�����޸ĵ��û���" << targ->_name << std::endl;
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.��������" << std::endl;
		std::cout << "2.�����û���" << std::endl;
		std::cout << "3.ɾ���û�" << std::endl;
		std::cout << "4.��ѯ���û������б�" << std::endl;
		std::cout << "5.������һ��" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::string ss;
		std::cin >> opt;
		switch (opt) {
		case 1:
			targ->change_passwd("123456");
			std::cout << targ->_name << " �������Ѿ�����Ϊ��123456" << std::endl;
			system("pause");
			break;
		case 2:
			std::cout << "���������û���" << std::endl;
			std::cin >> ss;
			targ->change_name(ss);
			std::cout << "���û����û����Ѿ��޸�Ϊ��" << ss << std::endl;
			system("pause");
			break;
		case 3:
			std::cout << "���棡���û�������Ϣ����ǿ��ɾ����" << std::endl;
			std::cout << "���û�����δ�黹�鼮����ǿ������Ϊ�ѹ黹��" << std::endl;
			while (true) {
				std::cout << "��ȷ��Ҫ������?[y/n]";
				std::cin >> ss;
				if (ss == "y") { 
					del_usr(targ);
					targ = nullptr;
					std::cout << "ɾ���ɹ�" << std::endl;
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
			std::cout << "��Ч�Ĳ�����" << std::endl;
			system("pause");
			break;
		}
	}
}
void admin_book_opt() {
	book* targ = nullptr;
	while (true) {
		system("cls");
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.��ѯ�鼮������Ϣ" << std::endl;
		std::cout << "2.�޸��鼮" << std::endl;
		std::cout << "3.�����鼮" << std::endl;
		std::cout << "4.������һ��" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		std::string ss,s1;
		book* tmp;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "������Ŀ���鼮����" << std::endl;
			std::cin >> ss;
			if (books.find(ss) == books.end()) {
				std::cout << "δ�ҵ�Ŀ���鼮��" << std::endl;
				system("pause");
				break;
			}
			targ = &books[ss];
			std::cout << "�����ߣ� " << targ->WhoBorrow() << std::endl;
			targ = nullptr;
			system("pause");
			break;
		case 2:
			change_book(nullptr);
			break;
		case 3:
			std::cout << "�����������鼮����" << std::endl;
			std::cin >> ss;
			tmp = new book(ss, "NULL", "NULL", "NULL", 1, "NULL", 0.00, 0);
			books[ss] = *tmp;
			while (true) {
				std::cout << "�Ƿ������༭��ͼ��������Ϣ��[y/n]";
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
			std::cout << "��Ч�Ĳ�����" << std::endl;
			system("pause");
			break;
		}
	}
}
void change_book(book* targ) {
	std::string ss;
	while (targ == nullptr) {
		system("cls");
		std::cout << "������Ŀ���鼮����" << std::endl;
		std::cin >> ss;
		if (books.find(ss) == books.end()) {
			std::cout << "δ�ҵ����鼮��" << std::endl;
			system("pause");
			continue;
		}
		targ = &books[ss];
	}
	while (true) {
		system("cls");
		std::cout << "Ŀǰ�����޸ĵ��鼮��" <<targ->show_name() << std::endl;
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.�޸��鼮����" << std::endl;
		std::cout << "2.�޸��鼮ISBN" << std::endl;
		std::cout << "3.�޸��鼮����" << std::endl;
		std::cout << "4.�޸��鼮������" << std::endl;
		std::cout << "5.�޸��鼮�۸�" << std::endl;
		std::cout << "6.ɾ���鼮" << std::endl;
		std::cout << "7.������һ��" << std::endl;
		std::cout << now_usr->_name << ">";
		int opt;
		double num;
		std::cin >> opt;
		switch (opt) {
		case 1:
			std::cout << "�������µ�����" << std::endl;
			std::cin >> ss;
			if (targ->change_name(ss)) {
				std::cout << "�����Ѿ��޸�Ϊ" << targ->show_name() << std::endl;
				system("pause");
			}
			else {
				std::cout << "�ݲ�֧���鼮ͬ��" << std::endl;
				system("pause");
				break;
			}
			break;
		case 2:
			std::cout << "�������µ�ISBN" << std::endl;
			std::cin >> ss;
			targ->change_ISBN(ss);
			std::cout << "ISBN�Ѿ��޸�Ϊ��" << ss << std::endl;
			system("pause");
			break;
		case 3:
			std::cout << "�������µ�����" << std::endl;
			std::cin >> ss;
			targ->change_writer(ss);
			std::cout << "�����Ѿ��޸�Ϊ��" << ss << std::endl;
			system("pause");
			break;
		case 4:
			std::cout << "�������µĳ�����" << std::endl;
			std::cin >> ss;
			targ->change_house(ss);
			std::cout << "�������Ѿ��޸�Ϊ��" << ss << std::endl;
			system("pause");
			break;
		case 5:
			std::cout << "�������µļ۸�" << std::endl;
			std::cin >> num;
			targ->change_price(num);
			std::cout << "�۸��Ѿ��޸�Ϊ��" << num << std::endl;
			system("pause");
			break;
		case 6:
			std::cout << "���棡���鼮������Ϣ����ɾ����" << std::endl;
			std::cout << "�ò������ɳ��أ�" << std::endl;
			while (true) {
				std::cout << "��ȷ��Ҫ������[y/n]";
				std::cin >> ss;
				if (ss == "y") {
					del_book(targ);
					targ = nullptr;
					std::cout << "ɾ���ɹ�" << std::endl;
					system("pause");
					return;
				}
				else break;
			}
			break;
		case 7:
			return;
		default: 
			std::cout << "��Ч�Ĳ�����" << std::endl;
			system("pause");
			break;
		}
	}
}
void ranking() {
	while (true) {
		std::cout << "�����������Ӧ�����" << std::endl;
		std::cout << "1.ͼ������" << std::endl;
		std::cout << "2.�û�����" << std::endl;
		std::cout << "3.������һ��" << std::endl;
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
			std::cout << "��Ч�Ĳ���" << std::endl;
			system("pause");
			return;
		}
	}
}
void book_ranking() {
	for (std::map<std::string, book>::iterator i = books.begin(); i != books.end(); i++) {

	}
}