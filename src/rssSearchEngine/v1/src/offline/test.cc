#include "Configuration.h"
#include "DirScanner.h"
#include "PageLib.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	if(argc != 2){
		cout << "conf dir please!" << endl;
	}
	Configuration *conf = Configuration::CreateConf(argv[1]);
	DirScanner test(*conf);
	PageLib page(*conf,test);
	page.create();
	page.store();
	cout << "store" << endl;
	return 0;
}
