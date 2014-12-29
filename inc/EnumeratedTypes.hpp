/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Action {
public:
        Action();
        Action(const string& string);
        void set(const string& string);
        friend ostream& operator<<(ostream& os, const Action& action);

        enum class Enum {
                MOVE,
        };
        
        enum Enum enumValue;
};

class LogicOperator {
public:
        LogicOperator(const string& string);
        friend ostream& operator<<(ostream& os, const LogicOperator& logicOperator);
       
        enum class Enum {
                AND,
                OR,
        };

        enum Enum enumValue;
};


class Criteria {
public:
        Criteria(const string& string);
        friend ostream& operator<<(ostream& os, const Criteria& criteria);
       
        enum class Enum {
                FROM, 
                TO,
                CC,
                SUBJECT,
                JUNK_STATUS,
        };
 
        enum Enum enumValue;
};

class Verb {
public:
        Verb(const string& string);
        friend ostream& operator<<(ostream& os, const Verb& verb);
        
        enum class Enum {
                IS, 
                CONTAINS,
        };

        enum Enum enumValue;
};


