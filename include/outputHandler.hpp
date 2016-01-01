/**
 *  Class Outputhandler
 *
 *  Handles the output of intern data structure to correctly formatted txt- and svg- files
 */
#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

#include "problem.hpp"
#include "setting.hpp"

using namespace std;

class OutputHandler
{
private:
	/**
	 *  A pointer to the problem the setting is based on
	 */
	Problem *problem;

	/**
	 *  A pointer to the setting that should be outputted
	 */
	Setting *setting;
	

public:
	/*!
	 *  Constructor
	 *
	 *  @param p 			a pointer to the problem
	 *  @param s 			a pointer to the setting that sould be used for output
	 *  @param name_txt 	a string defining the filename for txt-output
	 *  @param name_svg 	a string defining the filename for svg-output
	 */
	OutputHandler(Problem *p, Setting *s);

	/*!
	 *  writes the current setting of problem in defined format into a txt file
     *
     *  @param filename         the path and name of the output file
	 */
	void write_setting_to_txt(string filename);

	/*!
	 *  writes the current setting of problem to a svg file
	 *     
     *  @param filename         the path and name of the output file
	 *  @param with_covex_hull 	if true, the convex hull is added to the svg-file
	 */
	void write_setting_to_svg(string filename, bool with_covex_hull = false);
};

#endif