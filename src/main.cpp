/*
 * © 2014 Georges Savoundararadj 
 *
 * SPDX-License-Identifier: MIT
 */
#include <iostream>
#include <string>
#include <stdexcept>

#include "ThunderbirdFilters.hpp"
 
using namespace std;

int main(int argc, char *argv[])
{
        if (argc != 2)
        {
                cout << "Execute ./tf2g [thunderbird filter file]" << endl;
        }
        else
        {
                const string thunderbirdFiltersFilename = argv[1];
                const string gmailFiltersFilename = thunderbirdFiltersFilename + ".gmail.xml";
                try 
                {
                        const ThunderbirdFilters thunderbirdFilters(thunderbirdFiltersFilename);

                        thunderbirdFilters.makeGmailFilters(gmailFiltersFilename);

                        cout << "Check " << gmailFiltersFilename << ". Bye, Bye!" << endl; 
                }
                catch (const invalid_argument& ia)
                {
                        cerr << "Invalid argument: " << ia.what() << endl;
                }
        } 

        return 0;
}
