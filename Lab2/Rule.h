//
// Created by jacob on 2/14/2022.
//

#ifndef LAB2_RULE_H
#define LAB2_RULE_H

#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"
#include "Predicate.h"

using namespace std;

class Rule {
public:

    Rule(const Predicate &headPredicate) : headPredicate(headPredicate) {}

    Predicate headPredicate;
    vector<Predicate> predicateList;

    void setHeadPredicate(Predicate &headPred) {
        headPredicate = headPred;
    }

    Predicate getHeadPredicate() {
        return headPredicate;
    }

    void addPredicate(Predicate &pred) {
        predicateList.push_back(pred);
    }

    string toString() {
        int numPredicates = predicateList.size();
        stringstream outSS;
        outSS << headPredicate.toString() << " :- " << predicateList.at(0).toString();
        for (int i = 1; i < numPredicates; i++) {
            outSS << "," << predicateList.at(i).toString();
        }
        outSS << ".";
        return outSS.str();
    }
};


#endif //LAB2_RULE_H
