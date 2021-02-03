#include "cppngrok.h"


/*
* AUTHOR : demon-i386 / KB1te
* LICENSE : GPL v3.0
* VERSION : 0.1.0
*/

using namespace std;
bool log_handler;
const char* path;



//  return type = struct address_handler declared in cppngrok.h
address_handler CppngrokHandler::UrlBuilder(std::string regcheck) { // address_handler alocator, this will alocate address_handler structure with data and return address_handler
	address_handler addr_handler;
	std::regex https_rgx("https://[a-zA-Z0-9.ngrok.io]+");
	std::regex http_rgx("http://[a-zA-Z0-9.ngrok.io]+[^a-zA-Z/:localhost]io");
	std::regex tcp_rgx("tcp://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::regex tls_rgx("tls://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::smatch match;
	if (std::regex_search(regcheck, match, https_rgx)) {
		addr_handler.ext_https = match[0];
	}

	if (std::regex_search(regcheck, match, http_rgx)) {
		addr_handler.ext_http = match[0];
	} 

	if (std::regex_search(regcheck, match, tcp_rgx)) {
		addr_handler.ext_tcp = match[0];
	} 

	if (std::regex_match(regcheck, match, tls_rgx)) {
		addr_handler.ext_tls = match[0];
	} 
	return addr_handler;
}

address_handler CppngrokHandler::bind() { // return type = struct address_handler declared in cppngrok.h
	char *buff;
	buff = (char *) path;
	strncat(buff," http 80 --log stdout", 21);
	redi::ipstream is(buff);
	struct address_handler pAddr;
	std::string outBuff;
	while(std::getline(is, outBuff)){
		cout << outBuff << endl;
		pAddr = CppngrokHandler::UrlBuilder(outBuff);
		if(!(pAddr.ext_https.empty()) && !(pAddr.ext_http.empty())){
			cout << "TRYING TO RETURN :: " << pAddr.ext_http << endl;   
			is.close();
		}
		
	}
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
	char *buff = { std::getenv("HOME") };
	strncat(buff, "/.local/bin/ngrok", 17);
	path = buff;
	cout << "NGROK PATH :: " << path << endl;;
	cout << "BUFFER :: " << buff << endl;
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


