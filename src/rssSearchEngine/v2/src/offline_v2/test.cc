#include "PageLibPreprocessor.h"
#include "Configuration.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	if(argc != 2){
		cout << "Configuration director please!" << endl;
	}
	Configuration *conf = Configuration::CreateConf(argv[1]);
//	DirScanner test(*conf);
//	PageLib page(*conf,test);
//	page.create();
//	page.store();
	PageLibPreprocessor test(*conf);
	test.doProcess();
	return 0;
}
