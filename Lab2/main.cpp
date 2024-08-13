#include <iostream>
#include <vector>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[])
{

    vector<Token> tokens;

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
        tokens.push_back(t);
        //cout << t.toString();
        if (t.getType() == TokenType::EOFILE)
            endOfFile = true;
        numTokens++;
    }

    Parser parser(tokens);

    try
    {
        parser.parse();
        cout << "Success!" << endl;
        parser.print();
    }
    catch (Token errorToken) {
        cout << "Failure!\n" << "  " << errorToken.toString() << endl;
    }


    return 0;
}
