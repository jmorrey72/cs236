//
// Created by jacob on 2/1/2022.
//

#ifndef LAB2_PARSER_H
#define LAB2_PARSER_H

#include <vector>
#include "Token.h"
#include <iostream>
#include "Parameter.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Relation.h"

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    unsigned int index = 0;
    DatalogProgram datalog;


public:
    Parser(const vector<Token> &tokens) : tokens(tokens) {}

    TokenType tokenType() const {
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    void throwError() {
        cout << "error" << endl;
    }
    DatalogProgram getDatalog() {
        return datalog;
    }

    void match(TokenType type) {
        //cout << "match: " << tokenToString(type) << endl << tokenToString(tokens.at(index).getType()) << ":" << tokens.at(index).getValue() << endl;
        while (tokens.at(index).getType() == TokenType::COMMENT) {
            index++;
        }
        if (tokens.at(index).getType() == type) {
            index++;
        }
        else
            throw tokens.at(index);
    }

    void print() {
        datalog.print();
    }

    void parse() {
        match(TokenType::SCHEMES);
        match(TokenType::COLON);
        parseScheme();
        parseSchemeList();
        match(TokenType::FACTS);
        match(TokenType::COLON);
        parseFactList();
        match(TokenType::RULES);
        match(TokenType::COLON);
        parseRuleList();
        match(TokenType::QUERIES);
        match(TokenType::COLON);
        parseQuery();
        parseQueryList();
        //datalog.print();
    }

    void parseIdList(Predicate &pred) {
        if (tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            Parameter param(tokens.at(index).getValue());
            pred.addParameter(param);
            match(TokenType::ID);
            parseIdList(pred);
        } else {
            return;
        }
    }

    void parseScheme() {
        Predicate pred(tokens.at(index).getValue());
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        Parameter param(tokens.at(index).getValue());
        pred.addParameter(param);
        match(TokenType::ID);
        parseIdList(pred);
        match(TokenType::RIGHT_PAREN);
        datalog.addScheme(pred);
    }

    void parseStringList(Predicate &pred) {
        if (tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            Parameter param(tokens.at(index).getValue());
            pred.addParameter(param);
            match(TokenType::STRING);
            parseStringList(pred);
        } else {
            return;
        }
    }

    void parseFact() {
        Predicate pred(tokens.at(index).getValue());
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        Parameter param(tokens.at(index).getValue());
        pred.addParameter(param);
        match(TokenType::STRING);
        parseStringList(pred);
        match(TokenType::RIGHT_PAREN);
        match(TokenType::PERIOD);
        datalog.addFact(pred);
    }

    void parsePredicate(Predicate &pred) {
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        parseParameter(pred);
        parseParameterList(pred);
        match(TokenType::RIGHT_PAREN);
    }

    void parseParameter(Predicate &pred) {
        if (tokens.at(index).getType() == TokenType::STRING) {
            Parameter param(tokens.at(index).getValue());
            pred.addParameter(param);
            match(TokenType::STRING);
        } else {
            Parameter param(tokens.at(index).getValue());
            pred.addParameter(param);
            match(TokenType::ID);
        }
    }

    void parseParameterList(Predicate &pred) {
        if (tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            parseParameter(pred);
            parseParameterList(pred);
        } else {
            return;
        }
    }

    void parseHeadPredicate(Predicate &pred) {
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        Parameter param(tokens.at(index).getValue());
        pred.addParameter(param);
        match(TokenType::ID);
        parseIdList(pred);
        match(TokenType::RIGHT_PAREN);
    }

    void parsePredicateList(Rule &rule) {
        if (tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            Predicate pred(tokens.at(index).getValue());
            parsePredicate(pred);
            rule.addPredicate(pred);
            parsePredicateList(rule);
        } else {
            return;
        }
    }

    void parseRule() {
        Predicate pred(tokens.at(index).getValue());
        parseHeadPredicate(pred);
        Rule rule(pred);
        match(TokenType::COLON_DASH);
        pred.emptyPredicate();
        pred.setName(tokens.at(index).getValue());
        parsePredicate(pred);
        rule.addPredicate(pred);
        parsePredicateList(rule);
        match(TokenType::PERIOD);
        datalog.addRule(rule);
    }

    void parseQuery() {
        Predicate pred(tokens.at(index).getValue());
        parsePredicate(pred);
        match(TokenType::Q_MARK);
        datalog.addQuery(pred);
    }

    void parseSchemeList() {
        if (tokens.at(index).getType() != TokenType::FACTS) {
            parseScheme();
            parseSchemeList();
        } else {
            return;
        }

    }

    void parseFactList() {
        if (tokens.at(index).getType() != TokenType::RULES) {
            parseFact();
            parseFactList();
        } else {
            return;
        }
    }

    void parseRuleList() {
        if (tokens.at(index).getType() != TokenType::QUERIES) {
            parseRule();
            parseRuleList();
        } else {
            return;
        }
    }

    void parseQueryList() {
        if (tokens.at(index).getType() != TokenType::EOFILE) {
            parseQuery();
            parseQueryList();
        } else {
            return;
        }
    }

};
/*
(DONE) schemeList	->	scheme schemeList | lambda
(DONE) factList	->	fact factList | lambda
(DONE) ruleList	->	rule ruleList | lambda
(DONE) queryList	->	query queryList | lambda

(DONE) scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
(DONE) fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
(DONE) rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
(DONE) query	        ->      predicate Q_MARK

(DONE) headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
(DONE) predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

(DONE) predicateList	->	COMMA predicate predicateList | lambda
(DONE) parameterList	-> 	COMMA parameter parameterList | lambda
(DONE) stringList	-> 	COMMA STRING stringList | lambda
(DONE) idList  	-> 	COMMA ID idList | lambda

(DONE) parameter	->	STRING | ID

 */

#endif //LAB2_PARSER_H
