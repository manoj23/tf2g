/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include "ThunderbirdFilter.hpp"

ThunderbirdFilter::ThunderbirdFilter(const string& name, const bool enabled, const int type, 
                const Action& action, const string& actionValue, 
                const vector<Condition>& conditions) :
        name(name), enabled(enabled), type(type), 
        action(action), actionValue(actionValue), 
        conditions(conditions) { }

ostream& operator<<(ostream& os, const ThunderbirdFilter& filter)
{
        os << "name: " << filter.name << endl
                << "enabled: " << filter.enabled << endl
                << "type: " << filter.type << endl
                << "action: " << filter.action << endl
                << "actionValue: " << filter.actionValue << endl
                << "conditions: " << endl;

        for (const auto& condition: filter.conditions)
        {
                os << condition;
        }

        os << endl;

        return os;
}


