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
	Problem *problem;
	Setting *setting;
	
	string filename_txt;
	string filename_svg;

public:
	/**
	 *  Constructor
	 *
	 *  @param p 			a pointer to the problem
	 *  @param s 			a pointer to the setting that sould be used for output
	 *  @param name_txt 	a string defining the filename for txt-output
	 *  @param name_svg 	a string defining the filename for svg-output
	 */
	OutputHandler(Problem *p, Setting *s, string name_txt = "out.txt", string name_svg = "out.svg");

	/**
	 *  writes the current setting of problem in defined format into a txt file
	 */
	void write_setting_to_txt();

	/**
	 *  writes the current setting of problem to a svg file
	 */
	void write_setting_to_svg();
};

#endif