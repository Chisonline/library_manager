#pragma once
#include "db.h"
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
extern usr* now_usr;
void shutdown();
void login();
void welcome();
void regist();
void operat();
void op_book();
void Borrow(std::string ss);
void Back(std::string ss);
void admin_opt();