//
// Created by jacob on 3/1/2022.
//

#ifndef LAB3_RELATION_H
#define LAB3_RELATION_H


#include "Tuple.h"
#include "Parser.h"
#include <set>

class Relation
{
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string &name, const Scheme &scheme) : name(name), scheme(scheme)
    {}

    Relation()
    {}

    int size() {
        return tuples.size();
    }

    const string &getName() const
    {
        return name;
    }

    void setName(const string &name)
    {
        Relation::name = name;
    }

    const Scheme &getScheme() const
    {
        return scheme;
    }

    void setScheme(const Scheme &scheme)
    {
        Relation::scheme = scheme;
    }

    bool addTuple(Tuple t) // if the tuple was not already in the set this returns true, otherwise false
    {
        return tuples.insert(t).second;
    }

    string toString()
    {
        //cout << "Relation toString" << endl;
        stringstream out;
        //cout << "Number of Tuples: " << tuples.size() << endl;
        for (Tuple t : tuples)
        {
            //cout << "Size of Tuple: " << t.size() << endl;
            //cout << "Size of Scheme: " << scheme.size() << endl;
            if (t.size() != 0)
                out << "  " << t.toString(scheme) << endl;
        }
        return out.str();
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }

    //Likely need to fix loops on this one.
    Relation selectCompare(int indexA, int indexB) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples) {
            //for (auto& tupleB : tuples) {
                if (tuple.at(indexA) == tuple.at(indexB))
                    result.addTuple(tuple);
            //}
        }
        return result;
    }

    Relation project(vector<int> &columns) {
        Relation result(name, scheme);
        Scheme newScheme;
        for(int i : columns) {
            newScheme.push_back(scheme.at(i));
        }
        result.setScheme(newScheme);
        for (auto& tuple : tuples) {
            Tuple newTuple;
            for (int i : columns) {
                newTuple.push_back(tuple.at(i));
            }
            result.addTuple(newTuple);
        }
        return result;
    }

    Relation rename(vector<string> attributes) {
        Relation result(name, scheme);
        Scheme newScheme;
        int numAttributes = attributes.size();
        for(int i = 0; i < numAttributes; i++) {
            newScheme.push_back(attributes.at(i));
        }
        result.setScheme(newScheme);
        for (auto& tuple : tuples)
                result.addTuple(tuple);
        return result;
    }

};



#endif //LAB3_RELATION_H
