/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include "ThunderbirdFilters.hpp"

using namespace std;

ThunderbirdFilters::ThunderbirdFilters(const string& filename)
{
        ifstream file(filename, ifstream::in);

        if (!file.good() || file.peek() == ifstream::traits_type::eof())
        {
                throw invalid_argument("File does not exist or is empty");
        }

        string line;
        string name, actionValue;
        Action action;
        bool enabled;
        int type;

        const regex regex_key_value("(version|logging|name|enabled|type|action|actionValue|condition)=\"(.*)\"");
        const regex regex_action("imap://manoj125%40gmail.com@imap.googlemail.com/(.*)");
        const regex regex_condition("(OR|AND) \\((from|to|cc|subject|junk status),(is|contains),([A-Za-z0-9.@-]+)\\) ?");

        while (getline(file, line))
        {
                smatch smatch;

                if (regex_search(line, smatch, regex_key_value))
                {
                        string key = smatch[1];
                        string value = smatch[2];

                        if (key == "version" || key == "logging") 
                                continue; 
                        else if (key == "name") 
                                name = value;  
                        else if (key == "enabled") 
                                enabled = (value == "yes") ? true : false;
                        else if (key == "type") 
                                type = stoi(value); 
                        else if (key == "action")
                                action.set(value);
                        else if (key == "actionValue")
                        {
                                switch (action.enumValue)
                                {
                                        case Action::Enum::MOVE:
                                                if (regex_search(value, smatch, regex_action))
                                                        actionValue = smatch[1];
                                                else
                                                        throw invalid_argument("Tag not found: " + line);
                                                break;
                                }
                        }
                        else if (key == "condition") 
                        {
                                match_results<string::const_iterator> smatch;
                                string::const_iterator start = line.begin();
                                vector<Condition> conditions;
                                while (regex_search(start, line.cend(), smatch,  regex_condition)) 
                                { 
                                        LogicOperator logicOperator(smatch[1]);
                                        Criteria criteria(smatch[2]);
                                        Verb verb(smatch[3]);
                                        string value = smatch[4];
                                        Condition condition(logicOperator, criteria, verb, value);
                                        conditions.push_back(condition);

                                        // Ignore the JUNK_STATUS filter
                                        if (criteria.enumValue != Criteria::Enum::JUNK_STATUS)
                                        {
                                                ThunderbirdFilter filter(name, enabled, type, action, actionValue, conditions);
                                                filters.push_back(filter);
                                        }

                                        start = smatch[0].second; 
                                }
                        }
                }
                else
                        throw invalid_argument("Unrecognized line: " + line);
        }

        file.close();
}

void ThunderbirdFilters::makeGmailFilters(const string& filename) const
{
        ofstream file(filename);

        file << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
        file << "<feed xmlns='http://www.w3.org/2005/Atom' xmlns:apps='http://schemas.google.com/apps/2006'>" << endl;
        file << "\t<title>Mail Filters</title>" << endl;
        file << "\t<id></id>" << endl;
        file << "\t<updated></updated>" << endl;
        file << "\t<author></author>" << endl;

        for (const auto& filter : filters)
        {
                file << "\t<entry>" << endl;
                file << "\t\t<category term='filter'></category>" << endl;
                file << "\t\t<title>Mail Filter</title>" << endl;
                file << "\t\t<id></id>" << endl;
                file << "\t\t<updated></updated>" << endl;
                file << "\t\t<content></content>" << endl;

                switch (filter.action.enumValue)
                {
                        case Action::Enum::MOVE:
                                string actionValue, condition;

                                if (filter.conditions.size() > 1 && 
                                    filter.conditions[0].logicOperator.enumValue == LogicOperator::Enum::OR)
                                {
                                        file << "\t\t<apps:property name='hasTheWord' value='";

                                        for (const auto& condition : filter.conditions)
                                        {
                                                switch (condition.criteria.enumValue)
                                                {
                                                        case Criteria::Enum::FROM:
                                                                file << "from";
                                                                break;
                                                        case Criteria::Enum::TO:
                                                                file << "to";
                                                                break;
                                                        case Criteria::Enum::CC:
                                                                file << "cc" ;
                                                                break;
                                                        case Criteria::Enum::SUBJECT:
                                                                file << "subject";
                                                                break;
                                                        case Criteria::Enum::JUNK_STATUS:
                                                                // Currently not supported
                                                                break;
                                                }
                                                // FIXME: Add " OR " only if it is the last element
                                                file << ":" + condition.value + " OR ";
                                                 
                                        }
                                        file << "'/>" << endl;
                                }
                                else
                                {
                                        for (const auto& condition : filter.conditions)
                                        {
                                                file << "\t\t<apps:property name='";

                                                switch (condition.criteria.enumValue)
                                                {
                                                        case Criteria::Enum::FROM:
                                                                file << "from";
                                                                break;
                                                        case Criteria::Enum::TO:
                                                                file << "to";
                                                                break;
                                                        case Criteria::Enum::CC:
                                                                file << "cc" ;
                                                                break;
                                                        case Criteria::Enum::SUBJECT:
                                                                file << "subject";
                                                                break;
                                                        case Criteria::Enum::JUNK_STATUS:
                                                                // Currently not supported
                                                                break;
                                                }

                                                file << "' value='" + condition.value + "'/>" << endl;
                                                 
                                        }
                                }
                                file << "\t\t<apps:property name='label' value='" + filter.actionValue + "'/>" << endl;
                                break;
                }

                file << "\t\t<apps:property name='sizeOperator' value='s_sl'/>" << endl;
                file << "\t\t<apps:property name='sizeUnit' value='s_smb'/>" << endl;
                file << "\t</entry>" << endl; 
        }

        file << "</feed>" << endl;

        file.close();
}

ostream& operator<<(ostream& os, const ThunderbirdFilters& thunderbirdFilters)
{
        for (const auto& filter : thunderbirdFilters.filters)
        {
                os << filter;
        }
 
        return os;
}

