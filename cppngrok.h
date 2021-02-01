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

using namespace std;

enum methods {
	ngroktcp = 1,
	ngroktls = 2,
	ngrokhttp = 3,
	ngrokhttps = 4,
};

struct address_handler{
          string ext_http;
          string ext_https;
          string ext_tcp;
          string ext_tls;
          string ext_tcp_port;
          string ext_tls_port;
 };

class CppngrokHandler{
	public:
		CppngrokHandler(bool log_opt);
		int logger(std::string message, int log_level, bool log_handler);
		address_handler* bind();
		int bind(int port, methods ngrokmethod);
	private:
		address_handler* UrlBuilder(std::string regcheck);
};


