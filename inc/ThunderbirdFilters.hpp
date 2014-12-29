/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <stdexcept>
#include <vector>

#include "ThunderbirdFilter.hpp"

using namespace std;

class ThunderbirdFilters {
public:
        ThunderbirdFilters(const string& filename);
        void makeGmailFilters(const string& filename) const;
        friend ostream& operator<<(ostream& os, const ThunderbirdFilters& thunderbirdFilters);

private:
        vector<ThunderbirdFilter> filters;
};


