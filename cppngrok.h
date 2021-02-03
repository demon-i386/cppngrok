 // AUTHOR : demon-i38 / KB1te
 // LICENSE : GPL 3.0
 // VERSION : 0.1.0

#pragma once

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <locale>
#include <regex>
#include "pstream.h"

using namespace std;

enum methods {
	ngroktcp = 1,
	ngroktls = 2,
	ngrokhttp = 3,
	ngrokhttps = 4,
};



class CppngrokHandler{
	public:
		CppngrokHandler(bool log_opt);
		int logger(std::string message, int log_level, bool log_handler);
		void bind();
		bool UrlBuilder(in std::string regcheck,out char *buff);
		int bind(int port, methods ngrokmethods);
};

