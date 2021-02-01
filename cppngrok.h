 // AUTHOR : demon-i38 / KB1te
 // LICENSE : GPL 3.0
 // VERSION : 0.0.1

#pragma once
#ifndef CPPNGROK_H
#define CPPNGROK_H
#include <string>
#include <regex>
using namespace std;


struct address_handler{
          string ext_http;
          string ext_https;
          string ext_tcp;
          string ext_tls;
          string ext_tcp_port;
          string ext_tls_port;
 };

class CppngrokHandler{
	string NGROK_BINARY_PATH;
	public:
		CppngrokHandler(bool log_opt);
		int logger(std::string message, int log_level, bool log_handler);
		address_handler* bind();
		int bind(int port, std::string method);
		std::string convertToString(char* a, int size);
	private:
		address_handler* UrlBuilder(std::string regcheck);
};

#endif

