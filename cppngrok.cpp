#include "cppngrok.h"

/*
* AUTHOR : demon-i386
* LICENSE : GPL v3.0
* VERSION : 0.1.0
*/

using namespace std;
bool log_handler;
const char* path;
address_handler *addr_h;


address_handler *CppngrokHandler::UrlBuilder(std::string regex_food) { // address_handler alocator, this will alocate address_handler structure with data and return address_handler
	std::regex http_rgx("http://[a-zA-Z0-9.ngrok.io]+[^a-zA-Z/:localhost]io");
	std::regex tcp_rgx("tcp://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::regex tls_rgx("tls://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::smatch match;
	if (std::regex_search(regex_food, match, http_rgx)) {
		cout << "HTTP ADDRESS FOUND :: " << match[0] << endl;
		addr_h->ext_http = match[0];
	}
	if (std::regex_search(regex_food, match, tcp_rgx)) {
		cout << "TCP ADDRESS FOUND :: " << match[0] << endl;
		addr_h->ext_tcp = match[0];
	}
	if (std::regex_match(regex_food, match, tls_rgx)) {
		addr_h->ext_tls = match[0];
	}
	return addr_h;
}

address_handler *CppngrokHandler::bind() { // return type = struct address_handler declared in cppngrok.h
	char *buff;
	buff = (char *) path;
	redi::ipstream is((string)buff+(string)" http 80 --log stdout");
	std::string outBuff;
	while(std::getline(is, outBuff)){
		addr_h = CppngrokHandler::UrlBuilder(outBuff);
		if(!addr_h->ext_http.empty()){
			is.close();
		}
	}
	return addr_h;
}


address_handler *CppngrokHandler::bind(methods ngrokmethod, unsigned int port) {
	char *buff;
	buff = (char *) path;
	if(sizeof(port) > 5){
		cout << "FUCK U";
		exit(1);
	}
	char command[25];
	char char_port[5 + sizeof(char)];
	char method[4 + sizeof(char)];

	std::sprintf(method, "%s", methods_str[ngrokmethod]);
	std::sprintf(char_port, "%d", port);
	std::sprintf(command, " %s %s --log stdout", methods_str[ngrokmethod], char_port);

	redi::ipstream is ((string) buff + (string)command);

	memset(command, 0, sizeof(command));
	memset(char_port, 0, sizeof(char_port));
	memset(method, 0, sizeof(method));

	std::string outBuff;

	switch (ngrokmethod) {
	case methods::http:
		while(std::getline(is, outBuff)){
			addr_h = CppngrokHandler::UrlBuilder(outBuff);
			if(!addr_h->ext_http.empty()){
				cout << "RETURNED HTTP :: " << addr_h->ext_http << endl;
				is.close();
				if (is.rdbuf()->exited()){
					cout << "EXITED" << endl;
					
				}
			}
		}
		break;
	case methods::tcp:
		while(std::getline(is, outBuff)){
			addr_h = CppngrokHandler::UrlBuilder(outBuff);
			if(!addr_h->ext_tcp.empty()){
				cout << "RETURNED TCP :: " << addr_h->ext_tcp << endl;
				is.close();
			}
		}
		break;
	case methods::tls:
		while(std::getline(is, outBuff)){
			addr_h = CppngrokHandler::UrlBuilder(outBuff);
			if(!addr_h->ext_tls.empty()){
				is.close();
			}
		}
	}
	return addr_h;
}


int CppngrokHandler::logger(std::string message, int log_level, bool log_handler) {
	printf("[%d]", log_handler);
	if (log_handler == false) {
		return 0;
	}
	switch (log_level) {
	case 1:
		cout << "[NOTE] " << message << endl;
		break;
	case 2:
		cout << "[WARNING] " << message << endl;
		break;
	case 3:
		cout << "[ERROR] " << message << endl;
		break;
	case 4:
		cout << "[CRITICAL] " << message << endl;
		break;
	case 5:
		cout << "[DEBUG] " << message << endl;
		break;
	case 0:
		break;
	}
	return 0;
}


CppngrokHandler::CppngrokHandler(bool log_opt) {
	addr_h = (address_handler*)calloc(sizeof(std::string) * 3, sizeof(addr_h));
	log_handler = log_opt;
	char *buff = { std::getenv("HOME") };
	strncat(buff, "/.local/bin/ngrok", 17);
	path = buff;
	if (FILE *file = fopen(buff, "rb")) {
		fclose(file);
	}
	else {
		if (std::getenv("NGROK_PATH")) {
			buff = std::getenv("NGROK_PATH");
		}
		else {
			CppngrokHandler::logger("PLEASE SET NGROK PATH TO ENV 'NGROK_PATH' AND TRY AGAIN", 3, log_handler);
		}
	}
}
