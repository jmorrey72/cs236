#include <iostream>
#include <vector>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"
#include "Database.h"
#include "Interpreter.h"


using namespace std;

int main(int argc, char* argv []) {

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

    DatalogProgram datalog;

    try
    {
        parser.parse();
        //cout << "Success!" << endl;
        //parser.print();
        datalog = parser.getDatalog();
    }
    catch (Token errorToken) {
        cout << "Failure!\n" << "  " << errorToken.toString() << endl;
    }

    Interpreter interpreter(datalog);

    interpreter.generateDatabase();
    //interpreter.printDatabase();
    interpreter.evaluate();


    /*vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    vector<string> columns = {"Ident","Title","Prison"};

    Relation result = relation.rename(columns);

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();
    */
}