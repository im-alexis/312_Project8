//
// Created by Alexis Torres on 4/21/22.
//
/* Alexis Torres
 * EID: at39625
 * Project 8
 */

#ifndef UTSTRING_H_PROJECT8_H
#define UTSTRING_H_PROJECT8_H

#include <iostream>
#include <string>
#include <vector>
#include "Parse.h"
//#include "Input.h"
using namespace std;


struct variable{
    string varName;
    int value;
    variable(string name) ;
    variable(void) { varName = "__invalid__"; }

};

class varTable {
public:
    variable* data;
    int capacity;
    int length;
    varTable(void);
    void addVar (string name);
    bool isThere(string name);
    variable& operator[](string name) ;
    variable& find(string name);
    variable& end();

    ~varTable(void) ;

};

int operate(const string op, int val1, int val2 );
void exprVectorAdder();
int evaluatePolish (vector<string>& expression);


void isText();
void isOutput();
void isVariable();
void isSet();

void doStuff();







#endif //UTSTRING_H_PROJECT8_H
