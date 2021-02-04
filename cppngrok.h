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
	tcp,
	tls,
	http
};


static const char *methods_str[] = { "tcp", "tls", "http" };

struct address_handler{
          string ext_http;
          string ext_tcp;
          string ext_tls;
          unsigned int ext_tcp_port;
          unsigned int ext_tls_port;
};

class CppngrokHandler{
	public:
		CppngrokHandler(bool log_opt);
		int logger(std::string message, int log_level, bool log_handler);
		address_handler* bind();
		address_handler* UrlBuilder(std::string regexfood = "NONE");
		address_handler* bind(methods ngrokmethods, unsigned int port = 1337);
};

