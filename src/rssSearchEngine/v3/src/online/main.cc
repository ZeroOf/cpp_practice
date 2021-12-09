#include "Configuration.h"
#include "Acceptor.h"
#include "WordQueryServer.h"
#include "SocketUtil.h"
#include <stdlib.h>
#include <iostream>

using std::string;
using std::map;

int main()
{
	Configuration * conf = Configuration::CreateConf("../../conf/myconf.conf");
	map<string,string> temp = conf->getConfigMap();
	WordQueryServer wqs(*conf);
    wqs.Start();
	return 0;
}
