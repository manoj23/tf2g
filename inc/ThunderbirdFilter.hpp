/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include <iostream>
#include <string>
#include <vector>

#include "Condition.hpp"

using namespace std;

class ThunderbirdFilter {
public:
        ThunderbirdFilter(const string& name, const bool enabled, const int type, 
                        const Action& action, const string& actionValue, 
                        const vector<Condition>& conditions);

        friend ostream& operator<<(ostream& os, const ThunderbirdFilter& filter);

        string name;
        bool enabled;
        int type;
        Action action;
        string actionValue;
        vector<Condition> conditions;        
};


