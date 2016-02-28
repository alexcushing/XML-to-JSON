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
 * calls the function that will sort the xml into a map and output it into JSON form
 * 
 */
int main(int argc, char** argv) {

	RunProg("song.xml"); //goes through the file and parses each line
	cout << endl;
	return 0;
}

