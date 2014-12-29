/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include "EnumeratedTypes.hpp"

using namespace std;

Action::Action()
{

}

Action::Action(const string& string)
{
        if (string == "Move to folder")
                enumValue = Action::Enum::MOVE;
        else
                throw invalid_argument("Unrecognized action: " + string);
} 

void Action::set(const string& string)
{
        if (string == "Move to folder")
                enumValue = Action::Enum::MOVE;
        else
                throw invalid_argument("Unrecognized action: " + string);
} 

ostream& operator<<(ostream& os, const Action& action)
{
        switch (action.enumValue)
        {
                case Action::Enum::MOVE:
                        os << "Move to folder";
                        break;
        }
        return os;
}

LogicOperator::LogicOperator(const string& string)
{
        if (string == "OR")
                enumValue = LogicOperator::Enum::OR;
        else if (string == "AND")
                enumValue = LogicOperator::Enum::AND;
        else
                throw invalid_argument("Unrecognized logicOperator: " + string);
} 

ostream& operator<<(ostream& os, const LogicOperator& logicOperator)
{
        switch (logicOperator.enumValue)
        {
                case LogicOperator::Enum::AND:
                        os << "AND";
                        break;
                case LogicOperator::Enum::OR:
                        os << "OR";
                        break;
        }

        return os;
}

Verb::Verb(const string& string)
{
        if (string == "is")
                enumValue = Verb::Enum::IS;
        else if (string == "contains")
                enumValue = Verb::Enum::CONTAINS;
        else
                throw invalid_argument("Unrecognized Verb: " + string);
} 

ostream& operator<<(ostream& os, const Verb& verb)
{
        switch (verb.enumValue)
        {
                case Verb::Enum::IS:
                        os << "In: ";
                        break;
                case Verb::Enum::CONTAINS:
                        os << "Contains: ";
                        break;
        }

        return os;
}

Criteria::Criteria(const string& string)
{
        if (string == "from")
                enumValue = Criteria::Enum::FROM;
        else if (string == "to")
                enumValue = Criteria::Enum::TO;
        else if (string == "cc")
                enumValue = Criteria::Enum::CC;
        else if (string == "subject") 
                enumValue = Criteria::Enum::SUBJECT;
        else if (string == "junk status")
                enumValue = Criteria::Enum::JUNK_STATUS;
        else
                throw invalid_argument("Unrecognized criteria: " + string);

} 

ostream& operator<<(ostream& os, const Criteria& criteria)
{
        switch (criteria.enumValue)
        {
                case Criteria::Enum::FROM:
                        os << "From: ";
                        break;
                case Criteria::Enum::TO:
                        os << "To: ";
                        break;
                case Criteria::Enum::CC:
                        os << "Cc: ";
                        break;
                case Criteria::Enum::SUBJECT:
                        os << "Subject: ";
                        break;
                case Criteria::Enum::JUNK_STATUS:
                        os << "Junk status: ";
                        break;
        }

        return os;
}

