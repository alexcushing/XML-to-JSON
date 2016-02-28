/*
* File:   element.cpp
* Author: Alex Cushing
* Alexander_Cushing@student.uml.edu
* Copyright (c) UMass Lowell 2015
* Created on September 15, 2015, 4:31 PM
******USING TYLER BAINBRIDGES CODE FROM ASSIGNMENT 3******
* last edited 10/11 @ 1:22 PM
*/
#include "element.h"
using namespace std;
/**
*
* @param child pushes the child on
 * 
 * adds a child
*/
void element::addChild(element* child)
{
	children.push_back(child);
}
/**
*
* @return returns the vector children
 * 
 * returns the vector children
*/
vector<element*> element::getVector(void)
{
	return children;
}
/**
*
* @return returns the size of the amount of children
 * 
 * returns the size of the child
*/
int element::getChildSize(void)
{
	return children.size();
}

/**
*
* @return returns what level in (tabbed) in the xml file
* you currently are in so that it is marked later with "." in
* print everything
 * gets the level of the current location in the file
*/
int element::getLevel()
{
	return level;
}
/**
*
* @param finalTag - gives the element name
* @param level - sets the current elements tab amount, otherwise "level"
* @param lineNumber - returns the tags line number
 * 
 * makes an element with those features
*/
element::element(string finalTag, int level, int lineNumber)
{
	this->elementName = finalTag; //setting the name
	this->lineNum = lineNumber; //setting the line number
	this->level = level;
}
/**
*
* @param attribute - the map of string keys and strings for each element with an attribute
 * sets a new map of attributes
*/
void element::setAttr(map<string, string>attribute){
	this->attribute = attribute;
}

/**
*
* @param finalTag - makes an element with a tag
* @param level -  makes an element with the level (tab amount)
* @param lineNumber -  makes an element with the correct line number
* @param attribute -  makes the element\creates an element with the name, number, level, and attributes
*/
element::element(string finalTag, int level, int lineNumber, map<string, string>attribute)
{
	this->elementName = finalTag; //setting the name
	this->lineNum = lineNumber; //setting the line number
	this->level = level;
	this->attribute = attribute;
}

/**
* @param finalTag - sets the name
* @param lineNumber - sets the line number
 * creates element
*/
element::element(string finalTag, int lineNumber)
{
	this->elementName = finalTag; //setting the name
	this->lineNum = lineNumber; //setting the line number
}
/**
*
* @return - element name for printing info in main
 * gets the name of the element
*/
string element::getName(){
	return elementName;
}
/**
 * this function gets the atribute name and returns it
 * @return returns the attribute name
 */
string element ::returnAttribute(){
	string hold = "";
	map<string, string>::iterator it;
	for (it = attribute.begin(); it != attribute.end(); ++it){
		return it->second;
	}
}
/*
*
* @return - returns the line number for printing
 * this gets the line number of the element
*/
int element::getlineNum(){
	return lineNum;
}
/**
 * returns the amount of attributes
 * @return the attribute count
 */
int element::getAttrCount(){
	return attrCount;
}
/**
 * this sets the amount of attributes
 * @param c this is the count of attributes
 */
void element::addAttrCount(int c){
	attrCount = c;
}

/**
*this sets the content between the < and the >
* @param line - gets the content in between the tags and creates an element
*/
void element::setContent(string line) //sets the content
{
	int startPos, endPos; //start and end position of line substr
	string elementContent; //after editing line

	startPos = line.find(">");
	endPos = line.find("<", startPos + 1); //getting what's between the tags aka Content
	elementContent = line.substr(startPos + 1, (endPos - startPos) - 1); //getting content

	content = elementContent; //content being set
}


/**
* Test an element to see if it has content.
* @return true if the element has content, or false if it does not.
*/
bool element::hasContent(void) {
	return (!content.empty());
}

/**
*checks if their are attributes
* @return - returns true or false of there is an attribute
*/
bool element::hasAtr(void){
	return (!attribute.empty()); //if attribute map isn't empty a/k/a there is a map
}

/**
*gets the content
* @return returns the content string
*/
string element::getContent(void) //returns the content string
{
	return content; //the content
}
/**
*gets the attributes
* @return - returns the attribute map
*/
map<string, string> element::getAttr(void){
	return attribute;
}
/**
*adds an attribute
* @param x - the key (or the attribute) string passed in
* @param y - the other half of the map that is the definition
*/
void element::addAttr(string x, string y){
	attribute.insert(pair<string, string>(x, y));
}
/**
 * 
* prints the attributes
*/
void element::printAttributes(){
	map<string, string>::iterator itr;
	for (itr = attribute.begin(); itr != attribute.end(); ++itr){
		cout << "\tATTRIBUTE: "<<itr->first << endl << "\tVALUE: " << itr->second << endl;
	}
}
/**
 * this prints the attributes and rest of the XML that is in the map into the JSON file
 * @param inFile this is for printing straight to output.json
 * @param test this is to know whether the next line is an attribute for the same parent
 */
void element::printJSON(ofstream& inFile, bool test)
{
	map<string, string>::iterator it;
	for (it = attribute.begin(); it != attribute.end(); ++it ) // iterates through the map
	{

		if (it == attribute.begin()&& test == false){
			inFile << ",{" << endl;
		}
		else{
			inFile << "{" << endl;
		}
		inFile << "\"" << it->first << "\": " << "\"" << it->second << "," << endl;
		if (!content.empty()){
			inFile << "\"content\": " << "\"" << content << "\"" << endl;
		}
		inFile << "}" << endl;
	}
}