/*
* File:   main.cpp
* Author: Alex Cushing
* Alexander_Cushing@student.uml.edu
* Copyright (c) UMass Lowell 2015
* Created on September 15, 2015, 4:31 PM
* last edited 10/11 @ 1:22 PM
*/
#include "element.h"
#include "doc.h"
using namespace std;
/**
*
* @param line - takes in the full line and truncates it to just the attribute and definition
* @param tag- so that it can be printed with the tags
 * this function singles out the specific needed attributes on
 * their lines seperately
*/
void getTheAtrr(string line, element* tag)
{
	int startPos, endPos, attrStartPos, attrEndPos, valueStartPos, valueEndPos = 0, c = 0;
	string insideBrackets, attribute, value;

	startPos = line.find("<");
	endPos = line.find(">", startPos + 1);
	insideBrackets = line.substr(startPos + 1, (endPos - startPos) - 1); //leaves tag out of brackets

	while (insideBrackets.find('=', valueEndPos) != string::npos){ //locates = to identify ALL the attributes and values
		attrStartPos = insideBrackets.find(' ', valueEndPos); // starts at space
		attrEndPos = insideBrackets.find("=", attrStartPos); //ends at the =
		attribute = insideBrackets.substr(attrStartPos + 1, (attrEndPos - attrStartPos) - 1);//truncate to just the attribute
		valueStartPos = attrEndPos + 1;  //value start position after the attribute
		if (insideBrackets.find(' ', attrEndPos) != string::npos) //End at the space
		{
			valueEndPos = insideBrackets.find(' ', attrEndPos);
			value = insideBrackets.substr(valueStartPos + 1, ((valueEndPos)-valueStartPos) - 1);
		}
		else //Or end at bracket
		{
			valueEndPos = insideBrackets.find('\"', valueStartPos); //looks for the last 
			value = insideBrackets.substr(valueStartPos + 1, (valueEndPos - valueStartPos) - 1);
		}
		tag->addAttr(attribute, value);
		if (c != 0)
		{
			tag->addAttrCount(c);
		}
	}

}
/*

*/
/**
*
* @param fileName - passes in the xml file to read
 * *runs through the open file
*and calls specific functions
*in order to sort and output
*the program as assigned
*/
void RunProg(string fileName)
{
	ifstream inFile(fileName.c_str()); //setting the filename
	string line, finalTag, initialTag; //strings for different stages of the parsing stages
	element* tag; //element pointer for creating new elements
	element* closeTag; //for closing elements
	stack<element> songstack; //stack for opening tags
	vector<element> elementTree;
	int startPos = 0, endPos = 1, lineNumber = 1;
	string tagname;//for complete elements

	while (getline(inFile, line))
	{
		if (line.at(0) == '<' && line.at(1) == '?')
		{
			//cout << lineNumber << "    " << getOpen(line) << " is an attribute, not an open tag." << endl;
		}

		if (line.find("<!--") != string::npos) //looking for comments
		{
			//cout << lineNumber << "    Starting comment: " << line << endl; //shows the first part of the comment
			lineNumber++;
			getline(inFile, line); //gets next line
			while (line.find("-->") == string::npos) //searching for the end of the comment
			{
				lineNumber++;
				//cout << lineNumber << "    Comment: " << line << endl;
				getline(inFile, line); //gets next line
			}
			//cout << lineNumber << "    Ending comment: " << line << endl << endl;
			getline(inFile, line); //gets next line
			lineNumber++; //counts the line again
		}

		/*
		COMPLETE ELEMENTS
		*/

		if (line.at((line.find("<")) + 1) != '/') //if it is not a closing tag, then proceed to see if its closed inline
		{
			int backSlash = line.find('/'); //checks if there is a slash to then see if it is a closing tag
			if (backSlash != string::npos&&line.at(backSlash - 1) == '<') //checking for complete elements
			{
				tag = new element(getOpen(line), songstack.size(), lineNumber);
				if (tag->getLevel() > (songstack.top().getLevel())) //if the level is less then the one currently at the top of the stack, add to top of vec
				{
					tag->setContent(line); //setting the content between the tags
					getTheAtrr(line, tag);
					songstack.top().addChild(tag);
				}
				//printCompleteElement(line, lineNumber); //prints the full line, and the content between tags
			}
		}

		/*
		OPEN ELEMENTS
		*/

		if (line.at((line.find("<")) + 1) != '/'&&!ispunct(line.at((line.find("<")) + 1)) && line.at((line.find(">")) - 1) != '/') //if the character proceeding the opening bracket is not a backslash or punct (to get rid of closing tags and other tags) and there is no slash before the closing tags(self closing)
		{
			tag = new element(getOpen(line), songstack.size(), lineNumber); //creates a new Element with the line number and 

			int backSlash = line.find('/'); //checks if there is a slash to then see if it is a closing tag

			if (backSlash != string::npos&&line.at(backSlash - 1) != '<') //safeguard for tags that have forward slashes but are not for closing tags
			{
				getTheAtrr(line, tag);
				songstack.push(*tag); //pushes the tag onto the stack
			}

			if (backSlash == string::npos)//if there is no slash aka it is an open tag
			{
				getTheAtrr(line, tag);
				songstack.push(*tag);
			}


			//song.push_back(*tag); //adds onto a vector
		}
		else if (line.at((line.find("<")) + 1) != '/'&&ispunct(line.at((line.find("<")) + 1))) //xml
		{
			cout << "";
		}
		else if (line.at((line.find("<")) + 1) != '/'&&!ispunct(line.at((line.find("<")) + 1)) && line.at((line.find(">")) - 1) == '/') //self closing tags
		{
			cout << "";
		}

		if (line.at((line.find("<")) + 1) == '/') //if the character proceeding the opening bracket is a backslash (to find closing tags)
		{


			closeTag = new element(getClosed(line), songstack.size(), lineNumber); //creates a new Element with the line number and tagName
			if (songstack.top().getName() == closeTag->getName()){
				//checks if the top of the stack is equal to the closing tag found first
				//printClosedElement(*tag); //prints info



				if (!songstack.empty()) // if songstack isn't empty
				{
					if (!checkChild(songstack.top().getVector(), *tag)) //if tag is not in the songstack's child vector
					{
						songstack.top().addChild(tag); //add the child
					}
				}
				elementTree.push_back(songstack.top()); //pushing the elements on the vector for printing and organizing
				songstack.pop(); //pops the stack

			}

		}

		lineNumber++; //counting lines
	}
	displayOutput(elementTree); //printing in an organized way
}


/*
*Prints just open elements to screen
*/
/**
*
* @param tag - tag is an open element that this
* prints to the screen
 * this function is for printing the open elements
 * 
 * 
*/
void printOpenElement(element tag)
{
	int nameWidth = 30; //width of the name
	int numWidth = 5; //width of the number
	char separator = ' '; //using the i/o manipulation library adding spaces to fill the rest of the width

	//cout << left << setw(numWidth) << setfill(separator) << tag.getlineNum(); //line number
	//cout << left << setw(nameWidth) << setfill(separator) << "Opened Element: " + tag.getName() << endl; //prints the element opened
}

/**
*
* @param tag - closed element
* printed to the screen
 * *Prints closed elements to screen
 * 
*/
void printClosedElement(element tag)
{
	int nameWidth = 30; //width of the name
	int numWidth = 5; //width of the number
	char separator = ' '; //using the i/o manipulation library adding spaces to fill the rest of the width

	//cout << left << setw(numWidth) << setfill(separator) << tag.getlineNum(); //line number
	//cout << left << setw(nameWidth) << setfill(separator) << "Closed Element: " + tag.getName() << endl; //prints the element closed
	//cout << endl;


}



/**
*
* @param line - prints the line and line number
* @param lineNumber - see above
 * 
 * Prints just complete in line elements to screen
*/
void printCompleteElement(string line, int lineNumber)
{
	int nameWidth = 30; //width of the name
	int numWidth = 5; //width of the number
	int startPos, endPos; //start and end pos for substr
	string fullLine; //for the full line without XML indentation
	string elementContent; //for what is between the tags

	char separator = ' '; //using the i/o manipulation library adding spaces to fill the rest of the width

	startPos = line.find("<");
	endPos = line.find("/n ", startPos + 1); //getting the full line without spacing from XML
	fullLine = line.substr(startPos, (endPos - startPos) - 1); //getting the line with no spacing

	startPos = line.find(">");
	endPos = line.find("<", startPos + 1); //getting what's between the tags aka Content
	elementContent = line.substr(startPos + 1, (endPos - startPos) - 1); //getting content

	//cout << left << setw(numWidth) << setfill(separator) << lineNumber; //prints the name
	//cout << left << setw(nameWidth) << setfill(separator) << "Complete Element: " + fullLine << endl; //prints the complete line
	//cout << left << setw(numWidth) << setfill(separator) << " "; //spacing for next line
	//cout << left << setw(nameWidth) << setfill(separator) << "Element Name: " + getOpen(fullLine) << endl; //prints what is between the tags
	//cout << left << setw(numWidth) << setfill(separator) << " "; //spacing for next line
	//cout << left << setw(nameWidth) << setfill(separator) << "Element Content: " + elementContent << endl; //prints what is between the tags
	//cout << endl;
}


/**
*
* @param songstack - prints the stack after it is added and pops it after each
* element is printed
 *Prints entire stack to screen
*/
void printStack(stack<element> songstack)
{
	//cout << "     Vector contains: ";
	while (songstack.size() != 0) //if the stack isn't empty pop and print
	{
		//cout << songstack.top().getName() << " ";
		songstack.pop();
	}
	//cout << endl; //spacing for neatness
	//cout << endl;
}


/**
*
* @param line - passes in the line to truncate
* @return returns a string to return the tag after truncated th closing tage
 * returns the string of a closed element
*/
string getClosed(string line)
{
	int startPos; //where to start the substr
	int endPos; //where to end the substr
	string finalTag;

	startPos = line.find("/"); //to get tagname without slash
	endPos = line.find(">", startPos + 1); //sets end pos to the closing bracket
	finalTag = line.substr(startPos + 1, (endPos - startPos) - 1); //creates a new string that is the closing tag


	return finalTag;
}


/*
*returns the string of an open element
*/
/**
*
* @param line passes in the line to truncate it to an open tag
* @return returns the truncated line
*/
string getOpen(string line)
{

	int startPos; //where to start the substr
	int endPos; //where to end the substr
	string initialTag, finalTag;

	startPos = line.find("<");
	endPos = line.find(">", startPos + 1); //goes through "line" and finds what's in the brackets

	initialTag = line.substr(startPos + 1, (endPos - startPos) - 1); //creates a new string that is just what's in the brackets
	startPos = initialTag.find("<");
	endPos = initialTag.find(">", startPos + 1); //resets end positions to correspond with the new string

	if (initialTag.find(" ", startPos + 1) != string::npos) //checks if there is a space in the string (ids, etc)
	{
		if (ispunct(initialTag.at(startPos + 1))) //to avoid random punct.
		{
			startPos++;
		}
		endPos = initialTag.find(" ", startPos + 1); //sets the endPos to where the first instance of the space is
		finalTag = initialTag.substr(startPos + 1, (endPos - startPos) - 1); //get's rid of what is after the space and stores in finalTag
	}

	if (initialTag.find(" ", startPos + 1) == string::npos) //if there is no space in the tag
	{
		if (ispunct(initialTag.at(startPos + 1))) //to avoid random punct.
		{
			startPos++;
		}
		finalTag = initialTag.substr(startPos + 1, (endPos - startPos) - 1); //getting the finalTag
	}



	return finalTag;
}




/**
* @param elementTree - passes in the element vector and prints it
* out nicely formatted to match the assignment specifications
* also prints the attributes and their definitions
 * 
 * *print the collected data
*including the line number
*name and children
*/
void displayOutput(vector<element> elementTree)
{
	string test_json = "output.json";
	vector<element>::reverse_iterator it; //iterating the elementTree which is put in backwards because of the stack
	vector<element*>::iterator ij;
	vector<element*>::iterator jt; //for iterating the child vector
	vector<element*> childVecHold; // hold for the child vector
	map<int, element> elementMap; // for printing an organized way
	map<int, element>::iterator itr; //for iterating elementMap
	vector<element*> childVec;
	ofstream inFile(test_json.c_str());
	bool test = false;

	for (it = elementTree.rbegin(); it < elementTree.rend(); ++it) //adding to a map based off line number and element to get rid of possible duplicates
	{
		elementMap.insert(pair<int, element>(it->getlineNum(), (*it)));
		if (it->getChildSize() != 0)//if the element has children
		{
			childVecHold = it->getVector();
			for (jt = childVecHold.begin(); jt < childVecHold.end(); ++jt) //navigating the child vector which points to other elements
			{
				elementMap.insert(pair<int, element>((*jt)->getlineNum(), *(*jt)));
			}

		}

	}
	inFile << "{" << endl;//opening JSON '{'
	for (itr = elementMap.begin(); itr != elementMap.end(); ++itr) //iterates the map for printing to the JSON file
	{
		if (itr->second.hasContent()) //if it has content
		{
			if (itr->second.hasAtr()) // if it also has attribute(s)
			{
				if (next(itr) != elementMap.end())
				{
					inFile << "\"" << itr->second.getName() << "\": " << endl << "[" << endl;
					itr->second.printJSON(inFile, test);//calls function that translates current XML to JSON
					//inFile << "," << endl;
					if (itr->second.getName() == next(itr)->second.getName())//if the name & next name are the same (in his example the phone number with the phone # then the phone number with the fax #)
					{
						test = true;//yes, there is another with the same name, so set as true, so that it doesn't miss a comma thinking that it is the start of a new set of attributes
						next(itr)->second.printJSON(inFile, test);//calls function that translates current XML to JSON
						
						itr++;
					}
					else{
						test = false;
					}
					inFile << "]," << endl;
				}
				else
				{
					inFile << "\"" << itr->second.getName() << "\": " << "\"" << itr->second.getContent() << "\"," << endl;
					itr->second.printJSON(inFile, test);//calls function that translates current XML to JSON
				}
			}
			else//if it has no attributes
			{
				inFile << "\"" << itr->second.getName() << "\": " << "\"" << itr->second.getContent() << "\"," << endl;//print name and content in correct formatting
			}
			if (itr->second.getChildSize() > 0) //if it has children
			{
				inFile << "\"" << itr->second.getName() << "\": " << endl << "{" << endl;
				childVec = itr->second.getVector();
				for (ij = childVec.begin(); ij != childVec.end(); ++ij)//iterate child vector
				{
					int x = 0;
					inFile << "\"" << (*ij)->getName() << "\": " << "\"" << (*ij)->getContent() << "\"";
					if (next(ij) != childVec.end()&& ij != childVec.begin())
					{
						inFile << "," << endl;//adds comma before the child vector ends
					}
					else{
						inFile << endl;//has no comma if the child vector is on the final child
					}

					if (itr->second.hasAtr()) // if it has attributes
					{

						if (next(itr) != elementMap.end())
						{
							inFile << endl << ",[" << endl;//open attributes square brackets
							itr->second.printJSON(inFile, test);//calls function that translates current XML to JSON
							//inFile << "," << endl;
							if (next(itr)->second.getName() == itr->second.getName())
							{
								next(itr)->second.printJSON(inFile, test);//calls function that translates current XML to JSON
								itr++;
								inFile << ",";
							}
							if (next(ij) != childVec.end())
							{
								inFile << "]," << endl;//close attributes square bracket
							}
							else{
								inFile << "]" << endl;//close attributes square bracket
							}
						}
						else
						{
							itr->second.printJSON(inFile, test);//calls function that translates current XML to JSON
						}
					}
					itr++;
				}
				inFile << "}," << endl;
			}
		}
		else //if it doesn't have content
		{
			if (itr->second.getChildSize() > 0 && itr->second.getlineNum() != 2)
			{
				inFile << "\"" << itr->second.getName() << "\": " << endl << "{" << endl;
				childVec = itr->second.getVector();
				for (ij = childVec.begin(); ij != childVec.end(); ++ij)
				{
					inFile << "\"" << (*ij)->getName() << "\": " << "\"" << (*ij)->getContent() << "\"";
					if (next(ij) != childVec.end())//if its not the end of the vector, add a comma
					{
						inFile << "," << endl;
					}
					else if (next(ij) == childVec.end()){//otherwise just add a new line
						inFile << endl;
					}
					if (itr->second.hasAtr()) // if it has attributes
					{
						itr->second.printJSON(inFile, test);//calls function that translates current XML to JSON
					}
					itr++;
				}/*
				if (next(itr)->second.getName() == "metadata"){
					inFile << "}" << endl;
				}
				else{*/
				inFile << "}," << endl;//close bracket with comma (not end)
			}
		}
	}
	inFile << endl << "}";//close bracket
	cout << "You are all set : - )" << endl;
}

/*
* Searches the vector and returns if true or false (whether found a tag)
*/
/*
* @param temp -searches vector to check if temp is in it already
* @param tag - if tag == temp
* @return returns true or false if it found a duplicate
*/
bool checkChild(vector<element*> temp, element tag)
{
	bool check = false; //did it find the tag?
	vector<element*>::iterator jt; //for iterating the temporary vector

	for (jt = temp.begin(); jt != temp.end(); ++jt)
	{
		if ((*jt)->getName() == tag.getName()) //if tag is located in temp too (child vec) - set true
		{
			check = true;
		}
		else
		{
			check = false;						//otherwise set false
		}
	}

	return check;
}


