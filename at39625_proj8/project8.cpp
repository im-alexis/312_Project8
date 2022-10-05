//
// Created by Alexis Torres on 4/21/22.
//

/* Alexis Torres
 * EID: at39625
 * Project 8
 */



#include "project8.h"

using namespace std;

string blip_command_text = string ("text");
string blip_command_output = string("output");
string blip_command_set = string("set");
string blip_command_var = string("var");

varTable variableHolder; // this will hold all the variables
vector<string> expressionHolder;  //a vector to hold the expression

const int default_capacity = 1;



    variable::variable(string name) {
         this->varName = name;
         this->value = 0;
    }

    varTable::varTable(void) { // default constructor for the table
        this->capacity = default_capacity;
        this->data = new variable[this->capacity];
        this->length = 0;
    }
    bool varTable::isThere(string name) {
        int i;
        for(i = 0; i<length; i++){
            if(data[i].varName == name){
                return true;
            }
        }
        return false; // auto return false
    }
void varTable::addVar(string name){ //adds a variable to the table

    int i;
    variable *databasePlusOne = new variable[this->capacity+1];
    for(i = 0; i< length; i++){
        databasePlusOne[i] = data[i];
    }
    delete[] data;
    data = databasePlusOne;
    this->capacity++;
    this->data[length] = name;
    this->length++;

    }

variable& varTable::find(string name) { // finds element
    int i;
    for (i = 0; i < length; i++) {
        if (data[i].varName == name) {
            variable& holder = data[i];
            return holder;
        }
    }

}

variable& varTable::end() { //gets the last variable in the table
        variable& holder = data [length - 1];
        return holder;
    }

    variable& varTable::operator[](string name) { //like from customer but for the variables
        int i;
        if(!isThere(name)){
            variable *databasePlusOne = new variable[this->capacity+1];
            for(i = 0; i< length; i++){
                databasePlusOne[i] = data[i];
            }
            delete[] data;
            data = databasePlusOne;
            this->capacity++;
            this->data[length] = name;
            this->length++;
            variable &custHolder = data[length-1];
            return custHolder;
        }

        for (i = 0; i < length; i++) {
            if (data[i].varName == name) {
                variable &custHolder = data[i];
                return custHolder;
            }
        }
    }

    varTable::~varTable(void) {
        delete[] this->data;
    }

void exprVectorAdder() {
    string looker;
    do  {
        read_next_token();   //get next token
        string firstOp = string(next_token());
        looker = firstOp;
        looker = string(next_token());
        if (firstOp == "//") { skip_line(); }
        expressionHolder.push_back(firstOp); // adds the read token to the expression vector
        if (peek_next_token() == blip_command_text || peek_next_token() == blip_command_output || peek_next_token() == blip_command_var ||peek_next_token() == blip_command_set){
            return; // if the next thing going to be read is a command then leave.
        }
    }
    while( next_token_type != END && looker != blip_command_text && looker != blip_command_output && looker != blip_command_var && looker != blip_command_output);
}

int operate(const string op, int val1, int val2 ){ //every operation there
    if (op == ">"){   return (val1 > val2);}
    else if (op == "<"){  return (val1 < val2);}
    else if (op == ">="){ return (val1 >= val2);}
    else if (op == "<="){ return (val1 <= val2);}
    else if (op == "=="){ return (val1 == val2);}
    else if (op == "!="){ return (val1 != val2);}
    else if (op == "+"){ return (val1 + val2);}
    else if (op  == "-"){ return (val1 - val2);}
    else if (op == "*"){ return (val1 * val2);}
    else if (op == "/"){ return (val1 / val2);}
    else if (op == "&&"){ return (val1 && val2);}
    else if (op == "||"){ return (val1 || val2);}
    else if (op == "%"){ return (val1 % val2);}
    }

int evaluatePolish (vector<string>& expression){
    string firstElm = expression.front();   //gets the first elemnt in the vector
   if (variableHolder.isThere(expressionHolder.front())){ // if a variable name is passed through then return the value of the variable
        int value = variableHolder[firstElm].value;
        expression.erase(expression.begin()); //get rid of it and move on to the next element in the vector
        return value;
    }else if (firstElm != ">" && firstElm != "<" && firstElm != ">=" && firstElm != "<=" && firstElm != "==" &&
            firstElm != "!=" && firstElm != "+" && firstElm != "-" && firstElm != "*" && firstElm != "/" &&
            firstElm != "%" && firstElm != "&&" && firstElm != "||"  && firstElm != "!"
                && firstElm != "~" && !variableHolder.isThere(firstElm)){ // if its not an operator and not a variable then it is a number
        expression.erase(expression.begin());
        return stoi(firstElm);//change to integer
    } else if (firstElm == "~" ){ // negative number
        expression.erase(expression.begin());
        int polishExpr = evaluatePolish(expression);
        polishExpr *= -1;
        return polishExpr;
    } else if (firstElm != "!"){
        expression.erase(expression.begin());
        int sideA = evaluatePolish(expression);
        int sideB = evaluatePolish(expression);
        return operate(firstElm, sideA, sideB);
    } else if(firstElm == "!"){ // not (logic)
        expression.erase(expression.begin());
        int polishExpr = evaluatePolish(expression);

        if (polishExpr != 0){
            return false;

        } else if (polishExpr == 0){
            return true;    //in this case it will be zero so return true
        }
    }
}
void isText(){ // function to output text
    string holder = string(next_token());
    read_next_token();
    string text1 = string(next_token()); // since no calculations are needed then you can just output
    cout << text1;

}

void isOutput(){
    string holder = string(next_token());
    exprVectorAdder(); // this adds the expression to the vector to evaluate
    cout << evaluatePolish(expressionHolder);
    expressionHolder.clear(); // gets rid of everything in the vector

}

void isVariable(){
    string holder = string(next_token());
    read_next_token();
    string nameOFVariable = string(next_token());
    if (variableHolder.isThere(nameOFVariable)){
        cout << "variable " << nameOFVariable << " incorrectly re-initialized" << endl;
    }
    exprVectorAdder();
    variableHolder[nameOFVariable].value = evaluatePolish(expressionHolder);

}

void isSet(){
    string holder = string(next_token()); //
    read_next_token();
    string nameOFVariable = string(next_token()); // this will be the name of the variable
    if (!variableHolder.isThere(nameOFVariable)){
        cout << "variable " << nameOFVariable << " not declared" << endl;
        exprVectorAdder(); // add to the vector
        variableHolder[nameOFVariable].value = evaluatePolish(expressionHolder); // this will create a new variable and assign the expression to it
        return; // once you reach here youre done and can leave
    }
    exprVectorAdder();
    variableHolder[nameOFVariable].value = evaluatePolish(expressionHolder);
}

void doStuff(){
        varTable variableHolder;
    for (; next_token_type != END; read_next_token()) {
        string token = string(next_token());
        if (token == blip_command_text) {
            isText();
        } else if (token == blip_command_output) {
            isOutput();
        } else if (token == blip_command_set) {
            isSet();
        } else if (token == blip_command_var) {
            isVariable();
        } else if (token == "//") {
            skip_line();
        }

    }
    return;
}
int main(void){
//    set_input("test1.blip");
//    set_input("test2.blip");
//    set_input("test3.blip");
//    set_input("test4.blip");
//   set_input("test1.txt");
    set_input("test_grader.blip");
    doStuff();

    return 0;
}


