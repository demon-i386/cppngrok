#include <iostream>
#include "../cppngrok.h"

int main(){
	CppngrokHandler handler(true);
	struct address_handler teste = handler.bind();
	cout << endl;
	cout << "SUCCESS :: " << teste.ext_http << endl;
}
