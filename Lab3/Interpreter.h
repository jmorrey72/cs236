//
// Created by jacob on 3/16/2022.
//

#ifndef LAB3_INTERPRETER_H
#define LAB3_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"


using namespace std;

class Interpreter {
private:
    Database database;
    DatalogProgram datalog;
public:
    Interpreter(const DatalogProgram &datalog) : datalog(datalog) {}

    void generateDatabase() {
        //cout << "Creating Database" << endl;
        //cout << "numSchemes = " << datalog.numSchemes << endl;

        for (int j = 0; j < datalog.numSchemes; j++) {
            //cout << "Starting Scheme : " << j << endl;
            Relation relation;
            Scheme attributes;
            relation.setName(datalog.getSchemeName(j));
            int numParams = datalog.schemes.at(j).parameters.size();
            for (int i = 0; i < numParams; i++) {
                attributes.push_back(datalog.schemes.at(j).parameters.at(i).getName());
            }
            relation.setScheme(attributes);
            for (int i = 0; i < datalog.numFacts; i++) {
                if (datalog.getSchemeName(j) == datalog.facts.at(i).getName()) {
                    Tuple values;
                    int numParams = datalog.facts.at(i).parameters.size();
                    for (int k = 0; k < numParams; k++) {
                        values.push_back(datalog.facts.at(i).parameters.at(k).getName());
                    }
                    relation.addTuple(values);
                }
            }
            database.addRelation(relation);
        }
    }

    void evaluate() {
        //cout << "Database Created" << endl;
        Database finishedDB;
        //cout << "NumQueries: " << datalog.numQueries << endl;
        for (int i = 0; i < datalog.numQueries; i++) {
            Relation answer;
            vector<string> variables;
            vector<int> columns;
            vector<string> attributes;
            variables.clear();
            bool areThereVariables = false;
            for (int j = 0; j < datalog.numSchemes; j++) {
                if (datalog.queries.at(i).getName() == database.at(j).getName()) {
                    //cout << "Match at " << i << " , " << j << endl;
                    answer = database.at(j);
                    int numTuples = datalog.queries.at(i).parameters.size();
                    //cout << "Parameters in Scheme: " << numTuples << endl;
                    for (int k = 0; k < numTuples; k++) {
                        //cout << "( " << i << " , " << k << " )" << endl;
                        //cout << datalog.queries.at(i).parameters.at(k).getName() << ", ";
                        Scanner s = Scanner(datalog.queries.at(i).parameters.at(k).getName() + " ");
                        Token t = s.scanToken();
                        //cout << t.toString() << endl;
                        if (t.getType() == TokenType::STRING) {
                            answer = answer.select(k, datalog.queries.at(i).parameters.at(k).getName());
                            variables.emplace_back();
                        }
                        else {
                            string var = datalog.queries.at(i).parameters.at(k).getName();
                            //bool multipleVar = false;
                            areThereVariables = true;
                            //columns.push_back(k);
                            //attributes.push_back(var);
                            //cout << "Number of Columns: " << columns.size() << endl;
                            //cout << "Number of Attributes: " << attributes.size() << endl;
                            int numVars = variables.size();
                            for (int n = 0; n < numVars; n++) {
                                if ((variables.at(n) == var) && (var != "")) {
                                    answer = answer.selectCompare(n, k);
                                    var = "";
                                    //multipleVar = true;
                                    //cout << answer.toString() << endl;
                                    //attributes.pop_back();
                                    //columns.pop_back();
                                }
                            }
                            /*if (multipleVar) {
                                columns.pop_back();
                                attributes.pop_back();
                            }*/
                            variables.push_back(var);
                        }
                    }
                }
            }
            //cout << "Starting to print" << endl;
            finishedDB.addRelation(answer);
            cout << datalog.queries.at(i).toString() << "? ";
            if (answer.size() == 0) {
                cout << "No" << endl;
            } else {
                cout << "Yes(" << answer.size() << ")" << endl;
                if (areThereVariables) {
                    int varSize = variables.size();
                    for (int j = 0; j < varSize; j++) {
                        if (!variables.at(j).empty()) {
                            columns.push_back(j);
                            attributes.push_back(variables.at(j));
                        }
                    }

                    answer = answer.project(columns);
                    answer = answer.rename(attributes);
                    cout << answer.toString();
                }
            }

        }
        //finishedDB.print();

        /*for (int i = 0; i < finishedDB.size(); i++) {
            cout << datalog.queries.at(i).toString() << "? ";
            if (finishedDB.at(i).size() == 0) {
                cout << "No" << endl;
            } else {
                cout << "Yes(" << finishedDB.at(i).size() << ")" << endl;
            }
        }*/
    }

    void printDatabase() {
        database.print();
    }

};

#endif //LAB3_INTERPRETER_H
