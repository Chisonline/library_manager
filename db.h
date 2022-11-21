#pragma once
#include <fstream>
#include "usr.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

static std::ifstream inFile;
static std::ofstream outFile;
void load_database();
void write_database();