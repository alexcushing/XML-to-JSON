/*
* File:   element.h
* Author: Alex Cushing
* Alexander_Cushing@student.uml.edu
* Copyright (c) UMass Lowell 2015
* Created on September 15, 2015, 4:31 PM
* last edited 10/11 @ 1:22 PM
*/
#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include <stack>
#include <iomanip>

using namespace std;

class element{
public:
	element();
	element(string finalTag, int lineNumber); //creates a new element
	element(string finalTag, int level, int lineNumber);//for level
	element(string finalTag, int level, int lineNumber, map<string, string>attribute);//creates an element with a map
	int getAttrCount();//returns the amount of attributes
	void addAttrCount(int c);//this counts the amount of attrivutes
	int getLevel();//returns the current level of the line
	string getName(); //returns element name
	string returnAttribute();//this returns the attribute string
	int getlineNum(); //returns the line number
	void addChild(element* child);//this adds a child
	int getChildSize(void);//this gets the size of the urrent child
	vector<element*> getVector(void);//this returnns the element vector
	bool hasAtr(void);//this checks whether there are attributes
	void setContent(string line); //for complete elements where content is available
	bool hasContent(void); //checking if there is content
	string getContent(void); //returns the content string
	map<string, string> getAttr(void);//gets the attributes map
	void setAttr(map<string, string>attribute);//sets the attributes
	void addAttr(string x, string y);//adds an atttribute to the map
	void printAttributes();//prints the attribute to the screen
	void printJSON(ofstream& inFile, bool test);//prints out the JSON form

private:
	int attrCount;//the ammount of attributes
	string content;//content
	string elementName; //name of the tag
	int level;//level of line
	int lineNum; //line number its found on
	vector<element*> children; //points to the children
	string att;//attribute string
	map<string, string>attribute;//map of attributes
};

#endif

