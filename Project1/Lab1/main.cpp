#include <iostream>
#include <fstream>
#include<sstream>
#include<string>
#include "Token.h"
#include "Scanner.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Not enough arguments.  Expected and integer N" << endl;
        return -1;
    }

    ifstream infile;
    string file = argv[1];
    infile.open(file);
    string input;
    unsigned int numTokens = 0;

    if(infile.is_open()) {
        ostringstream ss;
        ss << infile.rdbuf();
        input = ss.str();
    }
    Scanner s = Scanner(input);
    bool endOfFile = false;

    while (!endOfFile) {
        Token t = s.scanToken();
        cout << t.toString() << endl;
        if (t.getType() == TokenType::EOFILE)
            endOfFile = true;
        numTokens++;
    }
    cout << "Total Tokens = " << numTokens << endl;
    return 0;
}
