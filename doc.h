/*
* File:   main.h
* Author: Alex
*
* Created on October 15, 2015, 8:25 PM
 * * last edited 10/11 @ 1:22 PM
*/

#ifndef MAIN_H
#define	MAIN_H

#include "element.h"
using namespace std;

string getOpen(string line); //get the name of the opening tag
string getClosed(string line); //get the name of the closing tag
void displayOutput(vector<element> elementVec);
void RunProg(string fileName); //the workhorse of the program, orgranizes all the utilities to complete the task
void getAttr(string line, element* tag);
void printOpenElement(element tag); //prints the info on an opening tag
void printClosedElement(element tag); //prints the info on a closing tag
void printCompleteElement(string line, int lineNumber); //print the complete tag
void printStack(stack<element> songstack); //prints the contents of the stack without modifying the original
void printMap(map<string, string>attrMap);
bool checkChild(vector<element*> temp, element tag);


#endif	/* MAIN_H */

