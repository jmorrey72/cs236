//
// Created by jacob on 3/1/2022.
//

#ifndef LAB3_TUPLE_H
#define LAB3_TUPLE_H

#include <vector>
#include <string>
#include <sstream>

#include "Scheme.h"

using namespace std;
class Tuple
{
private:
    vector<string> values;
public:
    string at(unsigned int index) const {
        return values.at(index);
    }

    unsigned int size()
    {
        return values.size();
    }

    void push_back(string newAttribute)
    {
        values.push_back(newAttribute);
    }



    bool operator<(const Tuple &rhs) const
    {
        return this->values < rhs.values;
    }

    string toString(Scheme scheme)
    {
        //cout << "Tuple toString" << endl;

        stringstream out;


        if (scheme.size() != values.size()) {
            throw "Scheme and Tuple are of different sizes";
        }

        string sep = "";
        //cout << "before for loop" << endl;
        for (unsigned int i = 0; i < values.size(); i++)
        {
            out << sep << scheme.at(i) << "=" << values.at(i);
            sep = ", ";
        }


        return out.str();
    }

    Tuple(const vector<string> &values) : values(values)
    {}

    Tuple()
    {}
};


#endif //LAB3_TUPLE_H
