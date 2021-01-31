#include <iostream>
#include <typeinfo>
#include "cppngrok.h"
#include <sys/utsname.h>


/*
* AUTHOR : demon-i386
* LICENSE : GPL v3.0
* VERSION : 0.0.1
*/

using namespace std;

int STARTUP_TIMEOUT = 15;
bool log_handler;

int Setup::logger(int log_level, std::string message){
	if(log_level == NULL){
		log_handler = false;
		return NULL;
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

Setup::Setup(bool log_opt, bool download_opt){
	log_handler = log_opt;
	struct utsname buf1;
	uname(&buf1);
	cout << buf1.sysname;
	string NGROK_BINARY_PATH = (string) std::getenv("HOME") + "/.local/bin/ngrok";
	if (FILE *file = fopen(NGROK_BINARY_PATH.c_str(), "rb")){
		fclose(file);
	}
	else{
		Setup::logger(log_handler, 1, "NGROK NOT FOUND IN :: " + NGROK_BINARY_PATH);
		if(std::getenv("NGROK_PATH")){
			NGROK_BINARY_PATH = std::getenv("NGROK_PATH");
		}
		else{
			Setup::logger(log_handler, 3, "PLEASE SET NGROK PATH TO ENV 'NGROK_PATH' AND TRY AGAIN");
			
		}
	}
}
