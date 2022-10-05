//
// Created by Alexis Torres on 4/30/22.
//
/* Alexis Torres
 * EID: at39625
 * Project 8
 */

#ifndef INPUT_CPP_INPUT_H
#define INPUT_CPP_INPUT_H


void set_input(const char* file_name);

void skip_line(void);

static bool IS_NUMBER(char c);
static bool IS_LETTER(char c);
static bool IS_SPACE(char c);

void read_next_token(void);
const char* next_token(void);
const char* peek_next_token(void);




#endif //INPUT_CPP_INPUT_H
