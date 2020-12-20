#include "Configuration.h"
#include "DictProductor.h"
#include "Mydict.h"
#include <iostream>

using std::cout;
using std::endl;
int main(int argc, char * argv[])
{
	if(argc != 2){
		std::cout << "args error" << std::endl;
		exit(-1);
	}
	Configuration conf(argv[1]);
	DictProductor dict(conf.getConfigMap()["cnfile"],conf.getConfigMap()["enfile"]);
	dict.build_dict();
	dict.store_dict(conf.getConfigMap()["mydict"]);

	Mydict index(dict.getCndict(),dict.getEndict());
	index.getIndexTable();
	index.saveIndex(conf.getConfigMap()["myindex"]);
	return 0;
}
