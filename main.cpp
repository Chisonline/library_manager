#include "opt.h"
int main() {
	load_database();
	welcome();
	while(true)
		operat();
	return 0;
}
