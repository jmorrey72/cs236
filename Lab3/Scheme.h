//
// Created by jacob on 2/28/2022.
//

#ifndef LAB3_SCHEME_H
#define LAB3_SCHEME_H

#include <vector>
#include <string>

using namespace std;

class Scheme
{
private:
    vector<string> attributes;
public:
    string at(unsigned int index)
    {
        return attributes.at(index);
    }

    unsigned int size()
    {
        return attributes.size();
    }

    void push_back(string newAttribute)
    {
        attributes.push_back(newAttribute);
    }

    bool operator<(const Scheme& s)
    {
        return this->attributes < s.attributes;
    }

    Scheme(const vector<string> &attributes) : attributes(attributes)
    {}

    Scheme()
    {}
};


#endif //LAB3_SCHEME_H
