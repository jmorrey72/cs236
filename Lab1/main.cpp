#include <iostream>
#include "Token.h"
#include "Scanner.h"

int main() {
    Token t(",", TokenType::COMMA , 2);
    cout << t.toString() << endl;

    Scanner s = Scanner(",,");
    t = s.scanToken();
    cout << t.toString() << endl;

    return 0;
}

