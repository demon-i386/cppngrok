 // AUTHOR : 70corre20matar // LICENSE :
 // VERSION : 0.0.1

#pragma once
#ifndef CPPNGROK_H
#define CPPNGROK_H
#include <string>
using namespace std;

class Setup{
	public:
		Setup(bool log_opt, bool download_opt);
		int logger(bool log_handler, int log_level, std::string message);
		void bind();
		int  bind(int mode,int port);
};

#endif

