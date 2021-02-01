#include <iostream>
#include <typeinfo>
#include <string>
#include "cppngrok.h"
#include <sys/utsname.h>
#include <openssl/err.h>
#include <iostream>
#include <sys/socket.h>
#include <algorithm>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <locale>
#include <regex>
/*
* AUTHOR : demon-i386
* LICENSE : GPL v3.0
* VERSION : 0.0.1
*/

using namespace std;

int STARTUP_TIMEOUT = 15;
bool log_handler;

// tá errado? oq eu faço ent como declaro krl


string CppngrokHandler::convertToString(char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

// e esse auto aqui?
//
address_handler* CppngrokHandler::UrlBuilder(std::string regcheck){
	cout << "UrlBuilder" << endl << endl;
	std::regex httpsrgx("https://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::regex httprgx("http://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");  
	std::regex tcprgx("tcp://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::regex tlsrgx("tls://[a-zA-Z0-9.]+[^a-zA-Z/:localhost]");
	std::smatch match;
	address_handler *addr_handler = NULL;
	cout << regcheck;
	if(std::regex_match(regcheck, match, httpsrgx))
		cout << "MATCHED :: " << match[0] << endl;
		addr_handler->ext_https = match[0];
		cout << "HTTPS :: " << addr_handler->ext_https;

	if(std::regex_match(regcheck, match, httprgx))
		cout << "MATCHED :: " << match[0] << endl;  
		addr_handler->ext_http = match[0];
		cout << "HTTP :: " << addr_handler->ext_http;

	if(std::regex_match(regcheck, match, tcprgx))
		cout << "MATCHED :: " << match[0] << endl;  
		addr_handler->ext_tcp = match[0];

	if(std::regex_match(regcheck, match, tlsrgx))
		cout << "MATCHED :: " << match[0] << endl;  
		addr_handler->ext_tls = match[0];

	cout << addr_handler << endl;
	return addr_handler;
}

address_handler* CppngrokHandler::bind(){
	pid_t ngrok_pid;
	cout << NGROK_BINARY_PATH << endl;
	std::string command = " http 80 --log stdout";
	std::string run = NGROK_BINARY_PATH + command;

	FILE *proc_handler = popen(run.c_str(),"r");
	if(!proc_handler){
		CppngrokHandler::logger("FAILED TO FORK NGROK", 4, log_handler);
		pclose(proc_handler);
	}
	cout << "MASTER PROCESS PID :: " << getpid() << endl << endl;
	char buf[500];
	while ( fgets(buf, 500,proc_handler) != "https"){
    		string regcheck = convertToString(buf, sizeof(buf));	
		struct address_handler &addrr_handler = CppngrokHandler::UrlBuilder(regcheck);
		return addrr_handler;
	};
}


int CppngrokHandler::bind(int port, std::string method){
	printf("PORT :: %d\nMETHOD :: %s\n", port, method.c_str());
	return 0;

}


int CppngrokHandler::logger(std::string message, int log_level, bool log_handler){
	printf("[%d]", log_handler);
	if(log_handler == false){
		return 0;
	}
	switch (log_level){
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

CppngrokHandler::CppngrokHandler(bool log_opt){
	log_handler = log_opt;
	struct utsname buf1;
	uname(&buf1);
	
	std::string machine_name = (string) buf1.sysname;
	std::transform(machine_name.begin(), machine_name.end(), machine_name.begin(), ::tolower);

	std::string machine_info = machine_name + " " + (string) buf1.machine; 
	CppngrokHandler::logger(machine_info, 5, log_handler);

	NGROK_BINARY_PATH = (string) std::getenv("HOME") + "/.local/bin/ngrok";
	if (FILE *file = fopen(NGROK_BINARY_PATH.c_str(), "rb")){
		fclose(file);
	}
	else{
		CppngrokHandler::logger("NGROK NOT FOUND IN :: " + NGROK_BINARY_PATH, 1, log_handler);
		if(std::getenv("NGROK_PATH")){
			NGROK_BINARY_PATH = std::getenv("NGROK_PATH");
		}
		else{
			CppngrokHandler::logger("PLEASE SET NGROK PATH TO ENV 'NGROK_PATH' AND TRY AGAIN", 3, log_handler);
		}
	}
}

