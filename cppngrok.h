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

struct address_handler{
          string ext_http;
          string ext_https;
          string ext_tcp;
          string ext_tls;
          string ext_tcp_port;
          string ext_tls_port;
          bool stop_trigger = false;
 };



class CppngrokHandler{
	public:
		CppngrokHandler(bool log_opt);
		int logger(std::string message, int log_level, bool log_handler);
		address_handler bind();
		address_handler UrlBuilder(std::string regcheck);
		int bind(int port, methods ngrokmethods);
};

