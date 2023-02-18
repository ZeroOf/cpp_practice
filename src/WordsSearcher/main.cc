#include "WordsSearcher.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "filename please!" << endl;
        return -1;
    }
    string queryWord("The");

    TextQuery tq(argv[1]);
    tq.readFile();
    tq.query(queryWord);
    return 0;
}     	
