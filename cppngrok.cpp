#include "cppngrok.h"


/*
* AUTHOR : demon-i386 / KB1te
* LICENSE : GPL v3.0
* VERSION : 0.1.0
*/

using namespace std;
const char* path;

bool CppngrokHandler::UrlBuilder(in std::string regcheck, out char *buff) { // address_handler alocator, this will alocate address_handler structure with data and return address_handler
	std::regex https_rgx("https://[a-zA-Z0-9.ngrok.io]+");
	std::regex http_rgx("http://[a-zA-Z0-9.ngrok.io]+[^a-zA-Z/:localhost]io");
	std::regex tcp_rgx("tcp://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::regex tls_rgx("tls://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]io");
	std::smatch match;
	if (std::regex_search(regcheck, match, https_rgx)) {
		buff = match[0];
		return true;
	}

	if (std::regex_search(regcheck, match, http_rgx)) {
		buff = match[0];
		return true;
	} 

	if (std::regex_search(regcheck, match, tcp_rgx)) {
		return false;
	} 

	if (std::regex_match(regcheck, match, tls_rgx)) {
		return false;
	} 
	return false;
}

void CppngrokHandler::bind(){
	char *buff;
	buff = (char *) path;
	strncat(buff," http 80 --log stdout", 21);
	redi::ipstream is(buff);
	std::string outBuff;
	memset(buff,0,sizeof(buff);
	while(std::getline(is, outBuff)){
		pAddr = CppngrokHandler::UrlBuilder(outBuff,buff);
		if(pAddr){
			cout << "TRYING TO RETURN :: " << buff << endl;   
			is.close();
		}
	}
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


CppngrokHandler::CppngrokHandler() {
	buff = std::getenv("NGROK_PATH");
	if (buff == NULL) {
		CppngrokHandler::logger("PLEASE SET NGROK PATH TO ENV 'NGROK_PATH' AND TRY AGAIN", 3, log_handler);
	}
	else{
		path = buff;
	}
}
