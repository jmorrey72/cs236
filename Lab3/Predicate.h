//
// Created by walte on 1/26/2022.
//

#ifndef CS235WINTER2022_PREDICATE_H
#define CS235WINTER2022_PREDICATE_H

#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

using namespace std;
//SNAP(S, N, A, P)
class Predicate
{
public:
    Predicate(const string &name) : name(name) {}

    string name;

    vector<Parameter> parameters = {};

    void addParameter(Parameter param) {
        parameters.push_back(param);
    }

    void emptyPredicate() {
        name = "";
        parameters.erase(parameters.begin(),parameters.end());
    }

    void setName(string newName) {
        name = newName;
    }

    string getName() {
        return name;
    }

    string toString() {
        int numParams = parameters.size();
        stringstream outSS;
        outSS << name << "(";
        for (int i = 0; i < (numParams - 1); i++) {
            outSS << parameters.at(i).getName() << ",";
        }
        outSS << parameters.at(parameters.size() - 1).getName() << ")";
        return outSS.str();
    }
};


#endif //CS235WINTER2022_PREDICATE_H
