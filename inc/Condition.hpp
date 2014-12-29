/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include "EnumeratedTypes.hpp"

using namespace std;

class Condition {
public:
        Condition(const LogicOperator& logicOperator, const Criteria& criteria, const Verb& verb, const string& value);
        friend ostream& operator<<(ostream& os, const Condition& condition);

        LogicOperator logicOperator;    
        Criteria criteria;
        Verb verb;
        string value;        
};

