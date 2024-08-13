//
// Created by jacob on 2/14/2022.
//

#ifndef LAB2_DATALOGPROGRAM_H
#define LAB2_DATALOGPROGRAM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram {
public:
    DatalogProgram() {}

    vector<Predicate> schemes;
    int numSchemes = 0;
    vector<Predicate> facts;
    int numFacts = 0;
    vector<Predicate> queries;
    int numQueries = 0;
    vector<Rule> rules;
    int numRules = 0;
    set<string> domain;
    int domainSize = 0;


    void addScheme(Predicate pred) {
        schemes.push_back(pred);
        numSchemes++;
    }

    void addFact(Predicate pred) {
        facts.push_back(pred);
        numFacts++;
        int predSize = pred.parameters.size();
        for (int i = 0; i < predSize; i++) {
            domain.insert(pred.parameters.at(i).getName());
        }
    }

    void addQuery(Predicate pred) {
        queries.push_back(pred);
        numQueries++;
    }

    void addRule(Rule rule) {
        rules.push_back(rule);
        numRules++;
    }

    void print() {
        stringstream outSS;
        domainSize = domain.size();
        set<string>::iterator itr;
        outSS << "Schemes(" << numSchemes << "):\n";
        for (int i = 0; i < numSchemes; i++) {
            outSS << "  " << schemes.at(i).toString() << endl;
        }
        outSS << "Facts(" << numFacts << "):\n";
        for (int i = 0; i < numFacts; i++) {
            outSS << "  " << facts.at(i).toString() << "." << endl;
        }
        outSS << "Rules(" << numRules << "):\n";
        for (int i = 0; i < numRules; i++) {
            outSS << "  " << rules.at(i).toString() << endl;
        }
        outSS << "Queries(" << numQueries << "):\n";
        for (int i = 0; i < numQueries; i++) {
            outSS << "  " << queries.at(i).toString() << "?" << endl;
        }
        outSS << "Domain(" << domainSize << "):" << endl;
        for (itr = domain.begin(); itr != domain.end(); itr++) {
            outSS << "  " << *itr << endl;
        }
        cout << outSS.str();
    }

};


#endif //LAB2_DATALOGPROGRAM_H
