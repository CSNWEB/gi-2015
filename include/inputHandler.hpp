#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef USE_SFML
#include <SFML/Graphics.hpp>
#endif

#include "abstractForm.hpp"
#include "problem.hpp"
#include "point.hpp"

using namespace std;

class InputHandler
{
private:

	float size_of_sheet_x;
	float size_of_sheet_y;

	int number_of_different_forms;
	
	//vector<string> names_of_forms;
	vector<AbstractForm> forms;
	vector<int> number_of_pieces;
public:
	InputHandler(){};

	void get_input();

	void _d_print_input();

	void _d_paint_input();

	Problem create_problem();
};

#endif