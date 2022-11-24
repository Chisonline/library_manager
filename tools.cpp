#include "tools.h"
std::string get_pwd() {
	std::string re;
	while (true) {
		char ch = _getch();
		if (ch == '\r') {
			putchar('\r');
			break;
		}
		re += ch;
	}
	return re;
}
