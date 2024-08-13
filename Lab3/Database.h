//
// Created by jacob on 3/14/2022.
//

#ifndef LAB3_DATABASE_H
#define LAB3_DATABASE_H

#include "Relation.h"
#include "DatalogProgram.h"

using namespace std;

class Database {
private:
    vector<Relation> database;
public:
    Database() {}

    void addRelation(Relation relation) {
        database.push_back(relation);
    }

    Relation at(int i) {
        return database.at(i);
    }

    int size() {
        return database.size();
    }

    void print() {
        //cout << "Printing" << endl;
        int numRelations = database.size();
        //cout << numRelations << endl;
        for (int i = 0; i < numRelations; i++) {
            //cout << "Starting relation to string for relation " << i << endl;
            cout << database.at(i).toString() << endl;
        }
    }

};


#endif //LAB3_DATABASE_H
