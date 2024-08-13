//
// Created by jacob on 1/18/2022.
//

#ifndef LAB1_SCANNER_H
#define LAB1_SCANNER_H

#include "Token.h"
#include <iostream>
#include <sstream>
#include <cwctype>



using namespace std;

class Scanner {
private:
    string input;
    unsigned int lineNum = 1;

public:
    Scanner(const string &input) : input(input) {}

    unsigned int getIDSize() {
        unsigned int IDSize = 0;
        while (!isspace(input.at(IDSize))) {
            if (iswalnum(input.at(IDSize)))
                IDSize++;
            else {
                return IDSize;
            }
        }
        return IDSize;
    }

    unsigned int getStringSize(bool &isUndefined) {
        unsigned int stringSize = 1;
        bool endOfString = false;
        while (!endOfString) {
            if (stringSize >= input.size()) {
                isUndefined = true;
                return stringSize;
            } else if (input.substr(stringSize, 2) == "\'\'")
                stringSize += 2;
            else if (input.at(stringSize) == '\'') {
                stringSize++;
                endOfString = true;
            } else if (input.at(stringSize) == '\n') {
                stringSize++;
                lineNum++;
            } else {
                stringSize++;
            }
        }

        return stringSize;
    }

    unsigned int getCommentSize (bool &isUndefined) {
        unsigned int commentSize = 1;
        bool endOfComment = false;
        if (input.at(1) == '|') {    // Block Comment
            while (!endOfComment) {
                if (commentSize + 1 >= input.size()) {
                    isUndefined = true;
                    return commentSize;
                } else if (input.substr(commentSize,2) == "|#") {
                    commentSize += 2;
                    endOfComment = true;
                } else if (input.at(commentSize) == '\n'){
                    commentSize++;
                    lineNum++;
                } else {
                    commentSize++;
                }
            }
        } else {
            while (!endOfComment) {    // Single Line Comment
                if (commentSize + 1 >= input.size()) {
                    endOfComment = true;
                    commentSize++;
                } else if (input.at(commentSize) == '\n') {
                    endOfComment = true;
                } else {
                    commentSize++;
                }
            }
        }

        return commentSize;
    }

    bool checkKeyWord() {
        if (input.at(0) == 'S') {
            if (input.substr(0,7) == "Schemes") {
                if (input.size() == 7)
                    return true;
                if (!iswalnum(input.at(7)))
                    return true;
            }
        }
        if (input.at(0) == 'F') {
            if (input.substr(0,5) == "Facts") {
                if (input.size() == 5)
                    return true;
                if (!iswalnum(input.at(5)))
                    return true;
            }
        }
        if (input.at(0) == 'R') {
            if (input.substr(0,5) == "Rules") {
                if (input.size() == 5)
                    return true;
                if (!iswalnum(input.at(5)))
                    return true;
            }
        }
        if (input.at(0) == 'Q') {
            if (input.substr(0,7) == "Queries") {
                if (input.size() == 7)
                    return true;
                if (!iswalnum(input.at(7)))
                    return true;
            }
        }
        return false;
    }

    Token scanToken()
    {
        string value;
        TokenType type = TokenType::UNDEFINED;
        unsigned int tempLineNum = lineNum;
        bool isUndefined = false;
        unsigned int size = 0;
        if (input.size() == 0) {
            type = TokenType::EOFILE;
            value = "";
            return Token(value, type, lineNum);
        }
        while (isspace(input.at(0))) {
            if (input.at(0) == '\n') {
                lineNum++;
                tempLineNum++;
            }
            input = input.substr(1, input.size() - 1);
            if (input.size() == 0) {
                type = TokenType::EOFILE;
                value = "";
                return Token(value, type, lineNum);
            }
        }
        if (input.size() == 0) {
            type = TokenType::EOFILE;
            value = "";
            return Token(value, type, lineNum);
        }

        switch (input.at(0))
        {
            case ',':
                size = 1;
                type = TokenType::COMMA;
                break;
            case '.':
                size = 1;
                type = TokenType::PERIOD;
                break;
            case '?':
                size = 1;
                type = TokenType::Q_MARK;
                break;
            case '(':
                size = 1;
                type = TokenType::LEFT_PAREN;
                break;
            case ')':
                size = 1;
                type = TokenType::RIGHT_PAREN;
                break;
            case ':':
                if (input.at(1) == '-') {
                    size = 2;
                    type = TokenType::COLON_DASH;
                } else {
                    size = 1;
                    type = TokenType::COLON;
                }
                break;
            case '*':
                size = 1;
                type = TokenType::MULTIPLY;
                break;
            case '+':
                size = 1;
                type = TokenType::ADD;
                break;
            case 'S':
                if (checkKeyWord()) {
                    size = 7;
                    type = TokenType::SCHEMES;
                }
                break;
            case 'F':
                if (checkKeyWord()) {
                    size = 5;
                    type = TokenType::FACTS;
                }
                break;
            case 'R':
                if (checkKeyWord()) {
                    size = 5;
                    type = TokenType::RULES;
                }
                break;
            case 'Q':
                if (checkKeyWord()) {
                    size = 7;
                    type = TokenType::QUERIES;
                }
                break;
            case '\'':
                size = getStringSize(isUndefined);
                if (isUndefined)
                    type = TokenType::UNDEFINED;
                else
                    type = TokenType::STRING;
                break;
            case '#':
                size = getCommentSize(isUndefined);
                if (isUndefined)
                    type = TokenType::UNDEFINED;
                else
                    type = TokenType::COMMENT;
                break;
        }
        if (size == 0) {
            if (isalpha(input.at(0))) {
                size = getIDSize();
                type = TokenType::ID;
            } else {
                size = 1;
                type = TokenType::UNDEFINED;
            }
        }


        value = input.substr(0,size);
        input = input.substr(size, input.size() - 1);
        return Token(value, type, tempLineNum);
    }


};



#endif //LAB1_SCANNER_H
