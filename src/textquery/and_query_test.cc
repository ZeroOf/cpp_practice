#include "query.h"
#include "text_query.h"

#include <string>

using std::string;

#include <iostream>

using std::cout; using std::endl;

#include <set>

using std::set;

int main(int argc, char **argv) {
    // gets file to read and builds map to support queries
    TextQuery file = get_file(argc, argv);

    do {
        string sought1, sought2;
        // Stop if hit eof on input or a "q" is entered
        if (!get_words(sought1, sought2)) break;

        // find all the occurrences of the requested string
        Query andq = Query(sought1) & Query(sought2);
        cout << "\nExecuting query for: " << andq << endl;
        QueryResult results = andq.eval(file);
        // report matches
        print(cout, results);

        results = Query(sought1).eval(file);
        cout << "\nExecuted query: " << Query(sought1) << endl;
        // report matches
        print(cout, results);

        results = Query(sought2).eval(file);
        cout << "\nExecuted query: " << Query(sought2) << endl;
        // report matches
        print(cout, results);
    } while (true);

    return 0;
}
