#include "utils.h"
#include <iostream>
#include "parser.h"


using namespace std;

int main(int argc, const char * argv[]) {
    try {
        benchmark b;
        txf_object result = parse("/Users/taoufik/Desktop/TxfParser/TxfParser/Members.txf");
        cout << "elapsed " << b.elapsed() <<  " ms" << endl;
        visualise(result);
    } catch(string s) {
        cout << "error " << s;
    }
    return 0;
}
