 // AUTHOR : demon-i38 // LICENSE :
 // VERSION : 0.0.1

#pragma once
#ifndef CPPNGROK_H
#define CPPNGROK_H
#include <string>
using namespace std;

class Setup{
	public:
		Setup(bool log_opt = false, bool download_opt = true);
		int logger(bool log_handler = false, int log_level = 0, std::string message = "NONE");
};

#endif

