//
// Created by jacob on 2/14/2022.
//

#ifndef LAB2_PARAMETER_H
#define LAB2_PARAMETER_H

#include <string>

using namespace std;

class Parameter {
public:
    Parameter(const string &name) : name(name) {}

    string name;

    string getName() {
        return name;
    }
};


#endif //LAB2_PARAMETER_H
