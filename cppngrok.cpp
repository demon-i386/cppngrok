#include "cppngrok.h"


/*
* AUTHOR : demon-i386 / KB1te
* LICENSE : GPL v3.0
* VERSION : 0.1.0
*/

using namespace std;

bool log_handler;

//  return type = struct address_handler declared in cppngrok.h
address_handler* CppngrokHandler::UrlBuilder(std::string regcheck) { // address_handler alocator, this will alocate address_handler structure with data and return address_handler
	cout << "UrlBuilder" << endl << endl;
	std::regex httpsrgx("https://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::regex httprgx("http://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::regex tcprgx("tcp://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::regex tlsrgx("tls://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::smatch match;
	address_handler *addr_handler = NULL;
	cout << regcheck;

	if (std::regex_match(regcheck, match, httpsrgx)) {
		cout << "MATCHED :: " << match[0] << endl;
		addr_handler->ext_https = match[0];
		cout << "HTTPS :: " << addr_handler->ext_https;
	}
		

	if (std::regex_match(regcheck, match, httprgx)) {
		cout << "MATCHED :: " << match[0] << endl;
		addr_handler->ext_http = match[0];
		cout << "HTTP :: " << addr_handler->ext_http;
	}
		

	if (std::regex_match(regcheck, match, tcprgx)) {
		cout << "MATCHED :: " << match[0] << endl;
		addr_handler->ext_tcp = match[0];
	}
		

	if (std::regex_match(regcheck, match, tlsrgx)) {
		cout << "MATCHED :: " << match[0] << endl;
		addr_handler->ext_tls = match[0];
	}
	cout << addr_handler << endl;
	return addr_handler;
}

address_handler* CppngrokHandler::bind() { // return type = struct address_handler declared in cppngrok.h
	cout << NGROK_BINARY_PATH << endl;
	std::string run = NGROK_BINARY_PATH.append("http 80 --log stdout");
	CppngrokHandler::logger(run, 1, log_handler);
	FILE *pPipe = _popen(run.c_str, "r");
	char buf[512];
	unsigned int i = 0;
	for (i; i < 512; i++) {
		fgets(buf, 512, pPipe);
		if (i == 4) {
			if (!_strcmpi(buf, "http")) {
				return NULL;
			}
		}
	}
	
	address_handler *pAddr = CppngrokHandler::UrlBuilder(buf);
	_pclose(pPipe);
	return pAddr;
}


int CppngrokHandler::bind(int port, methods ngrokmethod) {
	switch (ngrokmethod) {
	case methods::ngrokhttp:
		//do shit
		break;
	case methods::ngrokhttps :
		//do shit
		break;
	case methods::ngroktcp:
		//do shit
		break;
	case methods::ngroktls:
		//do shit
		break;
	}
	return 0;
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
	log_handler = log_opt;
	FILE *file = NULL;
	NGROK_BINARY_PATH = (string)std::getenv("HOME") + "/.local/bin/ngrok";
	if (!fopen(NGROK_BINARY_PATH.c_str(), "rb")) {
		fclose(file);
	}
	else {
		CppngrokHandler::logger("NGROK NOT FOUND IN :: " + NGROK_BINARY_PATH, 2, log_handler);
		if (std::getenv("NGROK_PATH")) {
			NGROK_BINARY_PATH = std::getenv("NGROK_PATH");
		}
		else {
			CppngrokHandler::logger("PLEASE SET NGROK PATH TO ENV 'NGROK_PATH' AND TRY AGAIN", 3, log_handler);
		}
	}
}
