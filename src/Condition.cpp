/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include "Condition.hpp"

using namespace std;

Condition::Condition(const LogicOperator& logicOperator, const Criteria& criteria, const Verb& verb, const string& value) :
        logicOperator(logicOperator), criteria(criteria), verb(verb), value(value) { }

ostream& operator<<(ostream& os, const Condition& condition)
{
        os << condition.logicOperator << ": " 
                << condition.criteria 
                << condition.verb 
                << condition.value << endl;

        return os;
}

