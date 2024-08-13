//
// Created by jacob on 1/18/2022.
//

#ifndef LAB1_SCANNER_H
#define LAB1_SCANNER_H

#include "Token.h"
#include <iostream>
#include <strstream>



using namespace std;

class Scanner {
private:
    string input;
    unsigned int lineNum = 0;

public:
    Scanner(const string &input) : input(input) {}

    Token scanToken()
    {
        string value = "";
        TokenType type = TokenType::UNDEFINED;
        unsigned int size = 0;
        while (isspace(input.at(0))) {
            if (input.at(0) == '\n')
            input = input.substr(1, input.size() - 1);
        }

        switch (input.at(0))
        {
            case ',':
                size = 1;
                Token out(",", TokenType::COMMA, lineNum);
                break;
        }

        value = input.substr(0,size);
        input = input.substr(size, input.size() - 1);
        return Token(value, type, lineNum);
    }
};


#endif //LAB1_SCANNER_H

