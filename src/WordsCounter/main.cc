#include "WordsCounter.h"

int main(int argc,char * argv[])
{
	if(argc<3){
		cout << "filename please!" << endl;
		return -1;
	}
	WordsCounter test(argv[1]);
	test.read();
	test.save(argv[2]);
	return 0;
}
