/**
 *  Class Inputhandler
 *
 *  Handles scanning and parsing of input files, creates and initializes the data structure.
 */
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "abstractForm.hpp"
#include "problem.hpp"
#include "point.hpp"

using namespace std;

class InputHandler
{
private:
	/**
	 *  The width of a sheet
	 */
	float size_of_sheet_x;

	/**
	 *  The height of a sheet
	 */
	float size_of_sheet_y;

	/**
	 *  The total number of different forms
	 */
	int number_of_different_forms;
	
	/**
	 *  A vector that stores each individual form once
	 */
	vector<AbstractForm> forms;

	/**
	 * A vector that stores the needed amount of forms for each individual form in vector<AbstractForm> forms
	 */
	vector<int> number_of_pieces;
    
    /**
     * A vector that stores the name of forms for each individual form in vector<AbstractForm> forms
     */
    vector<string> name_of_forms;

    /*!
     *  Flag to check if any input has been read
     */
    bool has_data;
    
public:
	/**
	*  Default constructor.
	*/
	InputHandler();

	/**
	 *  Scans and parses an input file, creates data-structure
	 *
	 *  @param filename 	Name of the input file
	 */
	void get_input(char* filename);

	/**
	 *  Create an instance of Problem with the inpute read by get_input(char*)
	 */
	Problem create_problem();


	/**
	 *  Debugging function: prints the parsed input to console (only if DEBUG-flag was set by compiler)
	 */
	void _d_print_input();
};

#endif